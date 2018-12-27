float h(float x, int y){
  return x + y;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  float x = 2.1;
  int y = 2;
  float z = h(x, y);

  Serial.println(z);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
