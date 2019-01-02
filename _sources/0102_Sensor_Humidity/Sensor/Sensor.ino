#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//온도습도센서 연결설정
int pin = 4;
DHT11 dht11(pin);

//워터센서 설정
int waterSensorPin = 0;
int WaterLED = 2;

//LED 설정
const int LED = 10;
int _i = 0;
bool _flag = true;

//시간별 처리
int timer = 0;

void setup() {
  // put your setup code here, to run once:

  // 통신속도 설정
  Serial.begin(9600);

  // Water 센서 설정
  pinMode(WaterLED, OUTPUT);
  digitalWrite(WaterLED, LOW);

  // LCD 셋업 (I2C 통신으로 진행)
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:

  // 1 millisecond 마다 water 센서 체크
  IsWater();

  // 4 millisecond 마다 LED 변화
  if (timer % 4 == 0){
    Control_LED();
  }

  // 10초마다 실행
  if (timer % 1000 == 0){
    Read_Sensor();
  }

  delay(10);
  // 시간별 함수 처리
  timer++;
  timer = (timer >= 100000) ? 0 : timer;
}

// 워터센서가 물에 빠진지 확인
void IsWater(){
  int value = analogRead(waterSensorPin);

  if (value > 100){
    digitalWrite(WaterLED, HIGH);
  }else{
    digitalWrite(WaterLED, LOW);
  }

  //Serial.print("Value of Water Sensor: ");
  //Serial.println(value);
}

// 온도, 습도 센서 읽어서 LCD에 출력
void Read_Sensor(){
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0)
  {
    lcd.clear();
    lcd.display();
    lcd.setCursor(0,0);
    lcd.print("TEMP:     ");
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("HUMIDITY: ");
    lcd.print(humi);
 
    Serial.print("temp: ");
    Serial.print(temp);
    Serial.print("humi: ");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    lcd.backlight();
    lcd.display();
    lcd.print("ERROR NO.: ");
    lcd.print(err);
  }
}

// LED 점점 밝게 점점 어둡게 
void Control_LED(){
  analogWrite(LED, _i);
  
  if(_flag == true){
    _i += 5;
  }else{
    _i -= 5;
  }

  if(_i >= 256){
    _flag = false;
    _i = 255;
  }

  if(_i < 0){
    _flag = true;
    _i = 0;
  }
}
