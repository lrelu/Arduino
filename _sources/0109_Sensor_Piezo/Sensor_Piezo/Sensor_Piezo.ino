const int BUZZER = 10;
const int melody[8] = {262,294,330,349,393,440,494,523};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0;i <= 7; i++){
    tone(BUZZER, melody[i]);
    delay(500);
  }
  noTone(BUZZER);
}

void loop() {
  // put your main code here, to run repeatedly:

}
