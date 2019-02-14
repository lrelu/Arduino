#include <Servo.h>

enum STATUS {D0 = 0, D90, D180};

int const SERVO = 11;
int const BUTTON = 2;
Servo sv;

volatile STATUS _status;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  sv.attach(SERVO);
  // 인터럽트, 풀업저항으로 사용
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), runServo, FALLING);
}

void loop() {
}

void runServo(){
  _status = (_status >= 2) ? 0 : _status + 1; 
  
  // 모드에 따른 제어
  if (_status == D0)
    sv.write(10);
  else if (_status == D90)
    sv.write(80);
  else if (_status == D180)
    sv.write(160);
}
