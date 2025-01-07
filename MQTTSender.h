int mqttConnect(MqttClient* mqttClient, bool wait);
String getMappedKeyName(int key, keyValuePairs<int, String>* keyNameMapping, String portName);

void sendMqttMessage(MqttClient* mqttClient, keyValuePairs<int, String>* keyValues, keyValuePairs<int, String>* keyNameMapping, String portName) {

  if (!mqttClient->connected()) {  // if the client has been disconnected,
    Serial.println("Client disconnected, attempting reconnection");
    Serial.println();

    if (!mqttConnect(mqttClient, false)) {
      Serial.print("Client reconnected!");
      Serial.println();
    } else {
      delay(1000);
      return;
    }
  }
  #ifdef debug
  Serial.println("Sending messages to MQTT server.");
  #endif

  // Iterate over keyValueStrore and add all entries to mqtt message
  for (auto keyValuePair : *keyValues) {
    String mqttMessage = getMappedKeyName(keyValuePair.key, keyNameMapping, portName);

    // Ignore all messages théy don't have a mapping
    // If you miss a message, please add a mapping to mappings.h
    if (!mqttMessage.equals("")) {
      mqttClient->beginMessage(mqttMessage);
      mqttClient->print(keyValuePair.value);
      mqttClient->endMessage();

      // Serial.print("Sending mqtt message to topic: ");
      // Serial.print(mqttMessage);
      // Serial.print(" value: ");
      // Serial.println(keyValuePair.value);
    }
  }

  // Clear key value store after sending to server
  keyValues->clear();
}

/**
returns connection status, which is other than zero on error, 0 on connected
**/
int mqttConnect(MqttClient* mqttClient, bool wait) {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(mqttBroker);
  //mqttClient.setId(String(mqttId) + String(" - ") + String(++mqttConnectCounter));
  if (!mqttClient->connect(mqttBroker, mqttPort)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient->connectError());

    if (wait) {
      while (1)
        ;
    }
  } else {
    Serial.println("You're connected to the MQTT broker!");
    Serial.println();
  }


  return mqttClient->connectError();  // return status
}

String getMappedKeyName(int key, keyValuePairs<int, String>* keyNameMapping, String portName) {
  // Serial.print("lookup for key: ");
  // Serial.println(key);
  String mappedName = "";
  String* foundName = keyNameMapping->find(key);
  if (foundName != NULL) {
    // Serial.print("found: ");
    // Serial.println(*foundName);
    mappedName = (String)mqttId + (String)'/' + portName + (String)'/'+ *foundName;
  } else {
    #ifdef debug
    Serial.print("Number: ");
    Serial.print(key);
    Serial.println(" not found in mapping. You can add this key to mappings.h .");
    #endif
    if (publishUnmapped) {
      mappedName = (String)mqttId + (String) "/Unknown/" + portName + (String)'/' + (String)key;
    }
  }

  return mappedName;
}