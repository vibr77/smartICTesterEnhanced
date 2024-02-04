#include "Arduino.h"
#include "common.h"
#include "test_functions.h"
#include "tft.h"
#include <ArduinoJson.h>
#include <ArduinoLog.h>

DynamicJsonDocument doc(131072);
DeserializationError error;

const char ICJSONTEST[]="{\
        \"title\":\"74LS74\",\
        \"description\":\"Dual D-TYPE Positive Edge triggered Flip-Flops with preset and clear\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"/CLR\",\
          \"1D\",\
          \"1CLK\",\
          \"/1PRE\",\
          \"1Q\",\
          \"/1Q\",\
          \"GND\",\
          \"/2Q\",\
          \"2Q\",\
          \"/2PRE\",\
          \"2CLK\",\
          \"2D\",\
          \"/2CLR\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"1XX0HLGLH0XX1V\",\
          \"0XX0HHGHH0XX0V\",\
          \"0XX0HHGLH0XX1V\",\
          \"1XX0HLGHH0XX0V\",\
          \"10C1LHGHL1C01V\",\
          \"11C1HLGLH1C11V\",\
          \"11C1HLGHL1C01V\",\
          \"10C1LHGLH1C11V\",\
          ]\
}";


const char ICJSONTEST_139[]="{\
        \"title\":\"74LS139\",\
        \"description\":\"Dual 1-OF-4 DECODER/DEMULTIPLEXER\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"/Ea\",\
          \"A0a\",\
          \"A1a\",\
          \"O0a\",\
          \"O1a\",\
          \"O2a\",\
          \"O3a\",\
          \"GND\",\
          \"O3b\",\
          \"O2b\",\
          \"O1b\",\
          \"O0b\",\
          \"A1b\",\
          \"A0b\",\
          \"/Eb\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"1XXHHHHGHHHHXX1V\",\
          \"000LHHHGHHHL000V\",\
          \"010HLHHGHHLH010V\",\
          \"001HHLHGHLHH100V\",\
          \"011HHHLGLHHH110V\"\
          ]\
}";

const char ICJSONTEST_175[]="{\
        \"title\":\"74LS175\",\
        \"description\":\"QUAD D FLIP-FLOP\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"MR\",\
          \"Q0\",\
          \"/Q0\",\
          \"D0\",\
          \"D1\",\
          \"/Q1\",\
          \"Q1\",\
          \"GND\",\
          \"CP\",\
          \"Q2\",\
          \"/Q2\",\
          \"D2\",\
          \"D3\",\
          \"/Q3\",\
          \"Q3\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"1HL11LHGCHL11LHV\",\
          \"1LH00HLGCLH00HLV\"\
          \"1HL11LHGCLH00HLV\",\
          \"1LH00HLGCHL11LHV\",\
          \"0LH00HLGXLH00HLV\"\
          ]\
}";

const char ICJSONTEST_00[]="{\
        \"title\":\"74LS00\",\
        \"description\":\"Quadruple 2-Input Positive-NAND Gates\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1B\",\
          \"1Y\",\
          \"2A\",\
          \"2B\",\
          \"2Y\",\
          \"GND\",\
          \"3Y\",\
          \"3B\",\
          \"3A\",\
          \"4Y\",\
          \"4B\",\
          \"4A\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"11L11LGL11L11V\",\
          \"X0HX0HGH0XH0XV\",\
          \"0XH0XHGHX0HX0V\",\
          \"11L0XHGL11H0XV\",\
          \"0XH11LGH0XL11V\"\
          ]\
}";

const char ICJSONTEST_32[]="{\
        \"title\":\"74LS32\",\
        \"description\":\"QUAD 2 INPUT OR GATE\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1B\",\
          \"1Y\",\
          \"2A\",\
          \"2B\",\
          \"2Y\",\
          \"GND\",\
          \"3Y\",\
          \"3A\",\
          \"3B\",\
          \"4Y\",\
          \"4A\",\
          \"4B\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"1XH1XHGH1XH1XV\",\
          \"X1HX1HGHX1HX1V\",\
          \"00L00LGL00L00V\",\
          \"X1H00LGL00HX1V\",\
          \"00LX1HGX1HL00V\"\
          ]\
}";

const char ICJSONTEST_85[]="{\
        \"title\":\"74LS85\",\
        \"description\":\"4-BIT Magnitude comparator\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"B3\",\
          \"IA<B\",\
          \"IA=B\",\
          \"IA>B\",\
          \"OA>B\",\
          \"OA=B\",\
          \"OA<B\",\
          \"GND\",\
          \"B0\",\
          \"A0\",\
          \"B1\",\
          \"A1\",\
          \"A2\",\
          \"B2\",\
          \"A3\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0XXXHLLGXXXXXX1V\",\
          \"1XXXLLHGXXXXXX0V\",\
          \"0XXXHLLGXXXX100V\",\
          \"1XXXHLLGXXXX101V\",\
          \"0XXXLLHGXXXX010V\",\
          \"1XXXLLHGXXXX011V\",\
          \"1XXXHLLGXX01111V\",\
          \"1XXXLLHGXX10111V\",\
          \"1XXXHLLG0111111V\",\
          \"1XXXLLHG1011111V\",\
          \"1001HLLG1111111V\",\
          \"1100LLHG1111111V\",\
          \"1X1XLHLG1111111V\",\
          \"1101LLLG1111111V\",\
          \"1000HLHG1111111V\"\
          ]\
}";

const char ICJSONTEST_86[]="{\
        \"title\":\"74LS86\",\
        \"description\":\"Quad 2-input XOR gates\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1B\",\
          \"1Y\",\
          \"2A\",\
          \"2B\",\
          \"2Y\",\
          \"GND\",\
          \"3Y\",\
          \"3A\",\
          \"3B\",\
          \"4Y\",\
          \"4A\",\
          \"4B\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"00L00LGL00L00V\",\
          \"01H01HGH01H01V\",\
          \"10H10HGH10H10V\",\
          \"11L11LGL11L11V\"\
          ]\
}";




const char ICJSONTEST_244[]="{\
        \"title\":\"74LS244\",\
        \"description\":\"Octal Buffers and Line Drivers With 3-State Outputs\",\
        \"pins\":20,\
        \"pinLabel\":[\
          \"/1G\",\
          \"1A1\",\
          \"2Y4\",\
          \"1A2\",\
          \"2Y3\",\
          \"1A3\",\
          \"2Y2\",\
          \"1A4\",\
          \"2Y1\",\
          \"GND\",\
          \"2A1\",\
          \"1Y4\",\
          \"2A2\",\
          \"1Y3\",\
          \"2A3\",\
          \"1Y2\",\
          \"2A4\",\
          \"1Y1\",\
          \"/2G/2G\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"01H1H1H1HG1H1H1H1H0V\",\
          \"00L0L0L0LG0L0L0L0L0V\",\
          \"10H0H0H0HG0H0H0H0H1V\"\
          ]\
}";

const char ICJSONTEST_161[]="{\
        \"title\":\"74LS161\",\
        \"description\":\"SYNCHRONOUS 4-BIT COUNTERS\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"CLR\",\
          \"CLK\",\
          \"Ia\",\
          \"Ib\",\
          \"Ic\",\
          \"Id\",\
          \"ENp\",\
          \"GND\",\
          \"LOAD\",\
          \"ENt\",\
          \"Qd\",\
          \"Qc\",\
          \"Qb\",\
          \"Qa\",\
          \"Carry\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0100000G00LLLLLV\",\
          \"0100001G11LLLLLV\",\
          \"1C00001G10LLLLLV\",\
          \"1C00000G11LLLLLV\",\
          \"1C00000G10LLLLLV\",\
          \"1C00000G00LLLLLV\",\
          \"1C00111G01HHLLLV\",\
          \"1C00001G11HHLHLV\",\
          \"1C00001G11HHHLLV\",\
          \"1C00001G11HHHHHV\",\
          \"1C00001G11LLLLLV\",\
          \"1C00001G11LLLHLV\",\
          \"1100001G11LLHLLV\",\
          \"1000001G11LLHLLV\",\
          \"0000001G11LLLLLV\",\
          \"1C00001G11XXXXXV\"\
          ]\
}";


const char ICJSONTEST_02[]="{\
        \"title\":\"74LS02\",\
        \"description\":\"Quad 2-input NOR gates\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"Y1\",\
          \"A1\",\
          \"B1\",\
          \"Y2\",\
          \"A2\",\
          \"B2\",\
          \"GND\",\
          \"A3\",\
          \"B3\",\
          \"Y3\",\
          \"A4\",\
          \"B4\",\
          \"Y4\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"H00H00G00H00HV\",\
          \"L10L10G10L10LV\",\
          \"L01L01G01L01LV\",\
          \"L11L11G11L11LV\"\
        ]\
}";

const char ICJSONTEST_04[]="{\
        \"title\":\"74LS04\",\
        \"description\":\"Hex Inverter\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1Y\",\
          \"2A\",\
          \"2Y\",\
          \"3A\",\
          \"3Y\",\
          \"GND\",\
          \"4Y\",\
          \"4A\",\
          \"5Y\",\
          \"5A\",\
          \"6Y\",\
          \"6A\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0H0H0HGH0H0H0V\",\
          \"1L1L1LGL1L1L1V\"\
        ]\
}";


const char ICJSONTEST_195[]="{\
        \"title\":\"74LS195\",\
        \"description\":\"4-bit universal shift register with J-/K inputs and asynchronous reset\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"MR\",\
          \"J\",\
          \"K\",\
          \"P0\",\
          \"P1\",\
          \"P2\",\
          \"P3\",\
          \"GND\",\
          \"/PE\",\
          \"CP\",\
          \"/Q3\",\
          \"Q3\",\
          \"Q2\",\
          \"Q1\",\
          \"Q0\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
        \"0000000G0CHLLLLV\",\
        \"1000000G0CHLLLLV\",\
        \"1000000G1CHLLLLV\",\
        \"1010000G1CHLLLLV\",\
        \"1000000G1CHLLLLV\",\
        \"1110000G1CHLLLHV\",\
        \"1100000G1CHLLHLV\"\
        ]\
}";

const char ICJSONTEST_194[]="{\
        \"title\":\"74LS194\",\
        \"description\":\"4-bit bidirectional universal shift register with asynchronous reset\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"/CLR\",\
          \"SR\",\
          \"A\",\
          \"B\",\
          \"C\",\
          \"D\",\
          \"SL\",\
          \"GND\",\
          \"S0\",\
          \"S1\",\
          \"CLK\",\
          \"QD\",\
          \"QC\",\
          \"QB\",\
          \"QA\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0000000G00CLLLLV\",\
          \"0111111G11CLLLLV\",\
          \"1000000G00CLLLLV\",\
          \"1111111G11CHHHHV\",\
          \"1011110G11CHHHHV\",\
          \"1100001G11CLLLLV\",\
          \"1111110G10CLLLHV\",\
          \"1100001G10CLLHHV\",\
          \"1100001G10CLHHHV\",\
          \"1100001G10CHHHHV\",\
          \"1000000G10CHHHLV\",\
          \"1011111G10CHHLLV\",\
          \"1000001G01CHHHLV\",\
          \"1111111G01CHHHHV\",\
          \"1000000G01CLHHHV\",\
          \"1111110G01CLLHHV\",\
          \"1000000G00CLLHHV\",\
          \"1111111G00CLLHHV\",\
          \"1111111G01CHLLHV\",\
          \"1111111G01CHHLLV\",\
          \"1111111G01CHHHLV\",\
          \"1111111G01CHHHHV\",\
          \"0111111G11CLLLLV\"\
        ]\
}";

const char ICJSONTEST_20[]="{\
        \"title\":\"74LS20\",\
        \"description\":\"Dual 4-input NAND gates\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1B\",\
          \"NC\",\
          \"1C\",\
          \"1D\",\
          \"1Y\",\
          \"GND\",\
          \"2Y\",\
          \"2A\",\
          \"2B\",\
          \"NC\",\
          \"2C\",\
          \"2D\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"00X00HGH00X00V\",\
          \"10X00HGH10X00V\",\
          \"01X00HGH01X00V\",\
          \"11X00HGH11X00V\",\
          \"00X10HGH00X10V\",\
          \"10X10HGH10X10V\",\
          \"01X10HGH01X10V\",\
          \"11X10HGH11X10V\",\
          \"11X11LGL11X11V\"\
        ]\
}";

const char ICJSONTEST_257[]="{\
        \"title\":\"74LS257\",\
        \"description\":\"8-to-4 line 3-state noninverting data selector/multiplexer\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"SEL\",\
          \"A1\",\
          \"B1\",\
          \"Y1\",\
          \"A2\",\
          \"B2\",\
          \"Y2\",\
          \"GND\",\
          \"Y3\",\
          \"B3\",\
          \"A3\",\
          \"Y4\",\
          \"B4\",\
          \"A4\",\
          \"OUTC\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"000H00HGH00H001V\",\
          \"111H11HGH11H111V\",\
          \"000L00LGL00L000V\",\
          \"001L01LGL10L100V\",\
          \"010H10HGH01H010V\",\
          \"011H11HGH11H110V\",\
          \"100L00LGL00L000V\",\
          \"110L10LGL01L010V\",\
          \"101H01HGH10H100V\",\
          \"111H11HGH11H110V\"\
        ]\
}";


const char ICJSONTEST_245[]="{\
        \"title\":\"74LS245\",\
        \"description\":\"Octal Bus Transceivers With 3-State Outputs\",\
        \"pins\":20,\
        \"pinLabel\":[\
          \"DIR\",\
          \"A1\",\
          \"A2\",\
          \"A3\",\
          \"A4\",\
          \"A5\",\
          \"A6\",\
          \"A7\",\
          \"A8\",\
          \"GND\",\
          \"B8\",\
          \"B7\",\
          \"B6\",\
          \"B5\",\
          \"B4\",\
          \"B3\",\
          \"B2\",\
          \"B1\",\
          \"/OE\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"100000000GLLLLLLLL0V\",\
          \"111111111GHHHHHHHH0V\",\
          \"0LLLLLLLLG000000000V\",\
          \"0HHHHHHHHG111111110V\",\
          \"0HHHHHHHHGHHHHHHHH1V\"\
        ]\
}";

const char ICJSONTEST_08[]="{\
        \"title\":\"74LS08\",\
        \"description\":\"QUADRUPLE 2-INPUT POSITIVE-AND GATES\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"A1\",\
          \"B1\",\
          \"Y1\",\
          \"A2\",\
          \"B2\",\
          \"Y2\",\
          \"GND\",\
          \"Y3\",\
          \"A3\",\
          \"B3\",\
          \"Y4\",\
          \"A4\",\
          \"B4\",\
          \"OUTC\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"00L00LGL00L00V\",\
          \"01L01LGL01L01V\",\
          \"10L10LGL10L10V\",\
          \"11H11HGH11H11V\"\
        ]\
}";

const char ICJSONTEST_51[]="{\
        \"title\":\"74LS51\",\
        \"description\":\"2-wide 2-input and 2-wide 3-input AND-NOR gates\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"2A\",\
          \"2B\",\
          \"2C\",\
          \"2D\",\
          \"2Y\",\
          \"GND\",\
          \"1Y\",\
          \"1D\",\
          \"1E\",\
          \"1F\",\
          \"1B\",\
          \"1C\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"10000HGH11001V\",\
          \"01000HGH01001V\",\
          \"10100HGH10000V\",\
          \"01100LGH00000V\",\
          \"00010HGH10000V\",\
          \"00001HGH11000V\",\
          \"00011LGH01000V\",\
          \"10110HGH00000V\",\
          \"11001HGH00001V\",\
          \"01111LGH00001V\",\
          \"11111LGL00011V\",\
          \"00011LGL11111V\"\
        ]\
}";

const char ICJSONTEST_06[]="{\
        \"title\":\"74LS06\",\
        \"description\":\"Hex Inverter Buffers and Drivers With Open-Collector High-Voltage Outputs\",\
        \"pins\":14,\
        \"pinLabel\":[\
          \"1A\",\
          \"1Y\",\
          \"2A\",\
          \"2Y\",\
          \"3A\",\
          \"3Y\",\
          \"GND\",\
          \"4Y\",\
          \"4A\",\
          \"5Y\",\
          \"5A\",\
          \"6Y\",\
          \"6A\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0H0H0HGH0H0H0V\",\
          \"1L1L1LGL1L1L1V\"\
        ]\
}";

const char ICJSONTEST_151[]="{\
        \"title\":\"74LS151\",\
        \"description\":\"8-to-4 line 3-state noninverting data selector/multiplexer\",\
        \"pins\":16,\
        \"pinLabel\":[\
          \"D3\",\
          \"D2\",\
          \"D1\",\
          \"D0\",\
          \"Y\",\
          \"W\",\
          \"/G\",\
          \"GND\",\
          \"C\",\
          \"B\",\
          \"A\",\
          \"D7\",\
          \"D6\",\
          \"D5\",\
          \"D4\",\
          \"VCC\"\
          ],\
        \"testCase\":[\
          \"0101LH1G1010101V\",\
          \"1010LH1G0101010V\",\
          \"1110LH0G0001111V\",\
          \"0001HL0G0000000V\",\
          \"1101LH0G0011111V\",\
          \"0010HL0G0010000V\",\
          \"1011LH0G0101111V\",\
          \"0100HL0G0100000V\",\
          \"0111LH0G0111111V\",\
          \"1000HL0G0110000V\",\
          \"1111LH0G1001110V\",\
          \"0000HL0G1000001V\",\
          \"1111LH0G1011101V\",\
          \"0000HL0G1010010V\",\
          \"1111LH0G1101011V\",\
          \"0000HL0G1100100V\",\
          \"1111LH0G1110111V\",\
          \"0000HL0G1111000V\"\
        ]\
}";

int loadTestCaseFromJson(const char strJson[]){

error = deserializeJson(doc, strJson);
  if (error) {
    Serial.println( "deserializeJson() failed: ");
    Serial.println(error.f_str());
    Serial.println(ICJSONTEST_51);

// 74LS244
// 74LS08
// 74LS51
// 74LS06
// 74LS151

    return -1;
  }
  return 0;
}

int execICTesting(char * ICref){

  int res=loadTestCaseFromJson(ICJSONTEST_51);

  bool testResult=false;
  int totalpin=doc["pins"].as<int>();
  drawIC(totalpin);
  drawICLabel(doc["title"].as<String>().c_str());
  JsonArray array2 = doc["pinLabel"];
  int i=1;
  for(JsonVariant v2 : array2 ) {
    Serial.println(v2.as<String>());
    drawPinLabel(i,doc["pins"],v2.as<String>().c_str());
    i++;
  }

  JsonArray array = doc["testCase"];
  char str[32];
  char strResult[32];
  int len=array.size();

  // Intensive testing 
  for (int z=0;z<50;z++){
    i=1;
    drawProgressBar(0,50,z,GRAY,0);
    for(JsonVariant v : array) {
      Log.notice("test %d/%d"CR,i,len);
      sprintf(str,"%s",v.as<String>().c_str());
      testResult=testCase(str,doc["pins"].as<int>(),strResult);
      if (testResult==false){    
        break;
      }
      i++;
    }
    z++;
    if (testResult==false)
      break;
  }
  drawProgressBar(0,50,0,GRAY,1);
  if (testResult==false){
    drawBottomLine(str,1,2, WHITE);
    drawBottomLine(strResult,2,2, RED);
    for (int i=0;i<totalpin;i++){
      if (strResult[i]!=' '){
        drawCirclePintStatus(i+1,totalpin,RED);
      }else if (str[i]=='H' || str[i]=='L' ){
        drawCirclePintStatus(i+1,totalpin,GREEN);
      }else if (str[i]=='1'){
        drawRecPintStatus(i+1,totalpin,BLUE);
      }else if (str[i]=='0'){
        drawRecPintStatus(i+1,totalpin,GRAY);
      }else if (str[i]=='C'){
        drawRecPintStatus(i+1,totalpin,YELLOW);
      }else if (str[i]=='V'){
        drawRecPintStatus(i+1,totalpin,RED);
      }
    }
  }else{
    drawBottomLine(doc["description"].as<String>().c_str(),1,1, WHITE);
    drawBottomLine("CHIP IS GOOD",2,2, GREEN);
  }
//drawCirclePintStatus(7,14,YELLOW);
//drawCirclePintStatus(13,14,YELLOW);

//drawtestResult(strResult,1);
/*JsonArray prefs = doc["prefs"].as<JsonArray>();
for (JsonObject a : prefs) {
    for (JsonPair kv : a) {
        Serial.println(kv.key().c_str());
        if (kv.value().is<int>()) {
            Serial.println(kv.value().as<int>());
        }
        else {
            Serial.println(kv.value().as<bool>());
        }
    }
}*/


}

boolean testCase(char *test, int pins, char* strResult){
  
  boolean result = true;
  
  int i=0;
  
  // Let init the clkpin

  int clkPin[pins];
  for (i=0;i<pins;i++){
    clkPin[i]=-1;
  }
  
  
  /*
    Serial.print("PINS=");
    Serial.println(pins);
    Serial.print("SignalIn : ");
    Serial.println(test);
  */

  if (pins==14)
    pin=pin14;
  else if (pins==16)
    pin=pin16;
  else
    pin=pin20;  

  //Setting Vcc, GND and INPUTS
  for (i = 0; i < pins; i++)
  {
    /*
    Serial.print("PIN ");
    Serial.print(i);
    Serial.print("=");
    Serial.println(pin[i]);
    */
    switch (test[i])
    {
      case 'V' : 
        pinMode(pin[i], OUTPUT); 
        digitalWrite(pin[i], HIGH);
        break;
      case 'G' : 
        pinMode(pin[i], OUTPUT); 
        digitalWrite(pin[i], LOW);
        break;
      case 'L' : 
        digitalWrite(pin[i], LOW); 
        pinMode(pin[i], INPUT_PULLUP);
        break;
      case 'H' : 
        digitalWrite(pin[i], LOW); 
        pinMode(pin[i], INPUT_PULLUP);
        break;
    }
  }
  
  delay(10);
 
  //Setting Input Signals
  
  for (i = 0; i < pins; i++){
    switch (test[i])
    {
      case 'X' :
      case '0' : 
        pinMode(pin[i], OUTPUT); 
        digitalWrite(pin[i], LOW);
        break;
      case '1' : 
        pinMode(pin[i], OUTPUT); 
        digitalWrite(pin[i], HIGH);
        break;
      case 'C' : 
        clkPin[i] = 1; 
        pinMode(pin[i], OUTPUT); 
        digitalWrite(pin[i], LOW);
        break;
    }
  }
  delay(5);
  // Trigger all the Clock pulse
  for (i=0;i<pins;i++){

    if (clkPin[i] != -1){
    //Clock Trigger
      digitalWrite(pin[i], HIGH);
      delay(5);
      digitalWrite(pin[i], LOW);
    }
  }

  delay(5);

  //Reading Outputs
 
  for (i = 0; i < pins; i++){
    switch (test[i]){
      case 'H' : 
        if (!digitalRead(pin[i])) {
          Log.notice( "ERROR PIN=%d, ID=%d,status=LOW instead of H" CR,i,pin[i]);
          result = false;
          strResult[i]='L';
        }
        else {
          strResult[i]=' ';
        }
        break;
      case 'L' : 
        if (digitalRead(pin[i])) {
          result = false;
          Log.notice( "ERROR PIN=%d, ID=%d,status=HIGH instead of L" CR ,i,pin[i]);
          strResult[i]='H';
          Serial.print("reread");
          Serial.println(digitalRead(pin[i]));
        }else {
          strResult[i]=' ';
        }
        break;
      default : 
        strResult[i]=' ';
    }
  }

  strResult[i]='\0';
  Log.notice("IN:  %s"CR,test);
  Log.notice("OUT: %s"CR,strResult);
  
  return result;
}

/*
  boolean testIC(String buffer, int pins)
  {
  int startIndex = 0, lastIndex = 0;
  boolean result=true;
  String newTest;
  buffer.trim();

  Serial.print(buffer);
  while (startIndex <= buffer.lastIndexOf('\n'))
  {
    lastIndex = buffer.indexOf('\n',startIndex);

    Serial.println("S: "+String(startIndex)+" L: "+String(lastIndex));

    newTest=buffer.substring(startIndex, lastIndex);
    newTest.trim();
    //Serial.println(newTest);
    Serial.println("------------------");
    startIndex = lastIndex + 1;

    if (testCase(newTest, pins)==false)
    {
      result = false;
      //break;
    }
  }
  //Serial.println("testIC() : "+String(result));
  return result;
  }
*/