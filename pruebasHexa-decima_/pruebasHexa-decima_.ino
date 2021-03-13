void setup() {
  // Definimos los pins
  pinMode(2, OUTPUT); // Red: D4
  pinMode(4, OUTPUT); // Green: D2
  pinMode(5, OUTPUT); // Blue: D1
  Serial.begin(115200);
}

void color (int R, int G, int B) {
  
   
  analogWrite(2, 1024-regla3(R));
  analogWrite(12,1024-regla3(G));
  analogWrite(14,1024-regla3(B));

  Serial.println(1024-regla3(R));
  Serial.println(1024-regla3(G));
  Serial.println(1024-regla3(B));
}

int regla3(int valor){
  return valor * 1024/255;
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
  String r = String(hexa[0])+String(hexa[1]);
  String g = String(hexa[2])+String(hexa[3]);
  String b = String(hexa[4])+String(hexa[5]);

  color(strToDecimal(r).toInt(),strToDecimal(g).toInt(),strToDecimal(b).toInt());
}
 
void loop() {

  String hexa= "8f09ec";
  
  //color(strToDecimal(String(hexa[0],hexa[1])), strToDecimal(String(hexa[2],hexa[3])), strToDecimal(String(hexa[4],hexa[5])));
  
  strtochar(hexa);
  delay(2000);
}
