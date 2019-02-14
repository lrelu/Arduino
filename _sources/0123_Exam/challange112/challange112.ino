enum STATUS {ZERO = 0, HALF, FULL};

int const LED = 11;
volatile char _key_now;
volatile char _key_pre;
volatile STATUS _status;

volatile int _cnt;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  pinMode(LED, OUTPUT);
  // LED 초기화
  digitalWrite(LED, LOW);

  // 카운터 초기화
  _cnt = 0;
}

void loop() {
  // put your main code here,z to run repeatedly:
  // 키 입력
  _key_now = Serial.read();

  // 키값에 의한 모드 변경
  if (_key_now != _key_pre){
    if (_key_now == '0')
      _status = ZERO;
    else if (_key_now == '5')
      _status = HALF;
    else if (_key_now == 't')
      _status = FULL;
  }

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
    

  _key_pre = _key_now;
  _cnt = (_cnt >= 10000) ? 1 : _cnt + 1; 
}
