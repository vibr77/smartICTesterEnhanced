#include "arduino.h"

void tft_init();
void printText(int curX, int curY, int textSize, String text);
void startScreen();
void modeScreen();
void autoScreen();
void autoSearchResult(int mode, String number = "", String name = "", int count = 0);
void searching(int i);
void manualScreen();
void manualSearchResult(String number, String name, int status);

void drawICLabel(char * title);
void drawPinLabel(int pin,int totalpin,char * txt);
void drawIC(int totalpin);
void drawProgressBar(int start,int end,int pos,uint16_t color,int clear);
void drawBottomLine(char * txt,int line,int font_size, uint16_t color);
void drawCirclePintStatus(int pin, int totalpin,uint16_t color);
void drawRecPintStatus(int pin, int totalpin,uint16_t color);




