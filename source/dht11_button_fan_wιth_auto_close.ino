/**********************************************************************************
 *  TITLE: Blynk + Manual Switch control Relays using NodeMCU (Real time feedback + no WiFi control)
 *  Click on the following links to learn more.
 *  YouTube Video: https://youtu.be/fRCVx6yKoYw
 *  Related Blog : https://easyelectronicsproject.com/esp32-projects/
 *  by Tech StudyCell
 *  Preferences--> Aditional boards Manager URLs :
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *
 *  Download Board ESP8266 NodeMCU : https://github.com/esp8266/Arduino
 *  Download the libraries
 *  https://github.com/blynkkk/blynk-library/releases/download/v0.6.1/Blynk_Release_v0.6.1.zip
 **********************************************************************************/

//#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11
#define FAN_PIN D10   // FAN RELAY
WidgetLED FAN(V0);
float humDHT = 0;
float tempDHT = 0;
int Val=0;
DHT dht(DHTPIN, DHTTYPE);
// define the GPIO connected with Relays and switches
#define RelayPin1 9  //SD2
#define RelayPin2 4  //D2
#define RelayPin3 14 //D5
#define RelayPin4 12 //D6

//#define RelayPin5 1  //D10/TX
//#define RelayPin6 2  //D4
#define RelayPin7 5 //D1
//#define RelayPin8 15 //D8

#define SwitchPin1 10  //SD3
#define SwitchPin2 0   //D3
#define SwitchPin3 13  //D7
#define SwitchPin4 3   //RX

#define wifiLed   16  //D0

#define VPIN_BUTTON_1    V10
#define VPIN_BUTTON_2    V11
#define VPIN_BUTTON_3    V12
#define VPIN_BUTTON_4    V13
#define VPIN_BUTTON_5    V5   // shut down all lights

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 4
int toggleState_5 = 1; //Define integer to remember the toggle state for relay 5
int toggleState_6 = 1; //Define integer to remember the toggle state for relay 6
int toggleState_7 = 1; //Define integer to remember the toggle state for relay 7
int toggleState_8 = 1; //Define integer to remember the toggle state for relay 8

int toggleState_0 = 0; //Define integer to shut down all the lights

int wifiFlag = 0;

#define AUTH "c21b890308294bceabb60a2ff2ace869"  // You should get Auth Token in the Blynk App.
#define WIFI_SSID "epic WIFI 20045"              //Enter Wifi Name
#define WIFI_PASS "32254381893304039206"         //Enter wifi Password


BlynkTimer timer;

void relayOnOff(int relay){

    switch(relay){
     case 1:
           if(toggleState_1 == 1){
           digitalWrite(RelayPin1, LOW); // turn on relay 1
              toggleState_1 = 0;
              Serial.println("Device1 ON");
              }
             else{
              digitalWrite(RelayPin1, HIGH); // turn off relay 1
              toggleState_1 = 1;
              Serial.println("Device1 OFF");
             }
             delay(100);
      break;
      case 2:
             if(toggleState_2 == 1){
              digitalWrite(RelayPin2, LOW); // turn on relay 2
              toggleState_2 = 0;
              Serial.println("Device2 ON");
              }
             else{
              digitalWrite(RelayPin2, HIGH); // turn off relay 2
              toggleState_2 = 1;
              Serial.println("Device2 OFF");
              }
             delay(100);
      break;
      case 3:
             if(toggleState_3 == 1){
              digitalWrite(RelayPin3, LOW); // turn on relay 3
              toggleState_3 = 0;
              Serial.println("Device3 ON");
              }
             else{
              digitalWrite(RelayPin3, HIGH); // turn off relay 3
              toggleState_3 = 1;
              Serial.println("Device3 OFF");
              }
             delay(100);
      break;
      case 4:
             if(toggleState_4 == 1){
              digitalWrite(RelayPin4, LOW); // turn on relay 4
              toggleState_4 = 0;
              Serial.println("Device4 ON");
              }
             else{
              digitalWrite(RelayPin4, HIGH); // turn off relay 4
              toggleState_4 = 1;
              Serial.println("Device4 OFF");
              }
             delay(100);
      break;
      default : break;
      }

}

void with_internet(){

   //Manual Switch Control

   if (digitalRead(SwitchPin1) == LOW){
   delay(200);
   relayOnOff(1);
   Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);   // Update Button Widget
  }

    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      relayOnOff(2);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);   // Update Button Widget
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      relayOnOff(3);
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);   // Update Button Widget
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      relayOnOff(4);
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);   // Update Button Widget
    }
}
void without_internet(){

    //Manual Switch Control

    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      relayOnOff(1);
    }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      relayOnOff(2);
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      relayOnOff(3);
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      relayOnOff(4);
    }
}

BLYNK_CONNECTED() {

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1); // Toggle the relay 1
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, toggleState_4);
}

BLYNK_WRITE(VPIN_BUTTON_5) {   //Virtual pin on Blynk app
    toggleState_0 = param.asInt();   //shut down all the light and update the virtual pin on app
    digitalWrite( RelayPin1, toggleState_0);
    digitalWrite( RelayPin2, toggleState_0);
    digitalWrite( RelayPin3, toggleState_0);
    digitalWrite( RelayPin4, toggleState_0);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_0);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_0);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_0);
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_0);
}


void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
  if (isconnected == true) {
    wifiFlag = 0;
    digitalWrite(wifiLed, LOW); //Turn on WiFi LED
  }
}
void setup()
{
  Serial.begin(9600);
   pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF

  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);

//  digitalWrite(RelayPin5, toggleState_5);
 // digitalWrite(RelayPin6, toggleState_6);
  digitalWrite(RelayPin7, toggleState_7); // can be deleted
 // digitalWrite(RelayPin8, toggleState_8);


  WiFi.begin(WIFI_SSID, WIFI_PASS);
  timer.setInterval(3000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
  Blynk.config(AUTH);
}
BLYNK_WRITE(V16)
{
  Val = param.asInt(); // assigning incoming value from pin V3 to a variable

  Serial.print(" The Threshhold value is: ");
  Serial.println(Val);
  Serial.println();

}


void loop()
{  {

  Blynk.run();
  delay(100);
  humDHT = dht.readHumidity();
  tempDHT = dht.readTemperature();
  if (isnan(humDHT) || isnan(tempDHT))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(tempDHT);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(humDHT);
  Serial.print(F("%"));
  Serial.println();

  Serial.println("***********************");
  Serial.println();

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (Val > tempDHT)
  {
    digitalWrite(FAN_PIN, HIGH);
    FAN.off();
}
  else {
    digitalWrite(FAN_PIN, LOW);
    FAN.on();

  }

  Blynk.virtualWrite(V14, tempDHT);
  Blynk.virtualWrite(V15, humDHT);
}
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi Not Connected");
  }
  else
  {
    Serial.println("WiFi Connected");
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (wifiFlag == 0)
    with_internet();
  else
    without_internet();
}
