int Pecho = 5;
int Ptrig = 16;

float tiempo, distancia;

void setup() {
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios               
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);

}

void loop() {
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(4);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  tiempo = pulseIn(Pecho, HIGH);
  distancia = (tiempo/2)/29;  

  Serial.println(distancia);

  delay(200);
}
