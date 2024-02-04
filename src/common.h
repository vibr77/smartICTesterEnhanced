
#include <Adafruit_GFX.h>    // Core graphics library
#include "../lib/Adafruit_TFTLCD/Adafruit_TFTLCD.h" // Hardware-specific library

//#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h> //Touch Screen Library

#include <ArduinoJson.h>



#ifndef common
#define common

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8C71

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // LCD RESET goes to Analog 4

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin


#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define fname "database.txt"

#define chipSelect 10


extern int screenStatus; 
extern int lastStatus;
extern int *pin; 
extern int pinCount;

extern Adafruit_TFTLCD tft;
extern TouchScreen ts;
extern Adafruit_GFX_Button buttons[];

extern int pin14[];
extern int pin16[];
extern int pin20[];

typedef struct {
  String num;
  String name;
} IC;



#endif


//extern TouchScreen ts;
