

/*
 * Deber #5
 * Autor: Ramirez Paul
 * Objetivo: Realizar el giro de motor mediante interrupciones y comunicacion serial.
 * Fecha: 07/12/2020
 */
 #include <Servo.h>
 Servo servo1;
 int giro;
 int on=0;//int 0
 int cont;//int 1
 int i;//aux
 int j=0;//aux
 int conversor1;
 String dato;
void setup() {
  servo1.attach(6);
  Serial.begin(9600);
  attachInterrupt(0,activacion,LOW);
  attachInterrupt(1,contador,LOW);

}

void loop() {
  if(on==2){//aqui es donde ya está configurado el dato para iniciar
    if(Serial.available()>0){//verifica el dato en la terminal virtual
        dato=Serial.readString();
        giro=dato.toInt();
      }
      conversor1=analogRead(0);
      conversor1=map(conversor1,0,1023,0,giro);//escala para el giro del servo
      //verificar si se cumple el rango de giro
      if(giro>=0 && giro<=180){
        servo1.write(giro);
      }else{
        Serial.println("Valor incorrecto, inicie nuevamente");
        on=0;//vuelve a inciar el sistema con int0
      }
      
//    if(cont==1){
//      if(Serial.available()>0){
//        dato=Serial.readString();
//        giro=dato.toInt();
//      }
//      conversor1=analogRead(0);
//      conversor1=map(conversor1,0,1023,0,giro);
//      servo1.write(giro);
//    }
  }

}

void activacion(){
  //inicio del sistema int0
  switch(on){
    case 0:
    Serial.println("Inicio del sistema");
    Serial.println("Ingrese un valor entre 0 y 180");
    on++;
    break;
    case 1:
    Serial.println(" ");
    Serial.println("Girar Motor");
    on++;
    break;
    case 2:
    Serial.println("Fin de Programa");
    cont=0;
    i=0;
    j=0;
    on=0;
    break;
  }
}

//int1
void contador(){
 
}
