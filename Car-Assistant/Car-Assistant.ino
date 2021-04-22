  
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "IZZI-38CA"
#define WLAN_PASS       "8871B1CA38CA"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "YaelGF"
#define AIO_KEY         "aio_tRzm97EILxB71e4IpnvkwWmyEjxo"


/************************* Car *********************************/

//left
#define en1A 4

#define Motor1A 0
#define Motor1B 2

//right
#define en2A 13

#define Motor2A 12
#define Motor2B 14

//Sensor Ultrasonico

int Pecho = 5;
int Ptrig = 16;

int tiempo, distancia;

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/



// Setup a feed called 'onoff' for subscribing to changes to the button
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Assistant-Car", MQTT_QOS_1);

/*************************** Sketch Code ************************************/



void setup() {
  
  pinMode(en1A, OUTPUT);
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B , OUTPUT);
  
  pinMode(en2A, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor2B, OUTPUT);

  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);

    
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
  digitalWrite(en1A, 1); // Send PWM signal to L298N Enable pin 
  digitalWrite(en2A, 1);
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();


Adafruit_MQTT_Subscribe *subscription;

while(subscription = mqtt.readSubscription(5000)){
  if(subscription == &onoffbutton){
    Serial.print("Recibi: ");
    String result = (char*)onoffbutton.lastread;
    Serial.println(result);

    digitalWrite(Ptrig, LOW);
    delayMicroseconds(4);
    digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
    delayMicroseconds(10);
    digitalWrite(Ptrig, LOW);
    
    tiempo = pulseIn(Pecho, HIGH);
    distancia = (tiempo/2)/29;
    
    if(result =="enfrente"){
    //UP
      while(distancia > 14 ){
      digitalWrite(Motor1A, LOW);
      digitalWrite(Motor1B, HIGH);
  
      digitalWrite(Motor2A, LOW);
      digitalWrite(Motor2B, HIGH);
      
      digitalWrite(Ptrig, LOW);
      delayMicroseconds(4);
      digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
      delayMicroseconds(10);
      digitalWrite(Ptrig, LOW);
      
      tiempo = pulseIn(Pecho, HIGH);
      distancia = (tiempo/2)/29;
      Serial.println(distancia);
      }
      digitalWrite(Motor1A, LOW);
      digitalWrite(Motor1B, LOW);
  
      digitalWrite(Motor2A, LOW);
      digitalWrite(Motor2B, LOW);
      
    }
  
 if (result == "atrás")  
  {
    //DOWN
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    
    digitalWrite(Motor2A, HIGH);
    digitalWrite(Motor2B, LOW);
  }if (result =="derecha"){

      //Right
    
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);

    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, HIGH);
  }if (result =="izquierda"){
      //Left
    
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, HIGH);

    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
  }if(result =="stop"){
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
    
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
