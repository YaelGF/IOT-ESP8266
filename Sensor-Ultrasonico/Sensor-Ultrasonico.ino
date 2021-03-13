//Declaracion de variables
int Pecho = 6;
int Ptrig = 7;
int LEDV = 13;
int LEDA = 12;
int LEDR = 11;

long duracion, distancia;   
 
void setup() { 
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios               
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(LEDV,OUTPUT);      // define el pin 13 como salida
  pinMode(LEDA,OUTPUT);      // define el pin 12 como salida
  pinMode(LEDR,OUTPUT);      // define el pin 11 como salida
  }
  
void loop() {
  
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
   if (distancia < 10 && distancia >= 1){
    
    Serial.print(distancia);               // envia el valor de la distancia por el puerto serial
    Serial.println("cm");                  
    digitalWrite(LEDR,HIGH);                //prende el led rojo
    digitalWrite(LEDA,LOW);                 //apaga el led amarillo
    digitalWrite(LEDV,LOW);                 //apaga el led verde
    
  }else if (distancia <= 20 && distancia >= 10){
    
    Serial.print(distancia);               // envia el valor de la distancia por el puerto serial
    Serial.println("cm");  
    digitalWrite(LEDA,HIGH);                //prende el led amarillo
    digitalWrite(LEDR,LOW);                 //apaga el led rojo
    digitalWrite(LEDV,LOW);                 //apaga el led verde
    
  }else if(distancia <= 30 && distancia > 20){
    
    Serial.print(distancia);              // envia el valor de la distancia por el puerto serial
    Serial.println("cm");  
    digitalWrite(LEDV,HIGH);              //prende el led verde
    digitalWrite(LEDR,LOW);               //apaga el led rojo
    digitalWrite(LEDA,LOW);               //apaga el led amarillo
    
  }else{
    
    Serial.print(distancia);              // envia el valor de la distancia por el puerto serial
    Serial.println("cm");  
    digitalWrite(LEDV,LOW);               //apaga el led verde
    digitalWrite(LEDR,LOW);               //apaga el led rojo
    digitalWrite(LEDA,LOW);               //apaga el led amarillo
    
  }
  delay(200);                            //descanso de 1 seg  
}
