// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <Adafruit_NeoPixel.h>
/*#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif*/

#include <Wire.h>

int go;

 int mode;

int pluie;

String msgr;

int goutte;

int gender;

int bleu = 40000;
int sat = 234;
int val = 200;



#define LED_STRIP_RAIN   3

#define LED_COUNT 48

Adafruit_NeoPixel rain(LED_COUNT, LED_STRIP_RAIN, NEO_GRB + NEO_KHZ800);



void setup()
{

  rain.begin();
  rain.show(); 
  rain.setBrightness(200);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  
      
}

void loop()
{  //Serial.println(mode);

if (go == 1)
{


  
if(mode==0 or mode ==1)
 {





/*switch(pluie) {
  case 0: goutte = 100;
    // code block
    break;
  case 1: goutte = 60;
    // code block
    break;
  case 2: goutte = 35;
    // code block
    break;
  case 3: goutte = 21;
    // code block
    break;
    case 4: goutte = 17;
    // code block
    break;
    case 5: goutte = 14;
    // code block
    break;
    case 6: goutte = 11;
    // code block
    break;
    case 7: goutte = 10;
    // code block
    break;
  default: goutte = 8;
    // code block
}*/

if (pluie==0)
{
  rain.clear();
  rain.show();
}
else if (pluie==1)
{
  goutte=60;
  frain(goutte);
}
else if (pluie==2)
{
  goutte=35;
  frain(goutte);
}

else if (pluie==3)
{
  goutte=21;
  frain(goutte);
}

else if (pluie==4)
{
  goutte=17;
  frain(goutte);
}
else if (pluie==5)
{
  goutte=14;
  frain(goutte);
}
else if (pluie==6)
{
  goutte=11;
  frain(goutte);
}
else if (pluie==7)
{
  goutte=10;
  frain(goutte);
}
else 
{
  goutte=8;
  frain(goutte);
}





 }



 



else if(mode==2)
{
  

 
  
  colorWipe(rain.Color(255,   0,   0), 50); // Red
  colorWipe(rain.Color(  0, 255,   0), 50); // Green
  colorWipe(rain.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(rain.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(rain.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(rain.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

  rain.clear();
  rain.show();
  
}

else if (mode==3)
{
  genderReveal();
}




}
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
     
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
      pluie =x;
      
    }

  
  go =1;
    }
  
  
  }





void frain(int goutte)
  {




if (goutte == 100)
{
  rain.clear();
  rain.show();
}


else if (goutte==60)
{
  val=255;



  for(int a=0; a<1; a++) {  // Repeat 10 times...
    for(int b=0; b<goutte; b++) { //  'b' counts from 0 to 2...
      rain.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int i=b; i<rain.numPixels(); i += goutte) {

 rain.clear();
rain.setPixelColor( i+0, rain.gamma32(rain.ColorHSV(bleu,sat,val)));
rain.setPixelColor( i-1, rain.gamma32(rain.ColorHSV(bleu,sat,val-100)));
rain.setPixelColor( i-2, rain.gamma32(rain.ColorHSV(bleu,sat,val-150)));
rain.setPixelColor( i-3, rain.gamma32(rain.ColorHSV(bleu,sat,val-175)));
rain.setPixelColor( i-4, rain.gamma32(rain.ColorHSV(bleu,sat,val-188)));
rain.setPixelColor( i-5, rain.gamma32(rain.ColorHSV(bleu,sat,val-195)));
rain.setPixelColor( i-6, rain.gamma32(rain.ColorHSV(bleu,sat,val-205)));
rain.setPixelColor( i-7, rain.gamma32(rain.ColorHSV(bleu,sat,val-215)));
rain.setPixelColor( i-8, rain.gamma32(rain.ColorHSV(bleu,sat,val-220)));
rain.setPixelColor( i-9, rain.gamma32(rain.ColorHSV(bleu,sat,val-225)));
rain.setPixelColor( i-10, rain.gamma32(rain.ColorHSV(bleu,sat,val-230)));
rain.setPixelColor( i-11, rain.gamma32(rain.ColorHSV(bleu,sat,val-235)));
rain.setPixelColor( i-12, rain.gamma32(rain.ColorHSV(bleu,sat,val-240)));
rain.setPixelColor( i-13, rain.gamma32(rain.ColorHSV(bleu,sat,val-243)));
rain.setPixelColor( i-14, rain.gamma32(rain.ColorHSV(bleu,sat,val-246)));  
rain.setPixelColor( i-15, rain.gamma32(rain.ColorHSV(bleu,sat,val-249)));

rain.show();
delay(10+(i*1.1));
}
}
}
}


else
{

  val=200;

  
 /* for(int a=0; a<1; a++) {  // Repeat 10 times...*/
    for(int b=0; b<goutte; b++) { //  'b' counts from 0 to 2...
      rain.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int i=b; i<rain.numPixels(); i += goutte) {
        
rain.setPixelColor( i, rain.gamma32(rain.ColorHSV(bleu,sat,val)));
rain.setPixelColor( i-1, rain.gamma32(rain.ColorHSV(bleu,sat,val-100)));
rain.setPixelColor( i-2, rain.gamma32(rain.ColorHSV(bleu,sat,val-125)));
rain.setPixelColor( i-3, rain.gamma32(rain.ColorHSV(bleu,sat,val-135)));
rain.setPixelColor( i-4, rain.gamma32(rain.ColorHSV(bleu,sat,val-145)));
rain.setPixelColor( i-5, rain.gamma32(rain.ColorHSV(bleu,sat,val-155)));
rain.setPixelColor( i-6, rain.gamma32(rain.ColorHSV(bleu,sat,val-160)));
rain.setPixelColor( i-7, rain.gamma32(rain.ColorHSV(bleu,sat,val-165)));
rain.setPixelColor( i-8, rain.gamma32(rain.ColorHSV(bleu,sat,val-170)));
rain.setPixelColor( i-9, rain.gamma32(rain.ColorHSV(bleu,sat,val-172)));
rain.setPixelColor( i-10, rain.gamma32(rain.ColorHSV(bleu,sat,val-174)));
rain.setPixelColor( i-11, rain.gamma32(rain.ColorHSV(bleu,sat,val-176)));


      }
      rain.show(); 
      delay(40);
        
    }
  

}
  }


void genderReveal()
{

int sat = 0;
int val = 200;
rain.clear();
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
    rain.setPixelColor(i,rain.gamma32(rain.ColorHSV(color,sat-(i*5),val)));
    rain.show();
    delay(50);

    if (i == 1)
    {
      for (int j =0; j<5; j++)
      {
      rain.fill(rain.gamma32(rain.ColorHSV(color,255,100)),0,47);
      
      rain.show();
      delay(1000);
      rain.clear();
      rain.show();
      delay(1000);
      }
      
    }
  }

}

  


  void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<rain.numPixels(); i++) { // For each pixel in strip...
    rain.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    rain.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      rain.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<rain.numPixels(); c += 3) {
        rain.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      rain.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
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
    for(int i=0; i<rain.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / rain.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      rain.setPixelColor(i, rain.gamma32(rain.ColorHSV(pixelHue)));
    }
    rain.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      rain.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<rain.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / rain.numPixels();
        uint32_t color = rain.gamma32(rain.ColorHSV(hue)); // hue -> RGB
       rain.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      rain.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}



void serial() {
  msgr = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msgr += (char)Serial.read();
    }
    Serial.flush();
  }
}
