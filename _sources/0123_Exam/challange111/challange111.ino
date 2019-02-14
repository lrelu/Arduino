enum STATUS {OFF = 0, ON};

int const LED = 12;
volatile char _key_now;
volatile char _key_pre;
volatile STATUS _status;

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
}

void loop() {
}

void controlLED(){
  // 모드에 따른 제어
  if (_status == ON)
    digitalWrite(LED, HIGH);
  else if (_status == OFF)
    digitalWrite(LED, LOW);
}
