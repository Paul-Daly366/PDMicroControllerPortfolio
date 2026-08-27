#define BUZZER 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("Begin Buzzer Test");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(BUZZER, 1000);
  delay(1000);
  tone(BUZZER, 1500);
  delay(1000);
  noTone(BUZZER);
  delay(500);
}
