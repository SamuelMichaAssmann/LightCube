#include <Adafruit_NeoPixel.h>

// NeoPixel
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// Button
#define buttonPin   3
int buttonState = 0;
int mode = 0;

void setup() {
  // Button Setup
  pinMode(buttonPin, INPUT);

  // NeoPixel Setup
  strip.begin();
}

void loop() {
  if (mode == 0){
    colorWipe(strip.Color(0, 0, 0), 100, 0); // white
  }
  else if (mode == 1){
    rainbow(200);
  }
  else if (mode == 2){
    colorWipe(strip.Color(255, 0, 0), 100, 2); // Red
  }
  else if (mode == 3){
    colorWipe(strip.Color(0, 255, 0), 100, 3); // Green
  }
  else if (mode == 4){
    colorWipe(strip.Color(0, 0, 255), 100, 4); // Blue
  }
  else if (mode == 5){
    colorWipe(strip.Color(255, 255, 255), 100, 5); // white
  }
  
  
  
}

void colorWipe(uint32_t c, uint8_t wait, int color) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    checkButton(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  while (mode == 1){
    j = (j+1)%256;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      
    }
    strip.show();
    checkButton(wait);
  }
}

void checkButton(uint8_t wait) { 
  delay(wait);
  if (digitalRead(buttonPin) == HIGH) {
    mode = (mode+1)%6;
  }
  
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
