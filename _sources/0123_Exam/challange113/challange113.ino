int const BUZZER = 11;
// 키값과 멜로디 결합
int const _scale[8][2] = {{97, 261}, {115, 294}, {100, 330}, {102, 349}, {103, 392}, {104, 440}, {106, 494}, {107, 523}};
volatile char _key_now;

void setup() {
  // 시리얼설정
  Serial.begin(9600);
  
  // 핀모드 설정
  pinMode(BUZZER, OUTPUT);
  //analogWrite(BUZZER, LOW);
  tone(BUZZER, 294, 1);
  Serial.println(sizeof(_scale));
}

void loop() {
  if(Serial.available()){
    // 키 입력
    _key_now = Serial.read();
    // 키값에 의한 부저 처리
    sound(_key_now);
  }
}

int getTone(int _key){
  // 스케일 배열의 사이즈 만큼 돌아서, 톤 값 리턴
  // 배열이 커지면 나중엔 해시를 만들어서 하는게 성능상 좋을것 같음
  for (int i = 0; i < sizeof(_scale) / sizeof(_scale[0]); i++){
    if (_key == _scale[i][0]){
      return _scale[i][1];
    }
  }

  // 배열속에 값이 없다면 에러코드 전달
  return -1;
}

void sound(char _key){
  int itone = getTone((int)_key);
  
  if (itone != -1){
    tone(BUZZER, itone, 500);
  }
}
