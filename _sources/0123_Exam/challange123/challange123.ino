int const BUZZER = 11;
int const BUTTON = 2;
// 멜로디
const int _tones[] = {261, 294, 330, 349, 392, 440, 494, 523};
volatile int _clicked = 0;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  pinMode(BUZZER, OUTPUT);
  // 인터럽트, 풀업저항으로 사용
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), sound, FALLING);
  // 벨소리 초기화
  tone(BUZZER, 261, 1);
}

void loop() {
}

void sound(){
  
  tone(BUZZER, _tones[_clicked], 500);

  _clicked = (_clicked >= 8) ? 0 : _clicked + 1;
}
