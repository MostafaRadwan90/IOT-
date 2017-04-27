/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Vodafone101."
#define WLAN_PASS       "vodafone9090"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Mostafa_Radwan"
#define AIO_KEY         "569aa2588de54322adc71755a01d2fb4"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish led1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Led11");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led11 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led1");

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish led2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Led22");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led22 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led2");


// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish led3 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Led33");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led33 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led3");


// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish led4 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Led44");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led44 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led4");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode (13,OUTPUT);
    pinMode (12,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (2,OUTPUT);


// radwan modification 


  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&led11);
    mqtt.subscribe(&led22);
  mqtt.subscribe(&led33);
  mqtt.subscribe(&led44);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &led11) {
      Serial.print(F("Got led 11: "));
      Serial.println((char *)led11.lastread);
    uint16_t   num1= atoi ((char *)led11.lastread);
    digitalWrite (13,num1);

    uint16_t   num2= atoi ((char *)led22.lastread);
// radwan modifaction 

          Serial.println((char *)led11.lastread);

    if (num1==1 && num2==2) {
    digitalWrite (12,num2);
    }
    else {
      digitalWrite (12,LOW);
      }
    
    }

if (subscription == &led22) {
      Serial.print(F("Got 22: "));
      Serial.println((char *)led22.lastread);
    uint16_t   num2= atoi ((char *)led22.lastread);
// radwan modifaction 
    uint16_t   num1= atoi ((char *)led11.lastread);

          Serial.println((char *)led11.lastread);

    if (num1==1 && num2==2) {
    digitalWrite (12,num2);
    }
    else {
      digitalWrite (12,LOW);
      }
    
    }


    if (subscription == &led33) {
      Serial.print(F("Got 33: "));
      Serial.println((char *)led33.lastread);
    uint16_t   num3= atoi ((char *)led33.lastread);
    digitalWrite (5,num3);
    
    }

    if (subscription == &led44) {
      Serial.print(F("Got44 : "));
      Serial.println((char *)led44.lastread);
    uint16_t   num4= atoi ((char *)led44.lastread);
    digitalWrite (2,num4);
    
    }

    
    
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending leds val "));
  Serial.print(x);
  Serial.print("...");
  if (! led1.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK led1!"));
  }

  if (! led2.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK led2!"));
  }

  if (! led3.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK led3!"));
  }

  if (! led4.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK led4!"));
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
