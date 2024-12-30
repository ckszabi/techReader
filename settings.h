// WIFI settings
// your network SSID (name)
const char wifiSsid[] = "SSID";
// your network password (use for WPA, or use as key for WEP)
const char wifiPassword[] = "password";    

// MQTT settings
const char mqttBroker[]   = "broker IP";
int        mqttPort       = 1883;
const char mqttId[]       = "Tech controller 1";
const char mqttUsername[] = "mqtt-tech";
const char mqttPassword[] = "mqtt pass";

//set interval for sending messages (milliseconds)
const long mqttSendInterval = 10000;