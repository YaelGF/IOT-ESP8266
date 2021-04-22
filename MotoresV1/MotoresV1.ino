#include <ESP8266WiFi.h>
 
const char* ssid = "IZZI-38CA";
const char* password = "8871B1CA38CA";

WiFiServer server(80);

//left
#define en1A 4

#define Motor1A 0
#define Motor1B 2

//right
#define en2A 13

#define Motor2A 12
#define Motor2B 14

//Led
#define r 15
#define g 5
#define b 16

//Sensor Ultrasonico

int Pecho = 5;
int Ptrig = 16;

int tiempo, distancia;


void setup() {
    Serial.begin(115200);
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT); 
  
    pinMode(en1A, OUTPUT);
    pinMode(Motor1A, OUTPUT);
    pinMode(Motor1B , OUTPUT);
  
    pinMode(en2A, OUTPUT);
    pinMode(Motor2A, OUTPUT);
    pinMode(Motor2B, OUTPUT);

    pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
    pinMode(Ptrig, OUTPUT);

    Serial.print("Connecting to Internet ");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
      }
      Serial.println("WiFi connected");
   
   /*-------- server started---------*/ 
    server.begin();
    Serial.println("Server started");
   
    /*------printing ip address--------*/
    Serial.print("IP Address of network: ");
    Serial.println(WiFi.localIP());
    Serial.print("Copy and paste the following URL: https://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  }
void loop() {
  
    
    digitalWrite(en1A, 1); // Send PWM signal to L298N Enable pin 
    digitalWrite(en2A, 1);
    WiFiClient client = server.available();    
    if (!client) 
    {
      return;
    }
  Serial.println("Waiting for new client");   
  while(!client.available())
  {
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(4);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
   
   
   if(request.indexOf("/UP") != -1){
    tiempo = pulseIn(Pecho, HIGH);
    distancia = (tiempo/2)/29;
    Serial.println(distancia);
    
    while(distancia > 14 ){
    
    if(distancia > 14 ){
    //UP
      digitalWrite(Motor1A, LOW);
      digitalWrite(Motor1B, HIGH);
  
      digitalWrite(Motor2A, LOW);
      digitalWrite(Motor2B, HIGH);
       }else{
      digitalWrite(Motor1A, LOW);
      digitalWrite(Motor1B, LOW);
  
      digitalWrite(Motor2A, LOW);
      digitalWrite(Motor2B, LOW);
      }
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
  
 
  
 if (request.indexOf("/DOWN") != -1)  
  {
    //DOWN
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    
    digitalWrite(Motor2A, HIGH);
    digitalWrite(Motor2B, LOW);
  }else if (request.indexOf("/RIGHT") != -1){

      //Right
    
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);

    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, HIGH);
  }else if (request.indexOf("/LEFT") != -1){
      //Left
    
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, HIGH);

    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
  }else if(request.indexOf("/STOP") != -1){
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    
    digitalWrite(Motor2A, LOW);
    digitalWrite(Motor2B, LOW);
    
  }
    
  

    client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=3.0, user-scalable=no\">");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<a href=\"/UP\"\"><button>Adelante</button></a>");
   client.println("<br><br>");
   client.println("<a href=\"/LEFT\"\"><button>Izquierda</button></a>");
   client.println("<a href=\"/RIGHT\"\"><button>Derecha</button></a>");
   
   client.println("<br><br>");
  client.println("<a href=\"/DOWN\"\"><button>Atras</button></a><br />");
  client.println("<a href=\"/STOP\"\"><button>Stop</button></a><br />");    
  client.print("</style>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  
}
void myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis()- myPrevMillis <= del);
}
