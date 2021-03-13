//Declarar Constantes leds y sus respectivas salidas
const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;

void setup() {
  //Salidas de cada led
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
}

void loop() {
  //encendido del led1
  digitalWrite(LED1,HIGH);
  //tiempo encendido
  delay(1000);
  //apagado del led1
  digitalWrite(LED1,LOW);
  //encendido del led2
  digitalWrite(LED2,HIGH);
  //tiempo encendido
  delay(1000);
  //apagado del led2
  digitalWrite(LED2,LOW);
  //encendido del led3
  digitalWrite(LED3,HIGH);
  //tiempo encendido
  delay(1000);
  //apagado del led3
  digitalWrite(LED3,LOW);
  //encendido del led2
  digitalWrite(LED2,HIGH);
  //tiempo encendido
  delay(1000);
  //apagado del led2
  digitalWrite(LED2,LOW);
}
  
