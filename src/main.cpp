/*
__   _____ ___ ___        Author: Vincent BESSON
 \ \ / /_ _| _ ) _ \      Release: 0.1
  \ V / | || _ \   /      Date: 2024
   \_/ |___|___/_|_\      Description: Smart IC Tester Enhanced DIP 14, DIP 16, D20, 74LSXX
                2022      Licence: Creative Commons
______________________

Release changelog:
  +20240204: Initial Release

*/ 

#include "Arduino.h"

//TFT
#include <Adafruit_GFX.h>    // Core graphics library
#include "../lib/Adafruit_TFTLCD/Adafruit_TFTLCD.h" // Hardware-specific library
#include <TouchScreen.h> //Touch Screen Library

#include "tft.h"
#include "common.h"
#include "sdcard.h"
#include "keypad.h"
#include "main.h"
#include "test_functions.h"
#include <SPI.h>

#include <ArduinoLog.h>

#define __AVR_ATmega2560__

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen  ts = TouchScreen(XP, YP, XM, YM, 300);

int  pin14[14] = {30, 32, 34, 36, 38, 40, 42, 43, 41, 39, 37, 35, 33, 31};
int  pin16[16] = {30, 32, 34, 36, 38, 40, 42, 44, 45, 43, 41, 39, 37, 35, 33, 31};
int  pin20[20] = {30, 32, 34, 36, 38, 40, 42, 44, 50,48,49,47,45, 43, 41, 39, 37, 35, 33, 31};

Adafruit_GFX_Button buttons[12];
//void(* resetFunc) (void) = 0;

int   screenStatus = 0;
int   lastStatus = 0;
int   pinCount = 0;
int  * pin;


void setup() {


  Serial.begin(9600);

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);    // Do not show loglevel, we will do this in the prefix

  delay( 1000 ); // power-up safety delay
  
  //TFT setup
  tft_init();
  tft.fillScreen(BLACK);
  execICTesting("test");


  /*
  int ic_h=50;
  int ic_x=60;
  int ic_y=70;

  int pin_w=15;
  int pin_h=15;
  int spc=10;
  int pin_rang_1=1;
  int num_pin=14;
  
  int ic_w=spc+(num_pin/2)*(spc+pin_w);

  // Encoche
  tft.drawCircle(ic_x+7,ic_y+ic_h/2,ic_h/4,WHITE); 
  tft.fillRect(ic_x-ic_h/4+7,ic_y,ic_h/4,ic_h,BLACK);
  tft.drawLine(ic_x,  ic_y+ic_h/4+1,  ic_x+7, ic_y+ic_h/4+1,WHITE);
  tft.drawLine(ic_x,  ic_y+3*ic_h/4,  ic_x+7, ic_y+3*ic_h/4,WHITE);

  tft.drawRoundRect(ic_x, ic_y,ic_w,ic_h,2, WHITE);
  int font_size=3;
  const char title[]="74LS74";
  int titleLen=strlen(title);
  tft.setTextColor(WHITE);  tft.setTextSize(font_size);
  tft.setCursor(ic_x+ic_w/2-(titleLen/2*(font_size*(5+1))), ic_y+3+ic_h/2-((7+1)*font_size/2));
  tft.println(title);

  for (int i=0;i<(num_pin/2);i++){
    tft.drawRoundRect(ic_x+spc+i*(pin_w+spc),ic_y-pin_h +1, pin_w, pin_h,2, WHITE);
    tft.drawRoundRect(ic_x+spc+i*(pin_w+spc),ic_y+ic_h-1, pin_w, pin_h,2, WHITE);
    
    tft.setTextColor(WHITE);  tft.setTextSize(1);

    tft.setCursor(ic_x+spc+i*(pin_w+spc)+(pin_w/3), ic_y+3+ic_h);
    tft.println(pin_rang_1);

    if ((num_pin+1)-pin_rang_1<10)
      tft.setCursor(ic_x+spc+i*(pin_w+spc)+(pin_w/3), ic_y-10);
    else
      tft.setCursor(ic_x+spc+i*(pin_w+spc)+2, ic_y-10);

    tft.println((num_pin+1)-pin_rang_1);

    pin_rang_1++;   

  }

  tft.setRotation(2);
  for (int j=0;j<(num_pin/2);j++){
    tft.setCursor(240-ic_y+(20+pin_h),ic_x+j*(pin_w+spc)+14);
    tft.println("GND");
    tft.setCursor(240-ic_y-ic_h-55,ic_x+j*(pin_w+spc)+14);
    tft.println("VCC");
  }
  tft.setRotation(3);
*/
/*
  for (int k=0;k<(num_pin/2);k++){
    tft.fillCircle(ic_x+spc+k*(pin_w+spc)+pin_w/2,ic_y-(pin_h+10),5,RED);
    tft.fillCircle(ic_x+spc+k*(pin_w+spc)+pin_w/2,ic_y+ic_h+(pin_h+10),5,GREEN);
    tft.fillRoundRect(ic_x+spc+k*(pin_w+spc),ic_y-(pin_h+16),pin_w,pin_h,2,YELLOW);
    tft.fillRoundRect(ic_x+spc+k*(pin_w+spc),ic_y+ic_h+(pin_h+1),pin_w,pin_h,2,YELLOW);
  }

  */
  //startScreen();
  //delay(2000);
  //modeScreen();



  /*
  tft.reset();
  uint16_t identifier = tft.readID();
  identifier=0x9341;
  tft.begin(identifier);
  Serial.println(testFillScreen());
  delay(500);
  */

  //SD Card Setup
  SD_init();

}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  return micros() - start;
}

void loop() {

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
 
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    Serial.println("Z: " + String(p.z) + " X: " + String(p.x) + " Y: " + String(p.y));
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());

    //Swapping for Set Rotation 3
   // p.x = p.x + p.y;
   // p.y = p.x - p.y;
   // p.x = p.x - p.y;
   int a=p.x;
    p.x=tft.width() - p.y;
    p.y=a;
    delay(10);
    //Serial.println("(" +  String(p.x) + " , " + String(p.y) + " , " + String(p.z) + ")");

    if (screenStatus == 0)
      screenStatus = 1;

    else if (screenStatus == 1)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("AUTO MODE");
        screenStatus = 2;
      }
      else if (buttons[1].contains(p.x, p.y))
      {
        Serial.println("MANUAL MODE");
        screenStatus = 3;
      }
    }
    else if (screenStatus == 2)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("14 Pin Selected");
        screenStatus = 21;
        pinCount = 14;
      }
      else if (buttons[1].contains(p.x, p.y))
      {
        Serial.println("16 Pin Selected");
        screenStatus = 21;
        pinCount = 16;
      }
    }
    else if (screenStatus == 3)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("Entering Keypad Mode");
        screenStatus = 30;
      }
    }
  }

  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);

  if (screenStatus != lastStatus)
  {
    switch (screenStatus)
    {
      case 0: startScreen();
        break;
      case 1: modeScreen();
        break;
      case 2: autoScreen();
        break;
      case 21: autoSearch(pinCount);
        break;
      case 3: manualScreen();
        break;
      case 30: String number = getIC();
        manualSearch(number);
        break;
    }
    lastStatus = screenStatus;
  }
  delay(5);
}

void getTouch()
{
  boolean status = false;
  while (1)
  {
    digitalWrite(13, HIGH);
    TSPoint q = ts.getPoint();
    digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (q.z > MINPRESSURE && q.z < MAXPRESSURE)
    {
      status = true;
      break;
    }
    delay(10);
  }

  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
}
