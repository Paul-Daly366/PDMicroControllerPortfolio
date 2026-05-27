// ~~ Binary Counter with 4 LEDs, incremented with a switch/timer ~~
#define LED1 7
#define LED2 8
#define LED3 9
#define LED4 10
#define SW1 6
#define DELAYTIME 10 //Debounce

void ledController(int counter){
  //Used state maps to find equations for if statements
  // ~~ LED 1 Controller ~~
  if(counter%2 != 0){ //If counter is odd, LED1 must be high
    digitalWrite(LED1,HIGH);
  }
  else{
    digitalWrite(LED1,LOW);
  }

  // ~~ LED 2 Controller ~~ (counter = 2n OR 2n+1, where n is odd)
  if(counter%2 == 0){ //Checks if counter is even
    if((counter/2)%2 == 1){ //Check if n is odd
      digitalWrite(LED2,HIGH);
    }
    else{ //n is not odd, go low
      digitalWrite(LED2,LOW);
    }
  }
  else if(counter%2 != 1){  //Counter is odd
    if(((counter - 1)/2)%2 == 1){ //Check if n is odd, remove 1 and divide by 2
      digitalWrite(LED2,HIGH);
    }
    else{
      digitalWrite(LED2,LOW);
    }
  }

  // ~~ LED 3 Controller ~~ (counter = (4n),(4n+1),(4n+2),(4n+3), where n is odd)
  if(counter%2 == 0){ //Check if counter is even
    if(counter%4 == 0){ //Check if counter is a multiple of 4
      if((counter/4)%2 == 1){ //Check if n is odd
        digitalWrite(LED3,HIGH);
      }
      else{
        digitalWrite(LED3,LOW);
      }
    }
  }
  else if(counter%2 == 1){ //Counter is odd
    int temp;
    temp = ((counter)%4); //Save remainder temporarily
    
    if(((counter-temp)/4)%2 == 1){ //Remove remainder (1,2,3), check if odd
      digitalWrite(LED3,HIGH);
    }
    else{
      digitalWrite(LED3,LOW);
    }
  }

  // ~~ LED 4 Controller ~~
  if(counter>7){ //ONLY WORKS WITH 4 BITS RIGHT NOW, correct algo ~(8n,8n+1 etc, while n=odd)
    digitalWrite(LED4, HIGH);
  }
  else{
    digitalWrite(LED4, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(SW1, INPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
}

void loop() {
  int counter = 0;

  while(1){
    if(digitalRead(SW1)){
      counter++;
      if(counter>15){
        counter=0;
      }
      while(digitalRead(SW1)){}
      Serial.print("Counter: ");
      Serial.println(counter);
    }
    ledController(counter);
    delay(DELAYTIME);
  }

}
