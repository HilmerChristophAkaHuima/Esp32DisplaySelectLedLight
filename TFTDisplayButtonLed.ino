/*  
 Made By Huima

 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define TFT_GREY 0x5AEB // New colour

const int LEDWhitePin = 25;
const int LEDBluePin = 26;
const int LEDRedPin = 27;

int LEDWhiteState = 0;
int LEDBlueState = 0;
int LEDRedState = 0;

const int PushBRight = 16;
const int PushBMid = 4;
const int PushBLeft = 5;

int PushBRightState = 0;
int PushBMidState = 0;
int PushBLeftState = 0;

unsigned long previousMillis = 0;

int registerSel = 0;
const int maxRegister = 3;

const long interval = 3000;

TFT_eSPI tft = TFT_eSPI();  // Invoke library

void paint(){ 
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_BLACK);  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  if(registerSel == 0){
    tft.setTextColor(TFT_WHITE, TFT_GREY);
  }else{
    tft.setTextColor(TFT_WHITE);
  }
  tft.setTextSize(1);
  tft.println("1. Blue");

  if(registerSel == 1){
    tft.setTextColor(TFT_WHITE, TFT_GREY);
  }else{
    tft.setTextColor(TFT_WHITE);
  }
  tft.println("2. White");

  
  if(registerSel == 2){
    tft.setTextColor(TFT_WHITE, TFT_GREY);
  }else{
    tft.setTextColor(TFT_WHITE);
  }
  tft.println("3. Red");
}

void setup(void) {
  Serial.begin(115200);
  pinMode(LEDWhitePin, OUTPUT);
  pinMode(LEDBluePin, OUTPUT);
  pinMode(LEDRedPin, OUTPUT);

  pinMode(PushBRight, INPUT);
  pinMode(PushBMid, INPUT);
  pinMode(PushBLeft, INPUT);
  
  tft.init();
  tft.setRotation(2);
  paint();
}


void loop() {
  unsigned long currentMillis = millis();
  
  int PBR = digitalRead(PushBRight);
  int PBM = digitalRead(PushBMid);
  int PBL = digitalRead(PushBLeft);

  if(PBL == HIGH || PBM == HIGH || PBR == HIGH){
    if(PBL == HIGH && PBL != PushBLeftState){
      if(registerSel == 0){
        registerSel = maxRegister-1;
      }else{
        registerSel = registerSel - 1;
      }
    } else {
      if(PBR == HIGH && PBR != PushBRightState){
        if(registerSel == maxRegister-1){
          registerSel = 0;
        }else{
          registerSel = registerSel + 1;
        }
      }else{
        if(PBM == HIGH && PBM != PushBRightState){
          switch(registerSel){
            case 0:
              LEDBlueState = !LEDBlueState;
              digitalWrite(LEDBluePin, LEDBlueState);
              break;
            case 1:
              LEDWhiteState = !LEDWhiteState;
              digitalWrite(LEDWhitePin, LEDWhiteState);
              break;
            case 2:
              LEDRedState = !LEDRedState
              digitalWrite(LEDRedPin, LEDRedState);
              break;
          }
        }
      }
    }
    paint();
    Serial.println(registerSel);
  }
    
  PushBRightState = PBR;
  PushBLeftState = PBL;
  PushBMidState = PBM;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    paint();
  }
}
