// ~~ Simple LED code ~~
#define LED 7
#define DELAYTIME 500

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
}

void loop() {
  digitalWrite(LED,!digitalRead(LED));
  delay(DELAYTIME);
}
