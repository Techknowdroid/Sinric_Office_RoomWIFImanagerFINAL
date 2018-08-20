/*
 Techknowdroid VERSION 1.00 -  5th August,2018 
 When your ESP8266 boots, it is set up in Station mode, and tries to connect to a previously saved Access Point (a known SSID and password combination);
 If this process fails, it sets the ESP into Access Point mode;
 Using any Wi-Fi enabled device with a browser, connect to the newly created Access Point (default name ESPConnectAP);
 After establishing a connection with the ESPConnectAP, you can go to the default IP address 192.168.4.1 to open a web page that allows you to configure your SSID and password;
 Once a new SSID and password is set, the ESP reboots and tries to connect;
 If it establishes a connection, the process is completed successfully. Otherwise, it will remain set up as an Access Point.
*/  

// Using WIFI Manager ESPConnectAP instead of hardcoded SSID and Password.
//
   

#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();
boolean wifiConnected = false;

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> //  get it from https://github.com/Links2004/arduinoWebSockets/releases 
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>

#include <LiquidCrystal_I2C.h>  // get from https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
#include <Wire.h>

// Set web server port number to 80
WiFiServer server(80);  // if code does not work then comment out only this entire line.

LiquidCrystal_I2C lcd(0x27, 20, 4);

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;


UpnpBroadcastResponder upnpBroadcastResponder;

#define MyApiKey ".............................." // Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard

#define MYPIN1 D3  //GPIO 0
#define MYPIN2 D4  //GPIO 02
#define MYPIN3 D5  //GPIO 14
#define MYPIN4 D6  //GPIO 12
#define MYPIN5 D7  //GPIO 13

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void setPowerStateOnServer(String deviceId, String value);
void setTargetTemperatureOnServer(String deviceId, String value, String scale);

// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == "........................") // Device ID of MYPIN1 which is Light 13 on the sinric webpage https://sinric.com/
  {  
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    Serial.print(" Switch D3");
    pinMode(MYPIN1, HIGH);
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Light  13: On     ");
    delay(5000);
    lcd.noBacklight();
  
  } 
  else if (deviceId == "........................") // Device ID of MYPIN2 which is Light 14 on the sinric webpage https://sinric.com/
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    Serial.print(" Switch D4");
    pinMode(MYPIN2, HIGH);
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 1);
    lcd.print("Light  14: On     ");
    delay(5000);
    lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN3 which is Light 15 on the sinric webpage https://sinric.com/
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    Serial.print(" Switch D5");
    pinMode(MYPIN3, HIGH);
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 2);
    lcd.print("Light  15: On     ");
    delay(5000);
    lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN4 which is Light 16 on the sinric webpage https://sinric.com/
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    Serial.print(" Switch D6");
    pinMode(MYPIN4, HIGH);
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 3);
    lcd.print("Light  16: On     ");
    delay(5000);
    lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN5 which is Light 17 on the sinric webpage https://sinric.com/
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    Serial.print(" Switch D7");
    pinMode(MYPIN5, HIGH);
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 4);
    lcd.print("Light  17: On     ");
    delay(5000);
    lcd.noBacklight();

  }
   
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);    
  }     
}

void turnOff(String deviceId) {
   if (deviceId == "........................") // Device ID of MYPIN1 Device ID of MYPIN1 which is Light 13 on the sinric webpage https://sinric.com/
   {  
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     Serial.print(" Switch D3");
     pinMode(MYPIN1, LOW);
     lcd.noBacklight();
     lcd.backlight();
     lcd.setCursor(0, 0);
     lcd.print("Light  13: Off     ");
     delay(5000);
     lcd.noBacklight();
   }
   else if (deviceId == "........................") // Device ID of MYPIN2 which is Light 14 on the sinric webpage https://sinric.com/
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     Serial.println(" Switch D4");
     pinMode(MYPIN2, LOW);
     lcd.noBacklight();
     lcd.backlight();
     lcd.setCursor(0, 1);
     lcd.print("Light  14: Off     ");
     delay(5000);
     lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN3 which is Light 15 on the sinric webpage https://sinric.com/
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     Serial.print(" Switch D5");
     pinMode(MYPIN3, LOW);
     lcd.noBacklight();
     lcd.backlight();
     lcd.setCursor(0, 2);
     lcd.print("Light  15: Off     ");
     delay(5000);
     lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN4 which is Light 16 on the sinric webpage https://sinric.com/
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     Serial.print(" Switch D6");
     pinMode(MYPIN4, LOW);
     lcd.noBacklight();
     lcd.backlight();
     lcd.setCursor(0, 3);
     lcd.print("Light  16: Off     ");
     delay(5000);
     lcd.noBacklight();

  }
   else if (deviceId == "........................") // Device ID of MYPIN5 which is Light 17 on the sinric webpage https://sinric.com/
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     Serial.print(" Switch D7");
     pinMode(MYPIN5, LOW);
     lcd.noBacklight();
     lcd.backlight();
     lcd.setCursor(0, 4);
     lcd.print("Light  17: Off     ");
     delay(5000);
     lcd.noBacklight();

  }
  
  else {
     Serial.print("Turn off for unknown device id: ");
     Serial.println(deviceId);    
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");
    //Create system initialized message
    lcd.clear();
    lcd.setCursor(0, 0);
    delay(1000);
    lcd.print("Sinric ONLINE:");
    delay(1000);
    lcd.setCursor(0, 2);
    lcd.print("Give Alexa Commands");
    delay(7000);
    lcd.clear();   
    lcd.noBacklight();
    }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Switch or Light device types
        // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html

        // For Light device type
        // Look at the light example in github
          
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if (action == "SetTargetTemperature") {
            String deviceId = json ["deviceId"];     
            String action = json ["action"];
            String value = json ["value"];
        }
        else if (action == "test") {
            Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  //Initalize LCD
  lcd.init();
  lcd.noBacklight();
  lcd.backlight();
  lcd.begin(4, 20);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Creating ESPConnectAP.");
  delay(4000);
  Serial.println("Waiting for ESPConnectAP.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Open ESPConnectAP");
  lcd.setCursor(0, 2);
  lcd.print("on your phone..");
  //delay(5000);
  
    //WiFiManager
    //Local intialization.Fetches ssid and password from eeprom and tries to connect.
    WiFiManager wifiManager;

    // Uncomment and run below code once, if you want to erase all the stored information
    //reset saved settings
    //wifiManager.resetSettings();
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    // fetches ssid and pass from eeprom and tries to connect if it does not connect automatically it starts an access point with the specified name "ESPConnectAP" ,
    // and goes into a blocking loop awaiting configuration.This can take upto a minute to create the ESPConnectAP.
    //This can take upto a minute to create the ESPConnectAP.
    wifiManager.autoConnect("ESPConnectAP");
    
    //Or use below code for an auto generated name ESP + ChipID if you don't want to use "ESPConnectAP" as the name.
    //wifiManager.autoConnect();
    //This can take upto a minute to create the ESPConnectAP.
    
    
    //if you get here you have connected to the WiFi
   Serial.println("connected...Yipee!!)");  


   // Initialise wifi connection
   server.begin();  // if code does not work then comment out only this entire line.
   
   wifiConnected = connectWifi();
   
   
  
  
  // SINRIC CODE starts from here.
  //Initalize LCD
 
  Serial.println("Waiting for WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  
  }
  Serial.println("WiFi Connected.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected to:");
    lcd.setCursor(0, 2);
    lcd.print(WiFi.SSID());
    delay(5000);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("WiFi Connected to SSID...  ");
  Serial.println(WiFi.SSID());
  Serial.println("WiFi Password...NOT DISPLAYED.");
//  Serial.print(WiFi.PASS());

//Create Polling Message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Getting Status   ");
    lcd.setCursor(0, 2);
    lcd.print("  Of Smart Devices  ");
    delay(4000);

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night. Thanks @MacSass
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}

// If you are going to use a push button to on/off the switch manually, use this function to update the status on the server
// so it will reflect on Alexa app.
// eg: setPowerStateOnServer("deviceid", "ON")
void setPowerStateOnServer(String deviceId, String value) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}

//eg: setPowerStateOnServer("deviceid", "CELSIUS", "25.0")
void setTargetTemperatureOnServer(String deviceId, String value, String scale) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["action"] = "SetTargetTemperature";
  root["deviceId"] = deviceId;
  
  JsonObject& valueObj = root.createNestedObject("value");
  JsonObject& targetSetpoint = valueObj.createNestedObject("targetSetpoint");
  targetSetpoint["value"] = value;
  targetSetpoint["scale"] = scale;
   
  StreamString databuf;
  root.printTo(databuf);
  
  webSocket.sendTXT(databuf);
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
 // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
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
   // Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
