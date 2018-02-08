#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

char readbyte[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial1.begin(9600);
  mySerial.begin(9600);
}

void loop() {

  while(mySerial.available()) mySerial.read(); // clear buffer before starting communication

  for (int i=0;i<9;i++){
    mySerial.write(readbyte[i]);
  }

  int timeout=100;  // no endless loop if no answer.
  int count=9;  // we expect 9 Bytes as response
  unsigned char receivebuf[9];
  while(timeout&&count){
    if (mySerial.available()) {
      receivebuf[9-count] = mySerial.read();
      count--;
    }  
  }

  if(!(receivebuf[8]-getCheckSum(receivebuf))){ // checksum ok?
    Serial.println(receivebuf[2]*256+receivebuf[3],DEC);
  }
  else Serial.println("Data ERROR");
  delay(1000); 
}

unsigned char getCheckSum(unsigned char *packet)
{
  char i, checksum;
  for( i = 1; i < 8; i++)
  {
    checksum += packet[i];
  }
  checksum = 0xff-checksum;
  checksum += 1;
  return checksum;
}
