#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include "settings.h"
#include "keyValuePairs.h"
#include "mappings_1.h"
#include "UARTKeyValueReader.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
UARTKeyValueReader reader1(rxPin, txPin, &mqttClient, &nameMapping1, "Port_1");

#ifdef useSecondSerial
#include "mappings_2.h"
UARTKeyValueReader reader2(rxPin2, txPin2, &mqttClient, &nameMapping2, "Port_2");
#endif

bool reader1IsCurrent = true;

void setup() {
  Serial.begin(serialBaud);

  reader1.begin(serialBaud);
  reader1.listen();

#ifdef useSecondSerial
  reader2.begin(serialBaud);
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

  if (reader1IsCurrent) {
    if (reader1.isPublished()) {
#ifdef useSecondSerial
      reader1IsCurrent = false;
      reader2.listen();
#else
      reader1.listen();
#endif
    } else {
      reader1.loop();
    }
  }


#ifdef useSecondSerial
  if (!reader1IsCurrent) {
    if (reader2.isPublished()) {
      reader1IsCurrent = true;
      reader1.listen();
    } else {
      reader2.loop();
    }
  }
#endif
}
