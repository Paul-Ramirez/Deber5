/*
 * Deber #7
 * Autor: Ramirez Paul
 * Objetivo: Validar y actualizar contraseña
 * Fecha: 09/12/2020
 *
 */

#include<EEPROM.h>
int claveIngreso;//nueva contraseña de ingreso
int clave=4563;//contraseña incial
int actPass;//contraseña actualizada
int inicio=0;//int0
String dato;//dato ingresado por serial


void setup() {
  EEPROM.get(0,claveIngreso);
  if(claveIngreso!=clave && claveIngreso>0){
    clave=claveIngreso;
  }
  attachInterrupt(0,sistema,LOW);//int 0
  Serial.begin(9600);
  

}

void loop() {
  //inicia el programa cuando int0 esté en 1
  if(inicio==1){
    if(Serial.available()>0){//verifica el dato de la terminal
      dato=Serial.readString();//lee el dato de la terminal
      actPass=dato.toInt();//convierte a entero el string
    }
    claveIngreso=actPass;//iguala a la clave ingresada por serial
  }

  if(inicio==2){//inicio segunda accion
    if(claveIngreso==clave){//verifica que la clave ingresada por serial sea igual a la predeterminada
      Serial.println("Contraseña Correcta!");
      delay(5000);
    }else{
      Serial.println("Contraseña Incorrecta!");
      delay(5000);
    }
  }//fin segunda accion

  //inicio 3era accion
  if(inicio==3){
    if(Serial.available()>0){//verifica el dato en la terminal
      dato=Serial.readString();//lee el dato
      actPass=dato.toInt();//lo convierte a entero y lo alamcena en otra variable
      
    }
    claveIngreso=actPass;//iguala la clave de ingreso a la clave ingresada por serial
    EEPROM.update(0,claveIngreso);//actualiza la escritura en la eeprom con la nueva contraseña
    clave=claveIngreso;//cambia la clave predeterminada por la nueva introducida
  }//fin tercera accion

}

//metodo int0
void sistema(){
  switch(inicio){
    case 0:
    Serial.println("BIENVENIDO");
    Serial.println("Ingrese contraseña:");
    inicio++;
    break;
    case 1:
    Serial.println(" ");
    Serial.println("ACEPTAR");
    inicio++;
    break;
    case 2: 
    Serial.println("Actualizar contraseña: ");
    inicio++;
    break;
    case 3:
    Serial.println(" ");
    Serial.println("Contraseña actualizada con exito!");
    inicio++;
    break;
    case 4:
    Serial.println("Programa Finalizado");
    Serial.println(" ");
    inicio=0;
    claveIngreso=0;
    actPass=0;
    break;
    
  }
  
}
