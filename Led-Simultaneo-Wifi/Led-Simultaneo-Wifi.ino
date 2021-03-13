#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


// Lamp pin

const int led1 = 16;
const int led2 = 5;
const int led3 = 4;


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "IZZI-38CA"
#define WLAN_PASS       "8871B1CA38CA"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "YaelGF"
#define AIO_KEY         "aio_VXvK44qsD5Xl49oObOKjbaZArRw0"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/



// Setup a feed called 'onoff' for subscribing to changes to the button
Adafruit_MQTT_Subscribe ledSimultane = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Led Simultaneo", MQTT_QOS_1);

/*************************** Sketch Code ************************************/



void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT"));

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



  mqtt.subscribe(&ledSimultane);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();


Adafruit_MQTT_Subscribe *subscription;

while(subscription = mqtt.readSubscription(5000)){
  if(subscription == &ledSimultane){
    Serial.print("Recibi: ");
    Serial.println((char*)ledSimultane.lastread);
    if(strcmp((char*)ledSimultane.lastread,"Encendido")==0){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"Apagado")==0){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"ON")==0){
    digitalWrite(led1,HIGH);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"OFF")==0){
    digitalWrite(led1,LOW);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"1")==0){
    digitalWrite(led2,HIGH);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"0")==0){
    digitalWrite(led2,LOW);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"Lumos")==0){
    digitalWrite(led3,HIGH);
    
   }
   if(strcmp((char*)ledSimultane.lastread,"Nox")==0){
    digitalWrite(led3,LOW);
    
   }
    
  }
}

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(500);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
 // if(! mqtt.ping()) {
 //   mqtt.disconnect();
 // }
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
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
