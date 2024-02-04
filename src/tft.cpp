#include "Arduino.h"
#include "common.h"
#include "main.h"
#include "tft.h"
#include <ArduinoLog.h>

#include <Adafruit_TFTLCD.h> // Hardware-specific library


void tft_init(){
  tft.reset();
  uint16_t identifier = tft.readID();
  identifier=0x9341;
  
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }

  tft.begin(identifier);
  
  tft.setRotation(3);
  screenStatus = 0;
  
}

int ic_w=0;
int ic_x=0;

void drawICLabel(char * title){

  int ic_h=50;
  //int ic_x=60;
  int ic_y=70;

  int font_size=3;
  int titleLen=strlen(title);
  tft.setTextColor(WHITE); 
   tft.setTextSize(font_size);
  tft.setCursor(ic_x+ic_w/2-(titleLen/2*(font_size*(5+1))), ic_y+3+ic_h/2-((7+1)*font_size/2));
  tft.println(title);

}

void drawBottomLine(char * txt,int line,int font_size, uint16_t color){

  int ic_h=50;
  int ic_y=70;

  int titleLen=strlen(txt);
  tft.setTextColor(color); 
  tft.setTextSize(font_size);
  tft.setCursor(ic_x+ic_w/2-(titleLen/2*(font_size*(5+1))), ic_y+ic_h+40+(20*line));
  tft.println(txt);

}

void drawProgressBar(int start,int end,int pos,uint16_t color,int clear){

// avoid divide by zero error
if (end==start)
  return;

int range=end-start;
int spos=pos-start;
int pg_x=(spos*ic_w)/range;
int pg_percent=(spos*100)/range;

int pg_h=25;
int ic_y=70;
int ic_h=50;

if (clear==1){
  tft.fillRect(ic_x-1,ic_y+ic_h+50+10-1,ic_w+1,pg_h+1,BLACK);
  return;
}

tft.fillRect(ic_x,ic_y+ic_h+50+10,ic_w,pg_h,BLACK);
tft.fillRect(ic_x,ic_y+ic_h+50+10,pg_x,pg_h,color);
tft.drawRect(ic_x-1,ic_y+ic_h+50+10-1,ic_w+1,pg_h+1,WHITE);

char txt[12];
sprintf(txt,"%d%%",pg_percent);
int slen=strlen(txt);

tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.setCursor(160-(slen*6*2)/2,ic_y+ic_h+50+10+pg_h/2-8*2/2);
tft.println(txt);

return;

}

void drawRecPintStatus(int pin, int totalpin,uint16_t color){

  int ic_h=50;
  
  int ic_y=70;

  int pin_w=15;
  int pin_h=15;
  int spc=10;

  int k=pin-1;
  if (pin>(totalpin/2)){
     tft.fillRoundRect(ic_x+spc+(totalpin-pin)*(pin_w+spc)+1,ic_y-(pin_h+14),pin_w-2,pin_h-2,2,color);
  }else{
    tft.fillRoundRect(ic_x+spc+k*(pin_w+spc)+1,ic_y+ic_h+(pin_h+1),pin_w-2,pin_h-2,2,color);
  }

}

void drawCirclePintStatus(int pin, int totalpin,uint16_t color){
  
  int ic_h=50;
  //int ic_x=60;
  int ic_y=70;

  int pin_w=15;
  int pin_h=15;
  int spc=10;

  int k=pin-1;
  if (pin>(totalpin/2)){
    tft.fillCircle(ic_x+spc+(totalpin-pin)*(pin_w+spc)+pin_w/2,ic_y-(pin_h+6+1),5,color);
  }else{
    tft.fillCircle(ic_x+spc+k*(pin_w+spc)+pin_w/2,ic_y+ic_h+(pin_h+6),5,color);
  }
}

void drawPinLabel(int pin,int totalpin,char * txt){
  
  int ic_h=50;
  //int ic_x=60;
  int ic_y=70;

  int pin_w=15;
  int pin_h=15;
  int spc=10;
  int activLow=0;

  tft.setRotation(2);
  tft.setTextSize(1);
  int j=pin-1;
  int ilen=strlen(txt);
  if (txt[0]=='/'){
    txt=txt+1;
    ilen--;
    activLow=1;

  }
    
  if (pin>totalpin/2){
    tft.setCursor(240-ic_y+(15+pin_h),  ic_x+(totalpin-pin)*(pin_w+spc)+14);
    tft.println(txt);
    if (activLow==1)
      tft.drawLine(240-ic_y+(15+pin_h),ic_x+(totalpin-pin)*(pin_w+spc)+14-3,240-ic_y+(15+pin_h)+ilen*5,ic_x+(totalpin-pin)*(pin_w+spc)+14-3,WHITE);
  }else{
    tft.setCursor(240-ic_y-ic_h-(30+6*ilen),  ic_x+j*(pin_w+spc)+14);
    tft.println(txt);
    if (activLow==1)
      tft.drawLine(240-ic_y-ic_h-(30+6*ilen),ic_x+j*(pin_w+spc)+14-3,240-ic_y-ic_h-(30+6*ilen)+ilen*5,ic_x+j*(pin_w+spc)+14-3,WHITE);
  }
    
  tft.setRotation(3);

}


void drawIC(int totalpin){
  
  int ic_h=50;
  //int ic_x=60;
  int ic_y=70;

  int pin_w=15;
  int pin_h=15;
  int spc=10;
  int pin_rang_1=1;
  
  ic_w=spc+(totalpin/2)*(spc+pin_w);
  ic_x=(320-ic_w)/2;

  // Encoche
  tft.drawCircle(ic_x+7,ic_y+ic_h/2,ic_h/4,WHITE); 
  tft.fillRect(ic_x-ic_h/4+7,ic_y,ic_h/4,ic_h,BLACK);
  tft.drawLine(ic_x,  ic_y+ic_h/4+1,  ic_x+7, ic_y+ic_h/4+1,WHITE);
  tft.drawLine(ic_x,  ic_y+3*ic_h/4,  ic_x+7, ic_y+3*ic_h/4,WHITE);

  tft.drawRoundRect(ic_x, ic_y,ic_w,ic_h,2, WHITE);


  for (int i=0;i<(totalpin/2);i++){
    tft.drawRoundRect(ic_x+spc+i*(pin_w+spc),ic_y-pin_h +1, pin_w, pin_h,2, WHITE);
    tft.drawRoundRect(ic_x+spc+i*(pin_w+spc),ic_y+ic_h-1, pin_w, pin_h,2, WHITE);
    
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);

    tft.setCursor(ic_x+spc+i*(pin_w+spc)+(pin_w/3), ic_y+3+ic_h);
    tft.println(pin_rang_1);

    if ((totalpin+1)-pin_rang_1<10)
      tft.setCursor(ic_x+spc+i*(pin_w+spc)+(pin_w/3), ic_y-10);
    else
      tft.setCursor(ic_x+spc+i*(pin_w+spc)+2, ic_y-10);

    tft.println((totalpin+1)-pin_rang_1);

    pin_rang_1++;   

  }
}

void printText(int curX, int curY, int textSize, String text){
  tft.fillScreen(BLACK);
  tft.setCursor(curX, curY);
  tft.setTextColor(RED);
  tft.setTextSize(textSize);
  tft.println(text);
}

void startScreen(){

  tft.fillScreen(BLACK);
  tft.setCursor(25, 40);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");
  tft.setCursor(150, 130);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("By");
  tft.setCursor(45, 160);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("VIBR77");
  tft.setCursor(20, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("Touch anywhere to START");

  //leds[0] = CRGB(255,0,255); leds[1] = CRGB(255,0,255);
  //FastLED.show();
}

void modeScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(60, 60);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Select Mode");

  buttons[0].initButton(&tft, 150, 120, 160, 40, BLACK, BLUE, WHITE, "Auto", 4);
  buttons[0].drawButton();

  buttons[1].initButton(&tft, 150, 180, 160, 40, BLACK, YELLOW, BLACK, "Manual", 4);
  buttons[1].drawButton();

}

void autoScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(20, 60);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Auto Search Mode");

  tft.setCursor(30, 120);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Select Number of Pins");

  buttons[0].initButton(&tft, 70, 180, 140, 40, WHITE, CYAN, BLACK, "14 Pins", 3);
  buttons[0].drawButton();

  buttons[1].initButton(&tft, 250, 180, 140, 40, WHITE, YELLOW, BLACK, "16 Pins", 3);
  buttons[1].drawButton();

  //leds[0] = CRGB(0, 0, 255); leds[1] = CRGB(0, 0, 255);
  //FastLED.show();
}

void autoSearchResult(int mode, String number = "", String name = "", int count = 0)
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(60, 55);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Auto Search");

  tft.setTextColor(YELLOW);
  tft.setCursor(90, 80);
  tft.println("Complete");
  //*************************************************************
  if (mode != 0)
  {
    number = "IC-" + number;

    tft.setTextColor(CYAN); tft.setTextSize(3);
    tft.setCursor(0, 130);
    tft.println(number);

    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println(name);
    tft.println();

    //leds[0] = CRGB(0, 255, 0); leds[1] = CRGB(0, 255, 0);
    //FastLED.show();
  }
  else
  {
    for (int i = 0; i < 3; i++)
    {
      tft.setCursor(40, 140);
      tft.setTextColor(BLACK);  tft.setTextSize(3);
      tft.print("NO MATCH FOUND");
      delay(500);
      tft.setCursor(40, 140);
      tft.setTextColor(RED);  tft.setTextSize(3);
      tft.print("NO MATCH FOUND");
      delay(500);

      //leds[0] = CRGB(255, 0, 0); leds[1] = CRGB(255, 0, 0);
      //FastLED.show();
    }
  }
  //*************************************************************
  tft.setCursor(40, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  if (mode == 0 || count == 0)
  {
    tft.println("Touch for MAIN MENU");
    getTouch();
    //resetFunc();
    asm volatile("jmp 0x00");
  }
  else
  {
    tft.println("Touch to CONTINUE");
    getTouch();
  }
}

void searching(int i)
{
  if (i == 1)
  {
    tft.setTextColor(BLACK);
    tft.setCursor(70, 150);
    tft.println("Testing...");
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing.");

    //leds[0] = CRGB(255, 0, 255); leds[1] = CRGB(255, 0, 255);
    //FastLED.show();
  }
  else if (i == 2)
  {
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing..");

    //leds[0] = CRGB(0, 0, 0); leds[1] = CRGB(0, 0, 0);
    //FastLED.show();
  }
  else if (i == 3)
  {
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing...");

    //leds[0] = CRGB(255, 0, 255); leds[1] = CRGB(255, 0, 255);
    //FastLED.show();
  }
  else if (i == -1)
  {
    tft.setTextColor(BLACK);
    tft.setCursor(70, 150);
    tft.println("Testing...");

    //leds[0] = CRGB(0, 0, 0); leds[1] = CRGB(0, 0, 0);
    //FastLED.show();
  }

}

void manualScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(45, 60);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Manual Search");
  tft.setCursor(125, 85);
  tft.println("Mode");

  tft.setCursor(60, 135);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Enter IC Number:");

  buttons[0].initButton(&tft, 200, 180, 200, 50, BLACK, BLUE, WHITE, "ENTER >", 4);
  buttons[0].drawButton();

  //leds[0] = CRGB(255, 255, 0); leds[1] = CRGB(255, 255, 0);
  //FastLED.show();
}

void manualSearchResult(String number, String name, int status)
{

  tft.fillScreen(BLACK);
  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(45, 55);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Manual Search");

  tft.setTextColor(YELLOW);
  tft.setCursor(90, 80);
  tft.println("Complete");

  number = "IC-" + number;

  tft.setTextColor(CYAN); tft.setTextSize(3);
  tft.setCursor(0, 130);
  tft.println(number);

  if (status != -1)
  {
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println(name);
    tft.println();
  }
  for (int i = 0; i < 2; i++)
  {
    delay(500);
    tft.setCursor(0, 130);
    tft.setTextColor(BLACK); tft.setTextSize(3);
    tft.setCursor(0, 130);
    tft.println(number);
    delay(400);
    switch (status)
    {
      case 0 : tft.setTextColor(RED); tft.setTextSize(3);
        //leds[0] = CRGB(255, 0, 0); leds[1] = CRGB(255, 0, 0);
        //FastLED.show();
        break;
      case 1 : tft.setTextColor(GREEN); tft.setTextSize(3);
        //leds[0] = CRGB(0, 255, 0); leds[1] = CRGB(0, 255, 0);
        //FastLED.show();
        break;
      case -1 : tft.setTextColor(MAGENTA); tft.setTextSize(3);
        //leds[0] = CRGB(255, 0, 255); leds[1] = CRGB(255, 0, 255);
        //FastLED.show();
        break;
    }
    tft.setCursor(0, 130);
    tft.println(number);
  }

  if (status == -1)
  {
    tft.setTextColor(RED);
    tft.println("IC NOT FOUND");
    //leds[0] = CRGB(0, 0, 0); leds[1] = CRGB(0, 0, 0);
    //FastLED.show();
  }

  tft.setCursor(40, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("Touch for MAIN MENU");

  getTouch();
  asm volatile("jmp 0x00");
  //resetFunc();
}
