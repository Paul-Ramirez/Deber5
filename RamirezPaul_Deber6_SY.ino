/*
 * Deber#6
 * Autor: Ramirez Paul
 * Objetivo: realizar un reloj con alarma
 */
 #include<MsTimer2.h>
 #include<LiquidCrystal.h>

 LiquidCrystal lcd(13,12,11,10,9,8);

 const int btn1=7;
 const int btn2=6;
 const int led1=5;

 int segundos=0;
 int minutos=0;
 int horas=0;
 int almH;
 int almM;
 int on=0;
 int i=0;
 String datoHoras;
 String datoMin;
 
 

void setup() {
  lcd.begin(16,2);
  pinMode(btn1,INPUT);
  pinMode(btn2,INPUT);
  pinMode(led1,OUTPUT);
  MsTimer2::set(1000,reloj);
  MsTimer2::start();
  attachInterrupt(0,activacion,LOW);
}

void loop() {
//inicio programa cunado int0 esta en 1
  if(on==1){
    if(Serial.available()>0){//verifica el dato en la terminal
      datoHoras=Serial.readString();//lee el dato
      almH=datoHoras.toInt();//lo convierte a entero   
    }
    
  }
//acceso a funcion cuando int0 esta en 2
  if(on==2){
    if(Serial.available()>0){//verifica el dato en la terminal
      datoMin=Serial.readString();//lee el dato
      almM=datoMin.toInt();//lo convierte a entero
  }
  //alarma configurada
  if(almH==horas && almM==minutos){//si cumple la condicion de alarma=reloj 
    for(i=0;i<20;i++){//enciende el led simulando alarma
      digitalWrite(led1,HIGH);
      delay(200);
      digitalWrite(led1,LOW);
      delay(200);
    }
  }
}
}

//metodo para visualizar reloj
void reloj(){
  if(digitalRead(btn1)==LOW){//botn para configurar minutos
    if(minutos<59)
        minutos++;
        else 
        minutos=0;
  }
  if(digitalRead(btn2)==LOW){//boton para configurar hotas
        if(horas<23) 
        horas++;
        else
        horas=0;
      }
//sistema de reloj
  if(segundos<59){
    segundos++;
   
  }else{
    segundos=0;
    if(minutos<59){
      minutos++;
      
    }else{
      minutos=0;
      if(horas<23){
        horas++;
      }else{
        horas=0;
      }
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(horas)+String(":")+String(minutos)+String(":")+String(segundos));
}

//metodo para int0
void activacion(){
//validacion int0
  switch(on){
    case 0:
    Serial.println("Bienvenido");
    Serial.println("Configuracion de Alamra");
    Serial.println("Ingrese horas: ");
    on++;
    break;
    case 1:
    Serial.println(" ");
    Serial.println("Ingrese minutos: ");
    on++;
    break;
    case 2:
    Serial.println("Iniciar nueva configuracion");
    on=0;
    almH=0;
    almM=0;
    i=0;
    break;
  }
}
