Code initial version from @Wingsofcourage https://github.com/Wingsofcourage, from https://github.com/mariusz-ostoja-swierczynski/tech-controllers/issues/40

# How the solution works ?

Tech controllers send their status every couple of seconds to the RS port
The Wemos D1 mini will receive those signals from the tech controllers
Convert the signals to an internal key-value-store
After a timeout (default 10s) the last received values are send to a customisable MQTT Server (ioBroker, home assistant, ... )

# Advanced use

It might happen that the TECH device you want to connect to has 2 ports: one for controller, one for another module. 
The code can read UART data from 2 different ports - to gather all the data possible from both ports.

For example the room regulator's set temperature wasn't available on 'controller port' of a i-1 valve controller, but it is published and available on the 'module port' of the same i-1 valve controller.

# What do you need ?

- Wemos D1 mini
- 5V step down regulator e.g. AMS 1117 5V
- Some wire.

# Cabling
If you look on the RS port female: Right pin1.

![image](https://github.com/user-attachments/assets/c6a2b7fc-aca4-4616-8869-73e852f26221)


PIN 2+4 GND

PIN 6 VCC 12V

PIN 3 RX

Connect GND and VCC to the voltage regulator and RX to D1 of your Wemos D1 mini.

Customise the settings.h

In Arduino Studio download ArduinoMqttClient and ESP8266WiFi libs.

Choose 160 Mhz as CPU speed for the Wemos D1 mini board from the tools menu

Increase the buffer size in SoftwareSerial.h from 64 to 256

Flash the code to the Wemos D1 mini with Arduino Studio.

Connect the Wemos D1 Mini to your tech controller.

Have fun.

# Notes:
Support read only.

Can look like:

![image](https://github.com/user-attachments/assets/1c71450a-dd09-425e-b873-f1ba44a6bd13)
