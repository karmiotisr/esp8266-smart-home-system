# ESP8266-based Smart-Home System
A Home control system with physical button and remote-control through Blynk application and support of feedback status. The present code is part of the thesis of Aristos Karmiotis at School of Electrical Engineering @ Hellenic Mediterranean University. It is an adaptation of the project presented [here](https://github.com/techstudycell/IoT-Project-using-ESP32-NodeMCU-network-with-Blynk#iot-project-using-esp32-nodemcu-network-with-blynk).

## Files description:
* `source/dht11_button_fan.ino`: Arduino code for the ESP8266. It supports DHT11 temperature/humidity sensor and has also definitions for the Blynk app virtual pins.
* `source/dht11_button_fan_wιth_auto_close`: Mostly same code as the previous source file, however at this implementation a simple automation is imlemented. A virtual LED at Blynk app is used to indicate the operational mode of a fan. When DHT11 temperature value is above a specific threshold, the fan (or the corresponding LED) is activated too.
* `design/schematic.json`: The schematic of the PCB board. Can be imported to an EDA tool like easyEDA.
* `design/PCB.json`: The design of the PCB board. Can be imported to an EDA tool like easyEDA.

## Demonstration
A video demonstration of the project can be found [here](https://www.youtube.com/watch?v=E98-GbPA7V0).