#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Definitions and Initialise
#define BUZ 3
#define SCREEN_WIDTH 128 // 0 - 127   -->
#define SCREEN_HEIGHT 64 // 0 - 63     V
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global Variables
uint8_t t = 0; // Time variable for controlling display with a framerate
uint8_t pX = 32; // Player x position
uint8_t pY = 50; // Player y position
uint8_t eX = 32; // Enemy x position
uint8_t eY = 8; // Enemy Y position
uint8_t score = 0;
uint8_t space_pressed = 0;
uint8_t enemy_active = 0;
uint8_t bullet_active = 0;
uint8_t bX = 50; // Bullet x position
uint8_t bY = 32; // Bullet y position

// Button Definitions
#define SWL 11
#define SWM 12
#define SWR 13

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  // Wait for display
  delay(500);

  // More init, setting screen voltage and connecting via I2C
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.cp437(true); //Fixes bug in library

  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(200);
  
  // TITLE SCREEN
  while(1){
    if(digitalRead(SWM)){
      titleScreen1();
      t = 0;
      delay(50);
      tone(BUZ,700);
      delay(100);
      tone(BUZ,1000);
      delay(150);
      noTone(BUZ);
      delay(700);
      break;
    }
    if(t == 30){
      titleScreen1();
    }
    if(t == 60){
      titleScreen2();
      t=0;
    }
    delay(16);
    t++;
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // Handle Controls
  if(digitalRead(SWL) && pX > (0 + 2)){ // 0: The edge, + 2: 2 for the border
    pX = pX - 2;
  }
  if(digitalRead(SWM) && space_pressed == 0){
    score++;
    space_pressed = 1;
    bullet_active = 1;
    bX = pX + 5;
    bY = pY;
  }
  if(digitalRead(SWM) != 1){
    space_pressed = 0;
  }
  if(digitalRead(SWR) && pX < (128 - 14)){ //128: The edge, -13: 12 for the sprite, 2 for the border
    pX = pX + 2;
  }
  // Handle Enemy Spawning

  // Handle Enemy/Bullet Movement
  if(t%2 == 0){
    eY = eY + 2;
    bY = bY - 2;
    if (eY > 70 && eY < 230){
      enemy_active = 0;
    }
    if (bY > 64 && bY < 240){
      bullet_active = 0;
    }
  }
  if(t%30 == 0){
    Serial.println("Enemy status: "); // DEBUG
    Serial.println(enemy_active); // DEBUG
    Serial.println("Bullet status: "); // DEBUG
    Serial.println(bullet_active); // DEBUG
    if(enemy_active == 0){
      enemy_active = 1;
      eX = random(8,120);
      eY = 250;
    }
  }
  // Handle Collision

  // Handle Display
  // Start by clearing display
  display.clearDisplay();
  // Border
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  // Player
  display.drawRoundRect(pX, pY, 11,6,2, SSD1306_WHITE);
  //display.drawRoundRect(pX+3,pY-2,4,4,3,SSD1306_WHITE);
  display.drawCircle(pX+5, pY, 2, SSD1306_WHITE);
  // Enemy
  if(enemy_active == 1){
    display.drawCircle(eX, eY, 4, SSD1306_WHITE);
  }
  // Bullet
  if(bullet_active == 1){
    display.drawFastVLine(bX, bY, 4, SSD1306_WHITE);
  }
  // Score
  display.setCursor(4,4);
  display.print(score);
  // Display function
  display.display();

  // Framerate Control
  delay(16);
  t++;
  if(t >= 60){
    t = 0;
  }
}

void titleScreen1(void){
display.clearDisplay();
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 16);
  display.write("Stellar Conquerors");
  display.setTextSize(1);
  display.setCursor(8,32);
  display.write("Press Middle Button");
  display.setCursor(38,42);
  display.write("to Start!");
  display.display();
}
void titleScreen2(void){
display.clearDisplay();
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 16);
  display.write("Stellar Conquerors");
  display.display();
}