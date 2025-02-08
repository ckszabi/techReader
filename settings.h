// WIFI settings
// your network SSID (name)
const char wifiSsid[] = "SSID";
// your network password (use for WPA, or use as key for WEP)
const char wifiPassword[] = "password";    

// MQTT settings
const char mqttBroker[]   = "broker IP";
int mqttPort = 1883;
const char mqttId[] = "Tech controller 1";
const char mqttUsername[] = "mqtt-tech";
const char mqttPassword[] = "mqtt pass";

//set interval for sending messages (milliseconds)
const long mqttSendInterval = 10000;

const bool publishUnmapped = false;

const int serialBaud = 9600;

//UART SoftwareSerial pins
const int txPin =12;  // D1 GPIO5, D2 GPIO4,  D5 GPIO14, D6 GPIO12
const int rxPin =5; 

// comment out if not desired and only one port is wired
#define useSecondSerial

#ifdef useSecondSerial
   // use the harware UART for the secondary port communication? comment out if not desired
  //#define useHardwareForSecondSerial

  // otherwise use SoftwareSerial on the second pair of pins
  const int txPin2 =14;  // D1 GPIO5, D2 GPIO4,  D5 GPIO14, D6 GPIO12
  const int rxPin2 =4; 
#endif

// Print Serial debugging messages, but only when the harware Serial is not used for TECH reading
#ifndef useHardwareForSecondSerial
  #define debug
#endif