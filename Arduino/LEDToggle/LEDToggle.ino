// ~~ Simple LED code ~~
#define LED 7
#define DELAYTIME 500

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}

void loop() {
  digitalWrite(LED,!digitalRead(LED));
  delay(DELAYTIME);
}
