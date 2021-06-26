// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <Wire.h>

int go =0;

int vent;

int mode;

int depart;

int fin;

int debut;

int gender=2;

#define LED_STRIP_WIND   3

#define LED_COUNT 96

Adafruit_NeoPixel wind(LED_COUNT, LED_STRIP_WIND, NEO_GRB + NEO_KHZ800);


void setup()
{
  

  wind.begin();
  wind.show(); 
  wind.setBrightness(255);
  
 
  Wire.begin(8);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
           // start serial for output
}

void loop()
{ 



if (go == 1)
{


if (mode == 0 or mode==1)
{
 

if (vent <= 1)
{
  debut = 19;
   fin = 22;
}

else if ( 1 < vent && vent <=5)
{
  debut = 17;
   fin = 24;

}

else if( 5< vent && vent <= 10)
{
  debut = 15;
  fin = 26;
}
else if( 10< vent && vent <= 15)
{
  debut =  13;
  fin = 28;
}
else if( 15< vent && vent <= 20)
{
  debut = 11;
  fin = 30;
}
else if( 20< vent && vent <= 25)
{
  debut = 9;
  fin = 32;
}
else if( 25< vent && vent <= 30)
{
  debut = 7;
  fin = 34;
}
else if( 30< vent && vent <= 35)
{
  debut = 5;
  fin = 36;
}
else if( 35< vent && vent <= 40)
{
  debut = 3;
  fin = 38;
}
else if( 40< vent && vent <= 45)
{
  debut = 1;
  fin = 40;
}
 else
{
  debut =0;
  fin = 43;
}

fwind2(vent);
}



else if (mode == 2)
{
  colorWipe(wind.Color(255,   0,   0), 50); // Red
  colorWipe(wind.Color(  0, 255,   0), 50); // Green
  colorWipe(wind.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(wind.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(wind.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(wind.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

  wind.clear();
  wind.show();
  
}

else if (mode==3)
{
  genderReveal();
}


}

}








 void fwind2 (int vent)
 {
   uint32_t green =  wind.ColorHSV(21845,255,50);

int vert = 21845;
int sat = 255;
int val = 200;

  for (int i =debut ; i<fin;i++)
  {
  wind.clear();
   wind.setPixelColor(i+5,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.setPixelColor(i+4,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  
  wind.setPixelColor(i+3,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+2,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+1,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  wind.setPixelColor(i,wind.gamma32(wind.ColorHSV(vert,sat,val)));

   wind.setPixelColor(i+53,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.setPixelColor(i+52,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  
  wind.setPixelColor(i+51,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+50,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+49,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  wind.setPixelColor(i+48,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.show();
 // i = i+1;
 if (vent < 70)
 {
 delay(80-(vent*2));
 }
 else 
 {
  delay(10);
 }
  }
 


  for (int i =fin ; i>debut;i--)
  {
   wind.clear();
   wind.setPixelColor(i,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.setPixelColor(i+1,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  
  wind.setPixelColor(i+2,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+3,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+4,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  wind.setPixelColor(i+5,wind.gamma32(wind.ColorHSV(vert,sat,val)));


  wind.setPixelColor(i+48,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.setPixelColor(i+49,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  
  wind.setPixelColor(i+50,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+51,wind.gamma32(wind.ColorHSV(vert,sat,val-150)));
  wind.setPixelColor(i+52,wind.gamma32(wind.ColorHSV(vert,sat,val-100)));
  wind.setPixelColor(i+53,wind.gamma32(wind.ColorHSV(vert,sat,val)));
  wind.show();
 // i = i+1;
 if (vent < 70)
 {
 delay(80-(vent*2));
 }
 else 
 {
  delay(10);
 }
  }

 }


  

/////////////// Fonction appelée dès qu'une donnée est reçue via le bus I2C 

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
        // print the character
  }
  int x = Wire.read();// receive byte as an integer
 if (x != NULL)
    {
 
    if(x==200)
    {
      mode = 1;
    }

    else if (x==199)
    {
      mode = 2;
    }

    else if (x==198)
    {
      mode =0;
    }

    else if (x==197)
    {
      gender=0;
    }
    else if (x==196)
    {
      gender=1;
    }
    else if(x==195)
    {
      mode =3;
    }

    else
    {
      vent =x;
      
    }

  
  go =1;
    }
 
}

void genderReveal()
{
    int sat = 255;
int val = 200;
wind.clear();
int color;

 if (gender==0)
  {
      color =40000;
    
  }
  else if (gender ==1)
  {
    color = 60074;
    
  }
 
 

  for (int i =48; i>0; i--)
  {
    wind.setPixelColor(i,wind.gamma32(wind.ColorHSV(color,sat-(i*5),val)));
    wind.setPixelColor(i+48,wind.gamma32(wind.ColorHSV(color,sat-(i*5),val)));
    wind.show();
    delay(25);

    if (i == 1)
    {
      for (int j =0; j<5; j++)
      {
      wind.fill(wind.gamma32(wind.ColorHSV(color,255,100)),0,96);
      
      wind.show();
     
      delay(1000);
     
      wind.clear();
      wind.show();
      delay(1000);
      }
      
    }
  }
}

////////////////////////////// Fonctions du mode demo

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<wind.numPixels(); i++) { // For each pixel in strip...
    wind.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    wind.show();                          //  Update strip to match
    delay(wait/2);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      wind.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<wind.numPixels(); c += 3) {
       wind.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      wind.show(); // Update strip with new contents
      delay(wait/2);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<wind.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / wind.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      wind.setPixelColor(i, wind.gamma32(wind.ColorHSV(pixelHue)));
    }
   wind.show(); // Update strip with new contents
    delay(wait/2);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
     wind.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<wind.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / wind.numPixels();
        uint32_t color = wind.gamma32(wind.ColorHSV(hue)); // hue -> RGB
       wind.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      wind.show();                // Update strip with new contents
      delay(wait/2);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
