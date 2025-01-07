#include <SoftwareSerial.h>
#include "keyValuePairs.h"
#include "MQTTSender.h"

class UARTKeyValueReader {
private:
  SoftwareSerial mySerial;
  int firstByte = 0;
  uint key = 0;
  uint value = 0;
  bool firstByteReceived = false;
  bool secondByteReceived = false;
  bool keyReceived = false;
  bool valueReceived = false;
  bool published = false;

  MqttClient* mqttClient;
  keyValuePairs<int, String> keyValueStore;
  keyValuePairs<int, String>* nameMapping;

  unsigned long currentMillis = 0;
  unsigned long previousPublishMillis = 0;
  unsigned long lastReadMillis = 0;
  unsigned long mqttConnectCounter = 0;

  String portName;

public:
  UARTKeyValueReader(int rxPin, int txPin, MqttClient* _mqttClient, keyValuePairs<int, String>* _nameMapping, String _portName)
    : mySerial(rxPin, txPin, true), mqttClient(_mqttClient), nameMapping(_nameMapping), portName(_portName) {
      pinMode(rxPin, INPUT);
      pinMode(txPin, OUTPUT);
      pinMode(LED_BUILTIN, OUTPUT);
  }

  void begin(long baudRate) {
    mySerial.begin(baudRate);
  }

  void listen() {
    mySerial.listen();
    published = false;

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

    // 1. Wait on timeout from setting.h
    // 2. Wait on silence from controller
    if (!published && (currentMillis - previousPublishMillis >= mqttSendInterval)) { // || currentMillis - lastReadMillis > 2500
      previousPublishMillis = currentMillis;
      lastReadMillis = currentMillis;  // reset the silence detection

      Serial.print("Publishing on ");
      Serial.println(portName);
      sendMqttMessage(mqttClient, &keyValueStore, nameMapping, portName);
      published = true;
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
    if (mySerial.available() > 0) {
      // Flash LED to indicate read
      digitalWrite(LED_BUILTIN, LOW);

      if (firstByteReceived == true) {
        returnValue = (firstByte << 8) | mySerial.read();
        firstByte = 0;
        firstByteReceived = false;
        secondByteReceived = true;
      } else {
        firstByte = mySerial.read();
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
