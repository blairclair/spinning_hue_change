#include "FastLED.h"
#define LED_TYPE    WS2811  //WS2811, WS2812, WS2812B
#define LED_PIN 2
#define NUM_LEDS 3
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 40
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CHSV colorStart = CHSV(96,255,255);  // starting color
CHSV colorTarget = CHSV(192,255,255);  // target color
CHSV colorCurrent = colorStart;
int which_light = 0;
void setup() {
   LEDS.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
   FastLED.setBrightness(MAX_BRIGHTNESS);
   random16_add_entropy(analogRead(0));
   FastLED.clear();
  // put your setup code here, to run once:

}

void loop() {
     EVERY_N_MILLISECONDS(150){

    static uint8_t k;  // the amount to blend [0-255]
    if ( colorCurrent.h >= colorTarget.h ) {  // Check if target has been reached
      colorStart = colorCurrent;
      colorTarget = CHSV(random8(),255,255);  // new target to transition toward
      k = 0;  // reset k value
    }

    colorCurrent = blend(colorStart, colorTarget, k, SHORTEST_HUES);
    k+=20;

  if (which_light == 0){
    leds[which_light] = colorCurrent;
    which_light = 1;
  }
  else if (which_light == 1){
    leds[which_light] = colorCurrent;
    which_light = 2;
  }
  else if (which_light == 2){
    leds[which_light] = colorCurrent;
    which_light = 0;
  }
    FastLED.show();
 // put your main code here, to run repeatedly:
     }\
     
}
