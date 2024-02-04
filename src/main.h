
#include "Arduino.h"
void getTouch();
//void resetFunc();
//void(* resetFunc) (void) = 0;

boolean testIC(String buffer, int pins);
void autoSearchResult(int mode, String number = "", String name = "", int count = 0);
void manualSearchResult(String number, String name, int status);
unsigned long testFillScreen();