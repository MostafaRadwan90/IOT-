#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <Ticker.h>

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  //ticker.attach(0.2, tick);
}

void setup() {
 // initialize digital pin GPIO2/D9 as an output.
 pinMode(12, OUTPUT);
 Serial.begin(115200);
   WiFiManager wifiManager;
    wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  
 }
 // the loop function runs over and over again forever
 void loop() {
if( WiFi.status() == WL_CONNECTED)
{
 digitalWrite(12, HIGH); // turn the LED on (HIGH is the voltage level)
 Serial.println ("    hi"); 
 delay(1500);              // wait for a second
 digitalWrite(12, LOW); // turn the LED off by making the voltage LOW
  Serial.println ("    low"); 
 delay(1500);              // wait for a second
 }

if( WiFi.status() != WL_CONNECTED)
{
 digitalWrite(12, HIGH); // turn the LED on (HIGH is the voltage level)
 Serial.println ("    hi"); 
 delay(500);              // wait for a second
 digitalWrite(12, LOW); // turn the LED off by making the voltage LOW
  Serial.println ("    low"); 
 delay(500);              // wait for a second
 }



 
 }
