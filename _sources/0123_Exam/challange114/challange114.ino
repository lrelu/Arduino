#include <Servo.h>

enum STATUS {D0 = 0, D90, D180};

int const SERVO = 11;
Servo sv;

volatile char _key_now;
volatile char _key_pre;
volatile STATUS _status;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  sv.attach(SERVO);
}

void loop() {
  // put your main code here,z to run repeatedly:
  // 키 입력
  _key_now = Serial.read();

  // 키값에 의한 모드 변경
  if (_key_now != _key_pre){
    if (_key_now == 'q')
      _status = D0;
    else if (_key_now == 'w')
      _status = D90;
    else if (_key_now == 'e')
      _status = D180;
  }

  // 모드에 따른 제어
  if (_status == D0)
    sv.write(0);
  else if (_status == D90)
    sv.write(90);
  else if (_status == D180)
    sv.write(180);
    
  _key_pre = _key_now;
}
