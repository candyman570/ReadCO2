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
#define LED_PIN     2       // led Strip Data Signal: Arduino Pin D2
#define NUM_LEDS 32         // length of LED strip.
#define MIN_BRIGHTNESS  2   // 0..255 minimum allowed brightness
#define MAX_BRIGHTNESS  255  // 0..255 maximum allowed brightness
#define DEFAULT_BRIGHTNESS 64 // 0..255 brightness if no LIGHT_SENSOR is used
#define USE_LIGHT_SENSOR 1  // enable light sensor measurement otherwise the MAX_BRIGHTNESS will be used
#define INTEG_COEFF 0.2    // light sensor integration factor (high values=fast)
#define LIGHT_K 1          // light sensor slope K   y=kx+d 
#define LIGHT_D -60        // light sensor offset D
#define LED_TYPE    WS2811  // LED chip type
#define COLOR_ORDER GRB
#define ANIMATION 0 // Set to 1 to animate LEDs while Sensor is starting up 
double light;


// define globals
CRGB leds[NUM_LEDS]; // Define the array of leds
SoftwareSerial mySerial(10, 11); // Arduino Pin D10: RX, D11: TX 

void setup() {
  light=analogRead(A7); // initial value of lightness
  Serial.begin(9600); // open serial port (USB) for optional data transmission to PC
  mySerial.begin(9600); // open serial port for sensor readout (software-uart)
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS); // create FastLED instance
  FastLED.setBrightness(MAX_BRIGHTNESS);
  if(ANIMATION) ledAnimation(); 
}

void loop() {
  unsigned char readbyte[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // bytes for querying CO2 sensor
  uint32_t bright;
  if(USE_LIGHT_SENSOR) bright=readLightingLevel(); else bright=MAX_BRIGHTNESS;
  FastLED.setBrightness(bright);
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
      //Serial.print(receivebuf[9-count],HEX);
      //Serial.print(" ");
      count--;
    }
    else timeout--;
  }

  if(!(receivebuf[8]-getCheckSum(receivebuf))){ // checksum ok?
    ppm=receivebuf[2]*256+receivebuf[3];
    Serial.print("CO2-ppm: ");
    Serial.print(ppm,DEC);
    Serial.print(" Brightness: ");
    Serial.println(bright);
    ledOut(1,ppm); // output to LED stripe.
  }
  else {
    Serial.println("Data ERROR");
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[0]=CRGB::DarkRed;  // one red Led as error indicator
  }
  FastLED.show();   // send prepared led strip pattern to the physical led strip
  delay(1000);      // update rate 1 second
}

unsigned char getCheckSum(unsigned char *packet)
{
  unsigned char i, checksum=0;
  for( i = 1; i < 8; i++)
  {
    checksum += packet[i];
  }
  checksum = 0xff-checksum;
  checksum += 1;
  return checksum;
}

void ledOut(unsigned char type, uint16_t ppm){
    uint8_t index;
    switch(type){
      case 0: // color gradient, 3200ppm max
        index=ppm/100;
        fill_gradient_RGB(leds,0, CRGB::Green,NUM_LEDS-1, CRGB::Red); // prepare colors from green to red on led strip 
        fill_solid(leds+index, NUM_LEDS-index, CRGB::Black);          // keep only leds up to  current value. Remove leds above.
      break;
      case 1: // 4 colors, 1600ppm max
        index=ppm/50;
        fill_solid(leds,8,CRGB::Green);
        fill_solid(leds+8,8,0x705000);
        fill_solid(leds+16,8,0xF04000);
        fill_solid(leds+24,8,CRGB::Red);
        fill_solid(leds+index, NUM_LEDS-index, CRGB::Black);          // keep only leds up to  current value. Remove leds above.
      break;
      case 2: // 4 colors in incrasing brightness, 1600ppm max
        index=ppm/50;
        fill_gradient_RGB(leds,0,0x000800,7, CRGB::Green);
        fill_gradient_RGB(leds,8,0x100900,15, 0x705000);
        fill_gradient_RGB(leds,16,0x0F0400,23, 0xF04000);
        fill_gradient_RGB(leds,24,0x0F0000,31, CRGB::Red);
        fill_solid(leds+index, NUM_LEDS-index, CRGB::Black);          // keep only leds up to  current value. Remove leds above.
      break;
    }
}
void ledAnimation(){
  fill_solid(leds,32,CRGB::Green);
  dimup();
  delay(500);
  dimdown();
  fill_solid(leds,32,0x705000);
  dimup();
  delay(500);
  dimdown();
  fill_solid(leds,32,0xF04000);
  dimup();
  delay(500);
  dimdown();  
  fill_solid(leds,32,CRGB::Red);
  dimup();
  delay(500);
  dimdown();
  FastLED.setBrightness(MAX_BRIGHTNESS);
}

void dimdown(){
  for (uint8_t i=MAX_BRIGHTNESS;i>0;i--){
      FastLED.setBrightness(i );
      FastLED.show();
      delay(20);
  }  
}

void dimup(){
  for (uint8_t i=0; i<=MAX_BRIGHTNESS;i++){
      FastLED.setBrightness(i );
      FastLED.show();
      delay(20);
  }  
}
int readLightingLevel(){
  int readLight=analogRead(A7);
  int retval;
  light=light+INTEG_COEFF*(readLight-light); // update global variable (integrator)
  retval=(1-light/1024)*255*LIGHT_K+LIGHT_D; // adjust co-domain
  if(retval<MIN_BRIGHTNESS)retval=MIN_BRIGHTNESS; // Limiter
  if(retval>MAX_BRIGHTNESS)retval=MAX_BRIGHTNESS;
  return (retval); 
}
