#include <SoftwareSerial.h>
#include "keyValuePairs.h"
#include "MQTTSender.h"

class UARTKeyValueReader {
private:
  Stream* mySerial; // Generic Stream pointer (works with HardwareSerial & SoftwareSerial)
  int firstByte = 0;
  uint key = 0;
  uint value = 0;
  bool firstByteReceived = false;
  bool secondByteReceived = false;
  bool keyReceived = false;
  bool valueReceived = false;
  bool published = false;
  bool awaitNextListen = true; // after publish have to wait for another listen() call for publishing to be allowed?
  bool dataFrameEnd = false;
  bool dataFrameBegin = false;

  MqttClient* mqttClient;
  keyValuePairs<int, String> keyValueStore;
  keyValuePairs<int, String>* nameMapping;

  unsigned long currentMillis = 0;
  unsigned long previousPublishMillis = 0;
  unsigned long lastReadMillis = 0;
  unsigned long mqttConnectCounter = 0;

  String portName;


public:
  UARTKeyValueReader(Stream* serialInterface, MqttClient* _mqttClient, keyValuePairs<int, String>* _nameMapping, String _portName)
    : mySerial(serialInterface), mqttClient(_mqttClient), nameMapping(_nameMapping), portName(_portName) {
  }

  void listen(bool awaitNext) {
    published = false;
    awaitNextListen = awaitNext;

    currentMillis = millis();
    previousPublishMillis = currentMillis;
    lastReadMillis = currentMillis;  // reset the silence detection
  }

  const bool isPublished() {
    return published;
  }


  void loop() {
    
    unsigned long lastReadMillisTemp = readKeyValuePair();
    if (lastReadMillisTemp != 0) {
      lastReadMillis = lastReadMillisTemp;
    }

    currentMillis = millis();

    // wait until we got data between frame begin and end
    if (!published && dataFrameBegin && dataFrameEnd) {
      previousPublishMillis = currentMillis;
      lastReadMillis = currentMillis;  // reset the silence detection
      dataFrameEnd = false;
      dataFrameBegin = false;

      Serial.print("Publishing on ");
      Serial.println(portName);
      sendMqttMessage(mqttClient, &keyValueStore, nameMapping, portName);
      published = awaitNextListen;
    }
  }


private:
  unsigned long readKeyValuePair() {
    uint16_t result = read2Bytes();
    unsigned long lastReadMillis = 0;

    if (secondByteReceived == true) {
      if (keyReceived == false) {
        key = result;
        keyReceived = true;
      } else {
        value = result;
        keyReceived = false;
        valueReceived = true;
      }
      secondByteReceived = false;
    }

    if (valueReceived == true) {
      #ifdef debug
      if (key == 550) {
        Serial.println("---------- Begin data frame ---------");
      }

      Serial.print("Key: ");
      Serial.print(key);
      Serial.print(" Value: ");
      Serial.println(value);

      if (key == 536) {
        Serial.println("---------- End data frame ---------");
      }
      #endif

      if (dataFrameBegin && key == 536) {
        dataFrameEnd = true;
      }

      if (key == 550) {
        dataFrameBegin = true;
      }

      lastReadMillis = millis();

      // Check existence in the key value store
      if (keyValueStore.find(key) != NULL) {
        // Delete the key
        keyValueStore.erase(key);
      }

      // insert measurement to key value store
      keyValueStore.insert(key, (String)value);

      // Reset all bool variables
      resetFlags();
    }

    return lastReadMillis;
  }


  uint16_t read2Bytes() {
    uint16_t returnValue = 0;
    if (mySerial->available() > 0) {
      // Flash LED to indicate read
      digitalWrite(LED_BUILTIN, LOW);

      if (firstByteReceived == true) {
        returnValue = (firstByte << 8) | mySerial->read();
        firstByte = 0;
        firstByteReceived = false;
        secondByteReceived = true;
      } else {
        firstByte = mySerial->read();
        firstByteReceived = true;
      }

      // Reset LED state
      digitalWrite(LED_BUILTIN, HIGH);
    }
    return returnValue;
  }

  void resetFlags() {
    firstByteReceived = false;
    secondByteReceived = false;
    keyReceived = false;
    valueReceived = false;
    key = 0;
    value = 0;
    firstByte = 0;
  }
};
