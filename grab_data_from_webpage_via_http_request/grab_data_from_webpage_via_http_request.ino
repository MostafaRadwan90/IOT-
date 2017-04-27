#include <ESP8266WiFi.h>
#include <ESP8266WiFiScan.h>
#include <WiFiServer.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <WiFiClientSecure.h>

#include <ESP8266WiFi.h>

#include <WiFiClient.h>
// Credentials
char ssid[] = "Bocelli";     //  your network SSID (name)
char pass[] = "66666222";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status 

// Server
char server[] = "www.google.com";

// WiFi client
WiFiClient client;

void setup() {
  
  // Initialize serial
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }



  // Attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");

  // Connect to server
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    
    // Make a request:
    client.println("GET / HTTP/1.1");
    client.println("Host: www.example.com");
    client.println("Connection: close");
    client.println();
  }
}

#include <ESP8266WiFi.h>

void loop() {
  
  // Read data
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // Stop the connection
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

