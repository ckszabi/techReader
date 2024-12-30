#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include "settings.h"
#include "uartReceive.h"
#include "keyValuePairs.h"
#include "mappings.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long lastReadMillis = 0;
unsigned long mqttConnectCounter = 0;

keyValuePairs<int, String> keyValueStore;

void setup() {
  setup_pins();
  
  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);

  // Start serial monitor for debugging
  Serial.begin(9600);

  setup_wifi();
  setup_mqtt();

  mqttConnect(true);

}

void setup_pins() {
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // Setup build in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup_wifi() {
  // Attempt to connect to Wifi network
  Serial.print("Attempting to connect to Wifi SSID: ");
  Serial.println(wifiSsid);
  while (WiFi.begin(wifiSsid, wifiPassword) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println("You're connected to the wifi network");
}

void setup_mqtt() {
  mqttClient.setId(mqttId);
  mqttClient.setUsernamePassword(mqttUsername, mqttPassword);
}

/**
returns connection status, which is other than zero on error
**/
int mqttConnect(bool wait) {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(mqttBroker);
  //mqttClient.setId(String(mqttId) + String(" - ") + String(++mqttConnectCounter));
  if (!mqttClient.connect(mqttBroker, mqttPort)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    if (wait) {
      while (1);
    }
  } else {
    Serial.println("You're connected to the MQTT broker!");
    Serial.println();
  }

 
  return mqttClient.connectError(); // return status
}

String getMappedKeyName(int key) {
  // Serial.print("lookup for key: ");
  // Serial.println(key);
  String mappedName = "";
  String *foundName = nameMapping.find (key);
  if (foundName != NULL) {
    // Serial.print("found: ");
    // Serial.println(*foundName);
    mappedName = (String)mqttId + (String)'/' + *foundName;
  } else {
    Serial.print("Number: ");
    Serial.print(key);
    Serial.println(" not found in mapping -> ignored. You should add this key to mappings.h .");
    mappedName = (String)mqttId + (String)"/Unknown/" + (String)key;
  }

  return mappedName;
}

void sendMqttMessage() {
  currentMillis = millis();

  // 1. Wait on timeout from setting.h
  // 2. Wait on silence from controller
  if (currentMillis - previousMillis >= mqttSendInterval || currentMillis - lastReadMillis > 1500) {
    // save the last time a message was sent
    previousMillis = currentMillis;
    lastReadMillis = currentMillis;

    Serial.println("Sending messages to MQTT server.");

    if(!mqttClient.connected()) { // if the client has been disconnected,
      Serial.println("Client disconnected, attempting reconnection");
      Serial.println();

      if (!mqttConnect(false)) {
        Serial.print("Client reconnected!");
        Serial.println();
      }
      delay(1000);
    }

    // Iterate over keyValueStrore and add all entries to mqtt message
    for (auto keyValuePair : keyValueStore){
      String mqttMessage = getMappedKeyName(keyValuePair.key);
      
      // Ignore all messages théy don't have a mapping
      // If you miss a message, please add a mapping to mappings.h
      if (!mqttMessage.equals("")){
        mqttClient.beginMessage(mqttMessage);
        mqttClient.print(keyValuePair.value);
        mqttClient.endMessage();

        // Serial.print("Sending mqtt message to topic: ");
        // Serial.print(mqttMessage);
        // Serial.print(" value: ");
        // Serial.println(keyValuePair.value);
      }
    }
    
    // Clear key value store after sending to server
    keyValueStore.clear();
  }
}

void loop() {
  unsigned long lastReadMillisTemp = readKeyValuePair(&keyValueStore);
  if (lastReadMillisTemp != 0) {
    lastReadMillis = lastReadMillisTemp;
  }
  sendMqttMessage();
}



