/* For use with the 8 LED Strip of Adafruit NeoPixel LEDs although it should theo work for any of the Adafruit NeoPixels that are 5050 size.   
 * Color Codes for Serial Port:
 *  
 *  A = Turn off all LEDs
 *  B = Set all LEDs to Red
 *  C = Set all LEDs to Green
 *  D = Set all LEDs to Blue
 *  E = Set all LEDs to Rainbow?!?!?!
 *  F = Set all LEDs to White
 * 
 */
#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 255

//PWM ports on Arduino to connect to the LED strips
#define STRIP_ONE 5
#define STRIP_TWO 6

//NumOfPixels
#define NUM_OF_PIXELS_ONE 8
#define NUM_OF_PIXELS_TWO 8

Adafruit_NeoPixel StripOne = new Adafruit_NeoPixel(NUM_OF_PIXELS_ONE, STRIP_ONE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTwo = new Adafruit_NeoPixel(NUM_OF_PIXELS_TWO, STRIP_TWO, NEO_GRB + NEO_KHZ800);

//Colors
uint32_t blank = StripOne.Color(0, 0, 0);
uint32_t white = StripOne.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
uint32_t red = StripOne.Color(BRIGHTNESS, 0, 0);
uint32_t green = StripOne.Color(0, BRIGHTNESS, 0);
uint32_t blue = StripOne.Color(0, 0, BRIGHTNESS);
uint32_t yellow = StripOne.Color(BRIGHTNESS, BRIGHTNESS, 0);
uint32_t magenta = StripOne.Color(BRIGHTNESS, 0, BRIGHTNESS);
uint32_t cyan = StripOne.Color(0, BRIGHTNESS, BRIGHTNESS);


void setup() {
Serial.begin(9600); //Sets bits/sec to 9600 and begins serial port used to communicate between the arduino and the roborio
 StripOne.begin(); 
 StripTwo.begin();

 StripOne.show(); //According to some documentation, should cause strips to not be lit up.
 StripTwo.show();
}

void loop() {
  if(Serial.available() > 0) //available() returns # of bytes that can be read so it being greater than 0 means that there is data to read
  {
    interpret(Serial.read());
  }
}

//Idea completely stolen from Alexis Renderos, will take a character written to the Arduino via the Serial port and interpret that into a specific pattern
void interpret(char x) { 
  switch(x)
  {
    case "A":
      colorAllStrips(blank); 
      break;
    case "B":
      colorAllStrips(red);
      break;
    case "C":
      colorAllStrips(green);
      break;
    case "D":
      colorAllStrips(blue);
      break;
    case "E":
      rainbowStrip(StripOne);
      rainbowStrip(StripTwo);
      break;
    case "F":
      colorAllStrips(white);
      break;
  }
}

void colorStrip(Adafruit_NeoPixel strip, uint32_t c)
{
  for(var i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show(); //Sets all of the pixels and then updates the strip to reflect that.
  }
}

void colorAllStrips(uint32_t c)
{
  colorStrip(StripOne, c);
  colorStrip(StripTwo, c);
}

void rainbowStrip(Adafruit_NeoPixel strip) //should theo make all of the pixels a different color.
{
  for(var i = 0; i < strip.numPixels(); i++)
  {
    uint32_t c = strip.Color(random(0, 255), random(0, 255), random(0, 255));
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void colorWithDelay(Adafruit_NeoPixel strip, uint32_t c, int delay) //Same as colorStrip but has a delay between setting the pixels so it creates a fade in effect.
{
  for(var i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(delay); 
  }
}

