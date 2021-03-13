#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"


/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "IZZI-38CA"
#define WLAN_PASS       "8871B1CA38CA"
/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "YaelGF"
#define AIO_KEY         "aio_VXvK44qsD5Xl49oObOKjbaZArRw0"
/************* DHT11 Setup ********************************************/
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/************ Global State (you don't need to change this!) ******************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish (&mqtt, AIO_USERNAME "/feeds/temperature");

/*************************** Sketch Code ************************************/
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

unsigned long tiempo =0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
  Serial.println(F("Adafruit MQTT Temperature demo"));
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
}
uint32_t x=0;
void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.

  tiempo = millis();
  
  if(tiempo % 6000 == 0){
    MQTT_connect();

    float t = dht.readTemperature();
    float h = dht.readHumidity();
  
    Serial.println(F("\nTemperatura: "));
    Serial.print(t);
    Serial.println(F("\nHumedad: "));
    Serial.print(h);
  
    temperature.publish(t);

  }
 

  
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  tiempo = millis();
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
       mqtt.disconnect();  // wait 5 seconds
       if (tiempo % 5000 == 0){
         retries--;
         if (retries == 0) {
           // basically die and wait for WDT to reset me
           while (1);
         }
       }
       
  }
  Serial.println("MQTT Connected!");
}
