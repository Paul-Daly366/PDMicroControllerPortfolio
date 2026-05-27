// ~~ LED with a Switch ~~
#define LED 7
#define SW1 8
#define DELAYTIME 10 //Debounce

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(SW1, INPUT);
  digitalWrite(LED,LOW);
}

void loop() {
  if(digitalRead(SW1)){
    digitalWrite(LED,!digitalRead(LED));
    while(digitalRead(SW1)){}
  }
  delay(DELAYTIME);
}
