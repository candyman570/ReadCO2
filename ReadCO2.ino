/*
CO2 meter for classrooms
Roman Bumerl-Lexa

Required Libraries (integrated in Arduino IDE):
SoftwareSerial v1.0.0
FastLED v3.1.6

Parts needed: 
Arduino Nano
MH-Z19 CO2 Sensor 0..5000ppm (aliexpress.com, EUR 20.-)
WS2811 LED Strip, e.g. Smart led pixel strip, 1m 96 IP30 
V1.0 initial release 2018-02-09
*/


#include <SoftwareSerial.h>

#include <FastLED.h>
#define LED_PIN     2
#define NUM_LEDS 32         // length of LED strip.
#define BRIGHTNESS  64      // 0..255
#define LED_TYPE    WS2811  // LED chip type
#define COLOR_ORDER GRB

// define globals
CRGB leds[NUM_LEDS]; // Define the array of leds
SoftwareSerial mySerial(10, 11); // RX, TX 

void setup() {
  Serial.begin(9600); // open serial port (USB) for optional data transmission to PC
  mySerial.begin(9600); // open serial port for sensor readout (software-uart)
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS); // create FastLED instance
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  char readbyte[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // bytes for querying CO2 sensor

  while(mySerial.available()) mySerial.read(); // clear buffer before starting communication

  for (int i=0;i<9;i++){
    mySerial.write(readbyte[i]); // send query message to CO2 sensor
  }

  int timeout=1000;  // no endless loop if no answer from sensor.
  int count=9;  // we expect 9 Bytes as response
  unsigned char receivebuf[9]; 
  uint16_t ppm;
  uint8_t index; // an index for the led strip. Above this value the leds are dark.
  while(timeout&&count){
    if (mySerial.available()) {
      receivebuf[9-count] = mySerial.read();
      count--;
    }
    else timeout--;
  }

  if(!(receivebuf[8]-getCheckSum(receivebuf))){ // checksum ok?
    ppm=receivebuf[2]*256+receivebuf[3];
    Serial.println(ppm,DEC);
    index=ppm/100;
    fill_gradient_RGB(leds,0, CRGB::Green,NUM_LEDS-1, CRGB::Red); // prepare colors from green to red on led strip 
    fill_solid(leds+index, NUM_LEDS-index, CRGB::Black);          // keep only leds up to  current value. Remove leds above.
  }
  else {
    Serial.println("Data ERROR");
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[0]=CRGB::DarkRed;  // one red Led as error indicator
  }
  FastLED.show();   // send prepared led strip pattern to the physical led strip
  delay(1000);      // update rate 
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
