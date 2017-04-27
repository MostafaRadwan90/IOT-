#include <ESP8266WiFi.h>
const char* ssid = "Makan's Space 1";
const char* password = "makan0123456789";
int count=0;    // i want to add time getting number of calling

// adding analog read
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor




void setup() {
  Serial.begin(115200); 
  Serial.println(); 
  initWifi();

}

void loop() {
  Serial.println(getTime(count));  // i am the one who pass count to function
  delay(5000);
  count++;
    // add by radwan
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
}
  
String getTime(int count) {
  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                theDate+="   trial is  "; // i am the one who concate the strings :) )) 
                theDate+=count;
                 Serial.println (sizeof(theDate)); // one who ruterns size :))

                return theDate;
              }
            }
          }
        }
      }
    }
  }
}

void initWifi() {
   Serial.print("Connecting to ");
   Serial.print(ssid);
      WiFi.begin(ssid, password);
  

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
} // See more at: http://www.esp8266.com/viewtopic.php?f=29&t=6007&start=4#sthash.KUppBemB.dpuf
