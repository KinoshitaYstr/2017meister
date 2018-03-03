void setup() {
  pinMode(4, OUTPUT);
  pinMode(16,OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(16, HIGH);
  delay(2000);
  digitalWrite(4, LOW);
  digitalWrite(16, HIGH);
  delay(2000);
  digitalWrite(4, HIGH);
  digitalWrite(16, LOW);
  delay(2000);
}
