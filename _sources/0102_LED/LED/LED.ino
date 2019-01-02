const int LED = 13;
const int LED1 = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  //digitalWrite(LED1, LOW);
  analogWrite(LED1, 5);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
