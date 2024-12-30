#include <SoftwareSerial.h>
#include "keyValuePairs.h"

//UART Settings
#define txPin 4 // D2
#define rxPin 5 // D1

// Set up a new SoftwareSerial object
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin, true);

int firstByte = 0;
uint key = 0;
uint value = 0;
bool firstByteReceived = false;
bool secondByteReceived = false;
bool keyReceived = false;
bool valueReceived = false;

uint16_t read2Bytes() {
  uint16_t returnValue = 0;

  if (mySerial.available() > 0){
    // Flash LED to indicate read
    digitalWrite(LED_BUILTIN, LOW);

    if (firstByteReceived == true){
      returnValue = (firstByte << 8) |  mySerial.read();
      //Serial.println(returnValue);
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

unsigned long readKeyValuePair(keyValuePairs<int,String> *keyValueStore) {
  uint16_t result = read2Bytes();
  unsigned long lastReadMillis = 0;

  if (secondByteReceived == true){
    if (keyReceived == false ) {
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
    if (key == 550){
      Serial.println("---------- Begin data frame ---------");
    }
    
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(" Value: ");
    Serial.println(value);

    if (key == 536) {
      Serial.println("---------- End data frame ---------");
    }

    lastReadMillis= millis();

    // Check existence in the key value store
    if (keyValueStore->find (key) != NULL) {
      // Delete the key 
      keyValueStore->erase(key);
    }

    // insert measurement to key value store
    keyValueStore->insert(key,(String)value);

    // Reset all bool variables
    firstByteReceived = false;
    secondByteReceived = false;
    keyReceived = false;
    valueReceived = false;
    key = 0;
    value = 0;
    firstByte = 0;
  }

  return lastReadMillis;
}
