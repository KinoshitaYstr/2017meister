#define PIN_IN1  4
#define PIN_VREF 2 // PWM
 
void setup(){
  pinMode(PIN_IN1,OUTPUT); 
  ledcSetup(0, 490, 8);
  ledcAttachPin(PIN_VREF, 0);
  ledcWrite(0, 255);
}
 
void loop(){
    ledcWrite(0, 0);
    digitalWrite(PIN_IN1,HIGH);
    delay(5000);
    //digitalWrite(PIN_IN1,LOW);
    //delay(5000);
    ledcWrite(0, 100);
    digitalWrite(PIN_IN1,HIGH);
    delay(5000);
    //digitalWrite(PIN_IN1,LOW);
    //delay(5000);
    ledcWrite(0, 255);
    digitalWrite(PIN_IN1,HIGH);
    delay(5000);
    //digitalWrite(PIN_IN1,LOW);
    //delay(5000);
    
}
