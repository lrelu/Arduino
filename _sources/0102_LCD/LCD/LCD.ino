#include <LiquidCrystal_I2C.h>    // LCD Library
#include <Wire.h>                   // I2C Control Library

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int LED = 10;
int _i = 0;
bool _flag = true;

void setup() {
  // put your setup code here, to run once:
  lcd.init();

  lcd.backlight();
  lcd.print("Temperature:....");
  lcd.setCursor(0,1);
  lcd.print("Wating Sensor...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Control_LED();
}

void Control_LED(){
  // LED 점점 밝게 점점 어둡게
  analogWrite(LED, _i);
  
  if(_flag == true){
    _i++;
  }else{
    _i--;
  }

  if(_i >= 256){
    _flag = false;
    _i = 255;
  }

  if(_i < 0){
    _flag = true;
    _i = 0;
  }
  
  delay(4);
}
