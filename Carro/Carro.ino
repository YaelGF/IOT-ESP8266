
#include <SoftwareSerial.h>
#include <Servo.h>


// MOTOR 1.

int Motor1A = 5;
int Motor1B = 4;

// MOTOR 2.

int Motor2A = 0;
int Motor2B = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode( Motor1A, OUTPUT );
  pinMode( Motor2A, OUTPUT );
  pinMode( Motor1B, OUTPUT );
  pinMode( Motor2B, OUTPUT );
  
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor1B, LOW );
  digitalWrite( Motor2B, LOW );

}
int flag1 = -1;
int flag2 = -1;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( Motor1A, HIGH);
  analogWrite( Motor1B, 0 );
  digitalWrite( Motor2A, HIGH);
  analogWrite( Motor2B, 0 );
  delay(500);
  digitalWrite( Motor1B, HIGH);
  analogWrite( Motor1A, 0 );
  digitalWrite( Motor2B, HIGH);
  analogWrite( Motor2A, 0 );
  delay(500);

}
