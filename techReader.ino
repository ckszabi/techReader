#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include "settings.h"
#include "keyValuePairs.h"
#include "mappings_1.h"
#include "UARTKeyValueReader.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
SoftwareSerial mySoftSerial1(rxPin, txPin, true); 
UARTKeyValueReader reader1(&mySoftSerial1, &mqttClient, &nameMapping1, "Port_1");

#ifdef useSecondSerial
  #include "mappings_2.h"
  SoftwareSerial mySoftSerial2(rxPin2, txPin2, true); 
  UARTKeyValueReader reader2(&mySoftSerial2, &mqttClient, &nameMapping2, "Port_2");
#endif

bool reader1IsCurrent = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  mySoftSerial1.begin(serialBaud);
  #if defined(useSecondSerial)
    reader1.listen(true);
  #else
    reader1.listen(false);
  #endif  


#ifdef useSecondSerial
  pinMode(rxPin2, INPUT);
  pinMode(txPin2, OUTPUT);
  
  mySoftSerial2.begin(serialBaud);
  Serial.begin(serialBaud); // normal debugging
#else
  Serial.begin(serialBaud); // normal debugging
#endif

  setup_wifi();
  setup_mqtt();
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

  mqttConnect(&mqttClient, true);
}

void loop() {
#ifndef useSecondSerial
  reader1.loop();
#else
  alternateLoop();
#endif
  
}

#if defined(useSecondSerial)
  // when 1 or 2 serials need to be used, and these are SoftwareSerials
  // then need to alternate between them
  void alternateLoop() {
    if (reader1IsCurrent) {
      if (reader1.isPublished()) {
        reader1IsCurrent = false;
        mySoftSerial2.listen();
        reader2.listen(true);
      } else {
        reader1.loop();
      }
    }

    if (!reader1IsCurrent) {
      if (reader2.isPublished()) {
        reader1IsCurrent = true;
        mySoftSerial1.listen();
        reader1.listen(true);
      } else {
        reader2.loop();
      }
    }
  }
#endif
