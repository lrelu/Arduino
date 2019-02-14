enum STATUS {ZERO = 0, HALF, FULL};

int const LED = 11;
int const BUTTON = 2;

volatile STATUS _status;

volatile int _cnt;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  pinMode(LED, OUTPUT);
  // LED 초기화
  digitalWrite(LED, LOW);
  // 인터럽트, 풀업저항으로 사용
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), controlLED, FALLING);
  
  // 카운터 초기화
  _cnt = 0;
}

void loop() {
  // 모드에 따른 제어
  if (_status == ZERO){
    // LED 끔
    digitalWrite(LED, LOW);
  }
  else if (_status == HALF){
    // loop 두번중 한번만 LED를 켬
    if (_cnt % 2 == 0)
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);
  }else if (_status == FULL){
    // LED를 계속 켬
    digitalWrite(LED, HIGH);
  }
  
  _cnt = (_cnt >= 10000) ? 1 : _cnt + 1; 
}

void controlLED(){
  _status = (_status >= 2) ? 0 : _status + 1;
}
