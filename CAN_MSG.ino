#include <SPI.h>       //header file for SPI communication 
#include <mcp2515.h>   //header file containing predifined functions for mcp2515 CAN module

struct can_frame canMsg1;   //instance of structureto store a message 
struct can_frame canMsg2;
MCP2515 mcp2515(10);      //create an instance to address the module connected at D10

//initialize pin numbers to variables
int IMD=2;
int BSPD=4;
int AMS=6;
int SW=8;

boolean flag=0;
boolean check=0;

void setup() {
  //set the initialized pins as input pins
pinMode(IMD,INPUT);
pinMode(BSPD,INPUT);
pinMode(AMS,INPUT);
pinMode(SW,INPUT);

  //initialize message 2
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

Serial.begin(9600);  //start serial communication (over USB) 
SPI.begin();         //start SPI communication
 
  mcp2515.reset();    //reset the CAN module
  mcp2515.setBitrate(CAN_250KBPS);    //set the bit rate of CAN bus
  mcp2515.setNormalMode();
}

void loop() {
  //at first message 1 will have this  
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

  //when 'check' flag is zero read pins (check for errors in circuits) 
 if(!check){ 
  
  //Read the inputs from circuits, if error is present change a particular byte of message 1 to a unique value
  //and set the 'flag'
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
  else {//no operation }   
  //if 'flag' is set, send the message
  if(flag) {
    mcp2515.sendMessage(&canMsg1);
    Serial.println("ERROR DETECTED");
    check=1;     //set 'check' flag to avoid reading the pins again
    flag=0;      //clear 'flag' to avoid sending the message agin
  }
 }
  if(check&&(!digitalRead(IMD))&&(!digitalRead(AMS))&&(!digitalRead(BSPD))&&(!digitalRead(SW))) {      //if an error occurred ('check' flag is 1) previously and now allpi s are LOW 
    mcp2515.sendMessage(&canMsg2);         //send message 2 to indicate no error state
    Serial.println("NO MORE ERRORS");
    check=0;                      //clear 'check' flag to start checking for errors again
  } 
}
