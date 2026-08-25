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
#define SCREEN_WIDTH 128 // 0 - 127   -->
#define SCREEN_HEIGHT 64 // 0 - 63     V
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global Variables
uint8_t t = 0; // Time variable for controlling display with a framerate
uint8_t pX = 32; // Player x position, initial = 
uint8_t pY = 50; // Player y position, initial =

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
      delay(1000);
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
  if(digitalRead(SWL) && pX > (0 + 6)){ // If pX isnt at the border (radius + 2)
    pX = pX - 2;
  }
  if(digitalRead(SWM)){
    pY = pY;
  }
  if(digitalRead(SWR) && pX < (128 - 7)){ // If pX isnt at the border (radius + 3)
    pX = pX + 2;
  }
  
  // Handle Display
  // Start by clearing display
  display.clearDisplay();
  display.drawRect(0,0,128,64,SSD1306_WHITE);
  display.drawCircle(pX, pY, 4, SSD1306_WHITE);

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
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 8);
  display.write("Game Test");
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
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 8);
  display.write("Game Test");
  display.display();
}