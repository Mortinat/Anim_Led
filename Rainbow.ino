// source code from : https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
// adaptation for lib FAB_LED
#include <FAB_LED.h>
#define NUM_LEDS 300

// FAB_LED provides many types of LEDs, here we use a WS2812B LED protocol on port D6
ws2812b<D,6> myLedStrip;

grb pixels[NUM_LEDS] = {};

void setup() {
  myLedStrip.clear(3000);
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      pixels[i].r = *c;
      pixels[i].g = *(c+1);
      pixels[i].b = *(c+2);
    }
    myLedStrip.sendPixels(NUM_LEDS, pixels);
    delay(SpeedDelay);
  }
}

void loop() {
  rainbowCycle(20);
}