void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  while(Serial1.available()) Serial1.read(); // clear buffer before starting communication

  Serial1.write(0xFF);  // start byte
  Serial1.write(0x01);  // sensor ID
  Serial1.write(0x86);  // 0x86: read CO2, 0x87: Calibrate zero point, 0x88 Calibrate span point
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x79);  // checksum, see getChecksum.

  int timeout=100;
  int count=9;
  unsigned char receivebuf[9];
  while(timeout&&count){
    if (Serial1.available()) {
      receivebuf[9-count] = Serial1.read();
      count--;
    }  
  }

    if(!(receivebuf[8]-getCheckSum(receivebuf))){
    /*Serial.print("Byte3:");
    Serial.print(receivebuf[2],DEC);
    Serial.print("  Byte4:");
    Serial.println(receivebuf[3],DEC);
    Serial.print(receivebuf[8],HEX);
    Serial.print("  ");
    Serial.println(getCheckSum(receivebuf),HEX);*/
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
