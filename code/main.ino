/*Written by Robodue in this code we are declaring 4 gpiu pins with relay and this
code is making a web server in node mcu itself just 
enter your ssid and password and you can also use this same code*/



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

//final working code for Nodemcu v3 and compatible for 8 Channel Power Relay..
//fb.com/insider7enjoy
//programmed on 13-Sep-2017
//PhantomCluster.com

// prototypes
boolean connectWifi();

//on/off callbacks 
void LightOn();
void LightOff();
void NightLightOn();
void NightLightOff();
void StudyOn();
void StudyOff();
void FanOn();
void FanOff();

// Change this before you flash
const char* ssid = "your ssid";
const char* password = "your password";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *Light = NULL;
Switch *NightLight = NULL;
Switch *Study = NULL;
Switch *Fan = NULL;

//relay pin setup for funct
int relayOne = 5;
int relayTwo = 4;
int relayThree = 0;
int relayFour = 2;
void setup()
{
 
 Serial.begin(115200);
   
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();
    
    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    Light = new Switch("Light", 80, LightOn, LightOff);
    NightLight = new Switch("NightLight", 81, NightLightOn, NightLightOff);
    Study = new Switch("Study", 82, StudyOn, StudyOff);
    Fan = new Switch("fan", 83, FanOn, FanOff);
    
    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*Light);
    upnpBroadcastResponder.addDevice(*NightLight);
    upnpBroadcastResponder.addDevice(*Study);
    upnpBroadcastResponder.addDevice(*Fan);    
    
    
    //relay pins setup i Used D1,D2,D3,D4 followed as assigned below, if you are willing to change Pin or planning to use extra please Check Image in Github File..:)
    pinMode (5, OUTPUT);
    pinMode (4, OUTPUT);
    pinMode (0, OUTPUT);
    pinMode (2, OUTPUT);

   
    digitalWrite (5,HIGH);
    digitalWrite (4,HIGH);
    digitalWrite (0,HIGH);
    digitalWrite (2,HIGH);
     
  }
}
 
void loop()
{
	 if(wifiConnected){
      
      upnpBroadcastResponder.serverLoop();
      
      Light->serverLoop();
      NightLight->serverLoop();
      Study->serverLoop();
      Fan->serverLoop();
	 }
}

void LightOn() {
    Serial.print("Switch 1 turn off ...");
    digitalWrite(relayOne, LOW);   // sets relayOne off
}

void LightOff() {
    Serial.print("Switch 1 turn on ...");
    digitalWrite(relayOne, HIGH);   // sets relayOne on
}

void NightLightOn() {
    Serial.print("Switch 2 turn off ...");
    digitalWrite(relayTwo, LOW);   // sets relayOne o
}

void NightLightOff() {
  Serial.print("Switch 2 turn on ...");
  digitalWrite(relayTwo, HIGH);   // sets relayOne on
}

void StudyOn() {
    Serial.print("Switch 3 turn off ...");
    digitalWrite(relayThree, LOW);   // sets relayOne on
}

void StudyOff() {
  Serial.print("Switch 3 turn on ...");
  digitalWrite(relayThree, HIGH);   // sets relayOne on
}

void FanOn() {
    Serial.print("Switch4 turn off ...");
    digitalWrite(relayFour, LOW);   // sets relayOne on
}

void FanOff() {
  Serial.print("Switch 4 turn on ...");
  digitalWrite(relayFour, HIGH);   // sets relayOne on
}


//sockets



// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
