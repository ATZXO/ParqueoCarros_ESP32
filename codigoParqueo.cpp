#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <ESP32Servo.h> 

Servo myservo;
int sensorEntrada = 19;
int sensorSalida = 18;
int lcdColumns = 16;
int lcdRows = 2;
int espaciosDisponibles = 4; 
int bandera1 = 0; 
int bandera2 = 0;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  pinMode(sensorEntrada, INPUT);
  pinMode(sensorSalida, INPUT);
  myservo.attach(4);
  myservo.write(100);
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("BIENVENIDO");
  lcd.setCursor(0, 1);
  lcd.print("Disponible:");
  lcd.print(espaciosDisponibles);
  lcd.clear();  
  delay(2000);
  Serial.begin(9600);
}

void loop(){

  const int entrada = digitalRead(sensorEntrada);
  const int salida = digitalRead(sensorSalida);

  if(entrada == 1 && bandera1 == 0){
    if(espaciosDisponibles > 0){ 
      bandera1 = 1;
      if(bandera2 == 0){
        myservo.write(0);
        espaciosDisponibles -= 1;
      }
    }else{
      lcd.setCursor(0, 0);
      lcd.print("LO SENTIMOS");
      lcd.setCursor(0, 1);
      lcd.print("Ocupado");
      delay(3000);
      lcd.clear();
    }
  }

  if(salida == 1 && bandera2 == 0){
    bandera2 = 1;
    if(bandera1 == 0){
      myservo.write(0);
      espaciosDisponibles += 1; 
    }
  }

  if(bandera1==1 && bandera2==1){
    delay(5000);
    myservo.write(100);
    bandera1=0;
    bandera2=0;
  }

  Serial.print("Pir:");
  Serial.print(entrada);
  Serial.println(salida);

  Serial.print("Banderas:");
  Serial.print(bandera1);
  Serial.println(bandera2);

  lcd.setCursor(0, 0);
  lcd.print("BIENVENIDO");
  lcd.setCursor(0, 1);
  lcd.print("Disponible:");
  lcd.print(espaciosDisponibles); 
}