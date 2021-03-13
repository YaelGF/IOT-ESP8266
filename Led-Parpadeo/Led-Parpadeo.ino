// Práctica encender y apagar un LED
const int LED=13;
void setup()
{
  pinMode(LED,OUTPUT);
}
void loop()
{
  //on
  digitalWrite(LED,HIGH);
  delay(1000);
  //off
  digitalWrite(LED,LOW);
  delay(1000);
}
