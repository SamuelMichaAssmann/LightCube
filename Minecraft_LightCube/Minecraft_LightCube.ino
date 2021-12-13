#include <Adafruit_NeoPixel.h>

// NeoPixel
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// Button
int pushButton = 7;
int buttonState = 0;
int mode = 1;
uint16_t i, j;

//RFID
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
  pinMode(pushButton, INPUT); // make the pushbutton pin an input
  strip.begin(); // NeoPixel setup
  SPI.begin();
  mfrc522.PCD_Init();
}


void loop() {
  checkButton();
  checkRfid();
  
  if (mode == 0){
    colorWipe(strip.Color(0, 0, 0)); // Black (Coal)
  } else if (mode == 1){
    rainbow();
  } else if (mode == 2){
    colorWipe(strip.Color(255, 0, 0)); // Red (Redstone)
  } else if (mode == 3){
    colorWipe(strip.Color(7, 255, 7)); // Green (Emarald)
  } else if (mode == 4){
    colorWipe(strip.Color(0, 5, 255)); // Blue (Lapis)
  } else if (mode == 5){
    colorWipe(strip.Color(251, 196, 155)); // gray (Iron)
  } else if (mode == 6){
    colorWipe(strip.Color(255, 252, 16)); // yellow (Gold)
  } else if (mode == 7){
    colorWipe(strip.Color(104, 197, 230)); // lightblue (Diamond)
  }
  
  delay(100);
}


void checkButton() { 
  if (digitalRead(pushButton) == HIGH) {
    buttonState = 1;
  } else {
    if (buttonState == 1){
      mode = (mode+1)%8;
      buttonState = 0;
      i = 0;
    }
  }
}

void checkRfid(){
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }
  long code=0;
  for (byte i = 0; i < mfrc522.uid.size; i++){
    code=((code+mfrc522.uid.uidByte[i])*10);
  }
  if (code == 2088030){
    mode = 1;
    buttonState = 0;
    i = 0;
  } else if (code == 664090){
    mode = 7;
    buttonState = 0;
    i = 0;
  }
}


void colorWipe(uint32_t c) {
  if (i<strip.numPixels()){
    strip.setPixelColor(i, c);
    strip.show();
  }
  i++;
}


void rainbow() {
  j = (j+1)%256;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
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
