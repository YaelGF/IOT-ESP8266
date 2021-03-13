void setup() {
  pinMode(2, OUTPUT);//r
  pinMode(14, OUTPUT);//b
  pinMode(12, OUTPUT);//g

}

void loop() {
  delay(2000);
  //amarillo
  analogWrite(2,0);
  analogWrite(14,10);
  analogWrite(12,255);
}
