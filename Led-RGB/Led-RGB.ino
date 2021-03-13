
void setup() {
  // Definimos los pins
  pinMode(2, OUTPUT); // Red: D4
  pinMode(4, OUTPUT); // Green: D2
  pinMode(5, OUTPUT); // Blue: D1
}

void color (int R, int G, int B) {
  analogWrite(2, R);
  analogWrite(4, G);
  analogWrite(5, B);
}
void loop() {
  color(0, 1023, 1023);
}
