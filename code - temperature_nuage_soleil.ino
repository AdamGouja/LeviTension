

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#include <Wire.h>

#include <SoftwareSerial.h>

#include <Arduino.h>


//PIN RUBAN LED

#define LED_STRIP_TEMP_PIN   5

#define LED_STRIP_CLOUD_PIN   6

#define SUN_PIN 7


 // Paramètres leds
 
#define LED_CLOUD 14

#define LED_COUNT 48


//PIN bluetooth

#define rx_PIN 10 // => HC05: tx
#define tx_PIN 11 // => HC05: rx
#define cmd 8

//PIN interruption mode

#define PIN_MODE0 2
#define PIN_MODE1 3
#define PIN_MODE2 18


//Délcaration des rubans de leds
Adafruit_NeoPixel temp(LED_COUNT, LED_STRIP_TEMP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cloud(LED_CLOUD, LED_STRIP_CLOUD_PIN, NEO_GRB + NEO_KHZ800);


// Déclaration du module bluetooth sur un port "serial"

SoftwareSerial BTserial(rx_PIN, tx_PIN); // RX | TX of Arduino

// 
int fin_prevision;

String nom = "Arduino";

bool wind_ready;

bool rain_ready;

bool temp_ready;


String msgr;

 String msga;

String ville;

String vent;

String pluie;

String degres;

String soleil;

String nuage;

String airQuality;

int air;

int air2;

String phrase;

int gender =2;

int ville1=0;

volatile int mode;
volatile int i =0;
volatile int j =0;
volatile int k =0;
volatile int i2c;




int conf = 1; // 1 pour mode normal, 0 pour mode AT (configuration du bluetooth)

int maj=0;

volatile int ready1=-1;

long temps;

int tempMin;


boolean precipitation;
int tempMax;

// BTconnected will = false when not connected and true when connected
boolean BTconnected = false;

// The setup() function runs once each time the micro-controller starts

void setup()
{

 // Configuration PIN mode0 en entrée
pinMode(PIN_MODE0,INPUT);
digitalWrite(PIN_MODE0, HIGH);
// Configuration PIN mode1 en entrée
pinMode(PIN_MODE1,INPUT);
digitalWrite(PIN_MODE1, HIGH);
// Configuration PIN mode0 en entrée
pinMode(PIN_MODE2,INPUT);
digitalWrite(PIN_MODE2, HIGH);

// Déclaration des interruptions
attachInterrupt(0,f_mode0,CHANGE);
attachInterrupt(1,f_mode2,CHANGE);
attachInterrupt(5,f_mode1,CHANGE);

  temp.begin();
  temp.show();  
  temp.setBrightness(255);

  cloud.begin();
  cloud.show();  
  cloud.setBrightness(255);
  //Initialisation I2C bus pour le vent et la pluie
 Wire.begin(); 


  // start serial communication with the serial monitor on the host computer

// set input through EN pin
pinMode(cmd, OUTPUT);
digitalWrite(cmd, HIGH);

pinMode(SUN_PIN,OUTPUT);

//Serial turns on in 1 second
delay(1000);

// wait until the HC-05 has made a connection
while (!BTconnected)
{
if (digitalRead(cmd) == HIGH) { BTconnected = true; };
}

Serial.begin(9600);


  BTserial.begin(9600); // SEUL TRUC UTILE
  ecrirebluetooth("Welcome to Levi'Tension menu");
  ecrirebluetooth("please enter a city name and press 0 for the actual weather, 1 for the weather forecast and 2 for de demo");
}




void loop()
{

  if (ville1 == 0)    
  {
  temps = 0;
  }

 
 
  lirebluetooth(); 


if (ready1==0)
{
  if (gender != 2)
  {
    mode=3;
    sendI2C(195,4);
    sendI2C(195,8);
    ecrirebluetooth("mode genderReveal");
   
  }
}

  
  
 if (((msga.charAt(0) == 'z') and (msga.charAt(1)=='z') and (msga.charAt(2)=='z')) or ((millis() - temps) > 600000))
     { 
      if(msga!="")
      {
      ville = msga.substring(3,msga.length());
      }
      
      Serial.print(ville);
     
      ville1 = 1;
      temps = millis();
    
      
    }

 else  if (msga.charAt(0) == '1')
  {
    mode = 1;
    fin_prevision=0;
    int i = 200;
    Serial.print("ppp");
    sendI2C(i, 4);
    sendI2C(i, 8);
    ecrirebluetooth("forecast mode");
    ecrirebluetooth("Please choose up a city : zzzCityName");
    ready1=-1;
    
  }

 else if ((msga.charAt(0) == '2') or ready1==2)
 {
  mode =2;
  int i = 199;
  sendI2C(i, 4);
  sendI2C(i, 8);
  ecrirebluetooth("demo mode");
  ecrirebluetooth("(You have to wait");
  ready1 = -1;

  
 }

  else if ((msga.charAt(0) == '0') or ready1==1)
 {
  mode =0;
  Serial.print("aaa");
  int i =198;
  sendI2C(i,4);
  sendI2C(i,8);
 
  ecrirebluetooth("Current weather selected");
  ecrirebluetooth("Please choose up a city : zzzCityName");
  ready1=-1;
  
 }

 else if((msga.charAt(0)=='b') and (msga.charAt(1)=='o') and (msga.charAt(2)=='y'))
 {
  gender =0;
  sendI2C(197,4);
  sendI2C(197,8);
 }
  else if((msga.charAt(0)=='g') and (msga.charAt(1)=='i') and (msga.charAt(2)=='r') and (msga.charAt(3)=='l'))
 {
  gender = 1;
  sendI2C(196,4);
  sendI2C(196,8);
 }

  



if(mode==0)
{
   
  if(ville1 == 1)
 {


  

  lireraspberry();
  
 

  
 if ((msgr.charAt(0) == 'b') and (msgr.charAt(1)=='b') and (msgr.charAt(2)=='b'))
 {
 
  int i = trad_msgr(pluie,msgr);
  sendI2C(i,4);
  offrain(i);
  Serial.print("ok3");
  Serial.flush();
  delay(50);
    
 }

 if ((msgr.charAt(0) == 'c') and (msgr.charAt(1)=='c') and (msgr.charAt(2)=='c'))
 {
  
  int i = trad_msgr(vent,msgr);
  sendI2C(i,8);
  Serial.print("ok2");
  Serial.flush();
  delay(50);
  
  
 }


if ((msgr.charAt(0) == 'd') and (msgr.charAt(1)=='d') and (msgr.charAt(2)=='d'))
 {
  
  int b = trad_msgr(degres,msgr);
  
  ftemp(b);
  Serial.print("ok1");
  Serial.flush();
  delay(50);
  
  
 }

if ((msgr.charAt(0) == 'e') and (msgr.charAt(1)=='e') and (msgr.charAt(2)=='e'))
 {
  soleil ="";
  soleil = msgr.substring(3,msgr.length());
  fsun(soleil);
  Serial.print("ok5");
  Serial.flush();
  delay(50);
  
  
 }

 if ((msgr.charAt(0) == 'f') and (msgr.charAt(1)=='f') and (msgr.charAt(2)=='f'))
 {
  
  int i = trad_msgr(nuage,msgr);
 
  fcloud(i);
  Serial.print("ok4");
  Serial.flush();
  delay(50);
   
 }
 


  
}
}


/// MODE PREVISION  

else  if(mode==1)
  {
  
  if(ville1==1)
  {
    
   
    lireraspberry();
  
  
  if ((msgr.charAt(0) == 'w') and (msgr.charAt(1)=='w') and (msgr.charAt(2)=='w'))
 {
 
  int b = trad_msgr(degres,msgr);
  tempMin = b;
   
  Serial.print("ok2");
  Serial.flush();
  temp_ready=false;
  
 }


else if ((msgr.charAt(0) == 'v') and (msgr.charAt(1)=='v') and (msgr.charAt(2)=='v'))
 {
 
  int b = trad_msgr(degres,msgr);
  tempMax=b;
  
  Serial.print("ok3");
  Serial.flush();
  
 }

 
else if ((msgr.charAt(0) == 'n') and (msgr.charAt(1)=='n') and (msgr.charAt(2)=='n'))
 {
  
  
  int b =trad_msgr(airQuality,msgr);
  air = b;
  
  Serial.print("ok4");
  Serial.flush();
  
 }

 
else if ((msgr.charAt(0) == 'm') and (msgr.charAt(1)=='m') and (msgr.charAt(2)=='m'))
 {
 
  int b = trad_msgr(degres,msgr);
  fsun("mode1");
  
  Serial.print("ok5");
  Serial.flush();
  delay(50);
 }

 
else if ((msgr.charAt(0) == 'l') and (msgr.charAt(1)=='l') and (msgr.charAt(2)=='l'))
 {
 
 int i = trad_msgr(vent,msgr);
  sendI2C(i,8);
  Serial.print("ok6");
  Serial.flush();
  
 }

else if ((msgr.charAt(0) == 'k') and (msgr.charAt(1)=='k') and (msgr.charAt(2)=='k'))
 {
 
 int i = trad_msgr(pluie,msgr);
 offrain(i);
  sendI2C(i,4);
  Serial.print("ok7");
  Serial.flush();
  

 }

else if ((msgr.charAt(0) == 'j') and (msgr.charAt(1)=='j') and (msgr.charAt(2)=='j'))
 {
 
 int i = trad_msgr(pluie,msgr);

  Serial.print("ok8");
  Serial.flush();
  
 
 }

else if ((msgr.charAt(0) == 's') and (msgr.charAt(1)=='s') and (msgr.charAt(2)=='s'))
 {
 
  int i = trad_msgr(nuage,msgr);
  fcloud(i);
  Serial.print("ok9");
  Serial.flush();
 
 }

else if ((msgr.charAt(0) == 'r') and (msgr.charAt(1)=='r') and (msgr.charAt(2)=='r'))
 {
  phrase = msgr.substring(3,msgr.length());

  Serial.print("ok10");
  Serial.flush();
 
 }


else if ((msgr.charAt(0) == 't') and (msgr.charAt(1)=='t') and (msgr.charAt(2)=='t'))
 {
  precipitation = msgr.substring(3,msgr.length());
  
  Serial.print("ok11");
  Serial.flush();
  fin_prevision=1;
  ecrirebluetooth("Module ready");
  
  
 }

 fsun("1");

 if (fin_prevision==1)
 {
   ftemp(0);
   temp.clear();
   temp.show();

  }
  }

  }
  

  else if (mode==2)
  {
    
    fsun("1");
    demo();
    temp.clear();
    temp.show();
    }

  else if(mode==3)
  {
    fsun("1");
    genderReveal();
  }
  
}

 


/// PROGRAMMES COMMUNICATION ////////////////////////////////////////////////////////////////////////////////////////////////


int trad_msgr(String param, String msg)
{
  param = "";
  param = msg.substring(3,msg.length());
  
  int temp1 = (int)param.toFloat();
  
  return temp1;
}

void lirebluetooth () // permet de lire les messages de l'utilisateur
{
   msga = ""; // On supprime l'ancien message
  if (BTserial.available()) {
    delay(10);
    while (BTserial.available() > 0) {
      msga +=(char)BTserial.read();  // on stocke les caractères dans une chaîne de caractères
    }
    
  
    BTserial.flush();// on supprime les données après utilisation 
  }
}

void ecrirebluetooth (String msga) // permet d'écrire des messages à l'utilisateur
{
   
  
    BTserial.println(msga);   
    BTserial.flush();
  
}



void lireraspberry() {
  msgr = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msgr += (char)Serial.read();
    }
    Serial.flush();
  }
}

void sendI2C(int i, int carte)
{
  
  Wire.beginTransmission(carte); // on veut communiquer avec la carte n°"carte"
  Wire.write(i);              // on envoie un bit de donnée  
  Wire.endTransmission(); // on referme la transmission
}

void receiveI2C()
{
  while(1 < Wire.available()) // verifie le nombre d'octets disponibles pour la lecture
  {
     
        // print the character
  }
 
  int x = Wire.read();// on reçoit un bit comme un entier
  if (x == 222)
  {
    rain_ready=1;
  }
  else if (x== 333)
  {
    wind_ready=1;
  }
}


// ROUTINE POUR ETEINDRE LA PLUIE : 

void offrain(int i) // i correspond aux mm de pluie
{
   if(i==0)
  {
    pinMode(8,OUTPUT);// on déclare la broche 8 en sortie
    delay(5);
    digitalWrite(8,LOW);// on effectue un reset
    delay(5);
    digitalWrite(8,HIGH);// on revient à la normale
    
  }
 
}

// ROUTINES INTERRUPTIONS ///////////////////////////////////////////////////////////////////////////

void f_mode0()
{
  i++;
  if (i >1)
  {
 
  ready1=0;
 i=0;
  }
}

void f_mode1()
{
  j++;
  if(j>300)
  {
 
  ready1=1;
  j=0;
  }  
}

void f_mode2()
{
  k++;
  if(k>300)
  {

  ready1=0;
  


  k=0;

  }
  
}


// PROGRAMME LEDS /////////////////////////////////////////////////////////////////////////////////////////////

void fsun(String etat) // la variable etat représente le soleil
{
  if(etat=="1") // soleil levé
  {
    digitalWrite(SUN_PIN,HIGH); // on alimente la bobine en +12V
  }
  else if(etat=="0") // soleil couché
  {
    digitalWrite(SUN_PIN,LOW);// on ouvre le relai
  }
}

void ftemp(int temperature)
{

  if (mode==0)
  {

  temp.clear();
  temp.show();

  temperature = temperature+10;

for (int i =0; i<temperature+1;i++)
{

  if (i < 15 )
  {
  temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(43690 +(i*500))));
  }
  else if ( (15 <= i) && (i < 30))
  {
   
  temp.setPixelColor( i,255,255,(255-i*8));
    
  }
  else if ( (30 <= i) && (i <= 48))
  {
    //uint32_t color = temp.gamma32(temp.ColorHSV(63736 +((i-33)*100)));
    
    temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(9000 -((i-33)*600))));
  }

  temp.show();
  temp . setBrightness (20);
 
}
 }

else if (mode==1)
{
  temp.clear();
  temp.show();

  temperature = tempMin+10;

for (int i =0; i<temperature;i++)
{

  if (i < 15 )
  {
  temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(43690 +(i*500))));
  }
  else if ( (15 <= i) && (i < 30))
  {
   
  temp.setPixelColor( i,255,255,(255-i*8));
    
  }
  else if ( (30 <= i) && (i <= 48))
  {
    //uint32_t color = temp.gamma32(temp.ColorHSV(63736 +((i-33)*100)));
    
    temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(9000 -((i-33)*600))));
  }

  temp.show();
  temp . setBrightness (20);
 
}


delay(2000);

temp.clear();
temp.show();


 temperature = tempMax+10;

for (int i =0; i<temperature;i++)
{

  if (i < 15 )
  {
  temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(43690 +(i*500))));
  }
  else if ( (15 <= i) && (i < 30))
  {
   
  temp.setPixelColor( i,255,255,(255-i*8));
    
  }
  else if ( (30 <= i) && (i <= 48))
  {
    //uint32_t color = temp.gamma32(temp.ColorHSV(63736 +((i-33)*100)));
    
    temp.setPixelColor( i , temp.gamma32(temp.ColorHSV(9000 -((i-33)*600))));
  }

  temp.show();
  temp . setBrightness (20);
 
}
  
delay(2000);
temp.clear();
temp.show();

air2 =air;

uint32_t color;

if ( (0<= air2) && (air2 <=19))
{
   color = temp.Color(0,255,0);
}
else if ((19 < air2) && air2 <= 49)
{
  color = temp.Color(255,255,0);
}
else if(49 < air2  && air2 <=99)
{
  color = temp.Color(255,128,0);
}
else if(99 < air2 && air2 <=149)
{
  color = temp.Color(255,0,0);
}
else if(149 < air2 && air2 <=249)
{
  color = temp.Color(238,128,238);
}
else if (249< air2)
{
  color = temp.Color(0,0,128);
}

temp.fill(color);

temp.show();
temp . setBrightness (150);

delay(2000);
}
  
}




void fcloud(int i)
{

 for( int j =0; j<14;j++)
 {
 cloud.setPixelColor(j,cloud.gamma32(cloud.ColorHSV(43690,255*(i/100),255)));
 //cloud.setPixelColor(1,cloud.gamma32(cloud.ColorHSV(43690,255*(i/100),255)));
  cloud.setBrightness(5+(i*2.5));
 }


cloud.show();
 
}

void genderReveal()
{

int sat = 0;
int val = 200;
temp.clear();
cloud.clear();
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
    temp.setPixelColor(i,temp.gamma32(temp.ColorHSV(color,sat-(i*5),val)));
    temp.show();
    delay(50);

    if (i == 1)
    {
      for (int j =0; j<5; j++)
      {
      temp.fill(temp.gamma32(temp.ColorHSV(color,255,100)),0,47);
      cloud.fill(cloud.gamma32(cloud.ColorHSV(color,255,100)),0,14);
      temp.show();
      cloud.show();
      delay(1000);
      cloud.clear();
      temp.clear();
      cloud.show();
      temp.show();
      delay(1000);
      }
      
    }
  }

}

  





//DEMO
void demo()
{
  fcloud(100);
  colorWipe(temp.Color(255,   0,   0), 50); // Red
  colorWipe(temp.Color(  0, 255,   0), 50); // Green
  colorWipe(temp.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(temp.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(temp.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(temp.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

  temp.clear();
  temp.show();

  cloud.clear();
  cloud.show();

}







void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<temp.numPixels(); i++) { // For each pixel in strip...
    temp.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    temp.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      temp.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<temp.numPixels(); c += 3) {
        temp.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      temp.show(); // Update strip with new contents
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
    for(int i=0; i<temp.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / temp.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      temp.setPixelColor(i, temp.gamma32(temp.ColorHSV(pixelHue)));
    }
    temp.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      temp.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<temp.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / temp.numPixels();
        uint32_t color = temp.gamma32(temp.ColorHSV(hue)); // hue -> RGB
        temp.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      temp.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
