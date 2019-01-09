void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(A0));
  Serial.print("X: ");
  Serial.print(analogRead(A5));
  Serial.print(" | Y: ");
  Serial.print(analogRead(A4));
  Serial.print(" | Click: ");
  Serial.println(analogRead(A3));
  
  delay(100);
}
