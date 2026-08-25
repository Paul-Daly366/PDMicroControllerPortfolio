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

// Button Definitions
#define SWLEFT 11
#define SWRIGHT 13

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  // Wait for display
  delay(500);

  // More init
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
}

void loop() {
  if(digitalRead(SWLEFT)){
    display.drawPixel(random(0,127), random(0,63), SSD1306_WHITE);
    display.display();
    while(digitalRead(SWLEFT)){}
  }
  if(digitalRead(SWRIGHT)){
    display.clearDisplay();
    display.display();
    while(digitalRead(SWRIGHT)){}
  }
  delay(1);
}