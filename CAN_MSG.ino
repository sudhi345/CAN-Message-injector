#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

int IMD=2;
int BSPD=4;
int AMS=6;
int SW=8;
boolean flag=0;
boolean check=0;

void setup() {
pinMode(IMD,INPUT);
pinMode(BSPD,INPUT);
pinMode(AMS,INPUT);
pinMode(SW,INPUT);

  canMsg2.can_id  = 0x007;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0xEE;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x00;
  canMsg2.data[4] = 0x00;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0xEE;

Serial.begin(9600);
SPI.begin();
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();
}

void loop() {
  canMsg1.can_id  = 0x007;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0xEE;
  canMsg1.data[1] = 0xEE;
  canMsg1.data[2] = 0xEE;
  canMsg1.data[3] = 0xEE;
  canMsg1.data[4] = 0xEE;
  canMsg1.data[5] = 0xEE;
  canMsg1.data[6] = 0xEE;
  canMsg1.data[7] = 0xEE;

 if(!check){
  if(digitalRead(IMD)) {
    canMsg1.data[2] = 0x45;
    flag=1;
  }
  else if(digitalRead(BSPD)) {
    canMsg1.data[4] = 0x69;
    flag=1;
  }
  else if(digitalRead(AMS)) {
    canMsg1.data[6] = 0x64;
    flag=1;
  }
  else if(digitalRead(SW)) {
    canMsg1.data[0] = 0x28;
    flag=1;
  }
  else {}
  if(flag) {
    mcp2515.sendMessage(&canMsg1);
    Serial.println("ERROR DETECTED");
    check=1;
    flag=0;
  }
 }
  if(check&&(!digitalRead(IMD))&&(!digitalRead(AMS))&&(!digitalRead(BSPD))&&(!digitalRead(SW))) {
    mcp2515.sendMessage(&canMsg2);
    Serial.println("NO MORE ERRORS");
    check=0;
  } 
}