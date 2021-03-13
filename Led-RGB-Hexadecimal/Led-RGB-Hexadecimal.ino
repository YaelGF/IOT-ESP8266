#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

int pinRojo = 2;
int pinVerde = 4;
int pinAzul =  5;

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
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Led RGB", MQTT_QOS_1);

/*************************** Sketch Code ************************************/
int regla3(int valor){
  return valor * 1024/255;
}
void color (int R, int G, int B) {
  analogWrite(2, 1024-regla3(R));
  analogWrite(12,1024-regla3(G));
  analogWrite(14,1024-regla3(B));
}
String strToDecimal(String cadena){
  unsigned long SumaTotal= 0;
  unsigned long Pot = 0;
  unsigned long multiplo = 0;
  int z;

  cadena.toUpperCase();
  
  for (int x = cadena.length()-1;x>=0;x--){

      z = (cadena.length()-x-1);
      Pot = 1;
      for (int y =0;  y < z ; y++){
           Pot *= 16;
        }
      
      if (isDigit(cadena[x]))
         multiplo = int(cadena[x])-48;
      else // no es digito
         multiplo = int(cadena[x])-55;  


        SumaTotal += (Pot * multiplo);
  }
   return String(SumaTotal);
}
void strtochar(String hexa){
  String r = String(hexa[1])+String(hexa[2]);
  String g = String(hexa[3])+String(hexa[4]);
  String b = String(hexa[5])+String(hexa[6]);

  color(strToDecimal(r).toInt(),strToDecimal(g).toInt(),strToDecimal(b).toInt());
}
void setup() {

  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);

    
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



  mqtt.subscribe(&onoffbutton);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();


Adafruit_MQTT_Subscribe *subscription;

while(subscription = mqtt.readSubscription(5000)){
  if(subscription == &onoffbutton){
    Serial.print("Recibi: ");
    Serial.println((char*)onoffbutton.lastread);
    String hexa = (char*)onoffbutton.lastread;
    
    strtochar(hexa);
    
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
