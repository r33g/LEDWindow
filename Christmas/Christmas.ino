#include <avr/pgmspace.h>  // needed for PROGMEM
#include <Adafruit_NeoPixel.h>

extern const byte rgbArray[21][11][36][3]PROGMEM;

#define PIN 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(396, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'  
  //strip.setBrightness(10);
  strip.setBrightness(50);
 // strip.setBrightness(0);
  //Serial.begin(9600);
  //Serial.println(rgbArray[9][2][1]);
  //Serial.println('ello');
}
bool down = false;    
void loop() {
  // Some example procedures showing how to display to the pixels:

  for (int image=0; image < 19; image++) {
    
    //for (int blinking=0; blinking < 6; blinking++) {    
      
    long led = 0;
    down = false;  
    for (int xx=0; xx < 11; xx++) {
      
      //int starti = down ? 0: 41;
      //int stopi = down ? 41 : 0;
      //int inci = down ? 1 : -1;
      
      for(int y = 0; y < 36; y++) {    
          int yy = y;    
          
          if (!down)
             yy = abs(35 - y);               
      
      
          int rc = pgm_read_byte(&(rgbArray[0][xx][yy][0]));
          int gc = pgm_read_byte(&(rgbArray[0][xx][yy][1]));
          int bc = pgm_read_byte(&(rgbArray[0][xx][yy][2]));
          
      
          int r = pgm_read_byte(&(rgbArray[image+1][xx][yy][0]));
          int g = pgm_read_byte(&(rgbArray[image+1][xx][yy][1]));
          int b = pgm_read_byte(&(rgbArray[image+1][xx][yy][2]));
          
          
          /*if ((blinking==0 || blinking == 2 || blinking == 4 || blinking==6)  && ( r < 100 && g < 100 && b < 100)) {
            r = 255;
            g = 255;
            b = 255; 
          } else if ((blinking==0 || blinking == 2 || blinking == 4 || blinking==6)  && (r > 200 && g > 200 && b > 200)) {
            r = 255;
            g = 0;
            b = 0; 
          */
          /*if ((r < 50 && g < 50 && b < 50)) {
            r= 0;
            g = 0;
            b = 0;
          }*/
          
          if (rc==255 && gc==255 && bc==255) {
            r = 150;
            g = 150;
            b = 150;
          } else {
            r = rc+r;
            b = bc+b;
            g = gc+g;
            
            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;
          }
          
          strip.setPixelColor(led, r, g ,b);
          //Serial.println('r'+r+'g'+g+'b'+b);
          //strip.setPixelColor(led, 241,185,35);
          //strip.setPixelColor(x, strip.Color(rgbArray[2][x][0], rgbArray[2][x][1], rgbArray[2][x][2]));
          //rgbArray[0][0][0] = 1;
          //strip.setPixelColor(x, strip.Color(0,150.0,0.0));
                 
          led++;
        }
        //delay(1000);
        // change direction
        down = down ? false : true;
      }
      strip.show();
      
      /*if (blinking < 5) {
        delay(50);
      } else {8*/
        delay(550);
         //colorWipe(strip.Color(0, 0, 0), 150, false); // OFF/*         
      //}
      
    
  }  
  

  //delay(60000);
  
  //colorWipe(strip.Color(127, 50, 0), 50, true); // Blue
  //colorWipe(strip.Color(127, 127, 127), 100, false); // WHITE/*
  //colorWipe(strip.Color(0, 255, 0), 50, true); // Green
  //colorWipe(strip.Color(0, 0, 0), 100, false); // OFF/*
  
  //delay(1000000);    
    
   // delay(10000000);  
  // Send a theater pixel chase in...
  /*theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  //theaterChaseRainbow(50);
*/  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, bool meet) {
  
  if (!meet)
  {
    for (int x=0; x < 11; x++) {    
       for (int y=0; y < 36; y++) {     
         strip.setPixelColor((x*36)+ y, c);     
       }
       strip.show();
       delay(wait); 
    }
  }
  else
  {
    down = false;
    for (int y=0; y < 36; y++) {    
       for (int x=0; x < 11; x++) {     
         
         // meeting in the middle
         strip.setPixelColor((x*36)+ y, c);     
         
       }
       strip.show();
       
       down = (down==true) ? false : true;  
       
       delay(wait);      
       
    }
   }

}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
