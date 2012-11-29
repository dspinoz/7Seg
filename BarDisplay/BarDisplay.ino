/*
  BarDisplay - Show a bar value on a series of LEDs
               connected to digital pins
*/

#include <TinyGPS.h>

TinyGPS gps;

#define led 13
#define pStartLED 2
#define pEndLED 7

void setup() 
{
  Serial.begin(57600);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  for (size_t i = pStartLED; i <= pEndLED; i++)
  {
    pinMode(i, OUTPUT);
  }  
}

void show(size_t num)
{
  // set the LEDs on
  size_t i = 0, j=0;
  for (i = pStartLED, j=0; i <= pEndLED && j < num; i++, j++)
  {
    digitalWrite(i, HIGH);
  }  
  
  for (; i <= pEndLED; i++)
  {
    digitalWrite(i, LOW);
  }   
}

void showFromSpeed(float i)
{
  int leds = 0;
  
  if (i >= 20)
  {
    //green
    leds++;
  }
  
  if (i >= 60)
  {
    //green
    leds++;
  }
  
  if (i >= 80)
  {
    //green
    leds++;
  }
  
  if (i >= 90)
  {
    //green
    leds++;
  }
  
  if (i >= 100)
  {
    //yellow
    leds++;
  }
  
  if (i >= 110)
  {
    //red
    leds++; 
  }
  
  show(leds);
}

void loop() 
{
  digitalWrite(led, LOW);
  
  while (Serial.available())
  {
    digitalWrite(led, LOW);
    char c = Serial.read();
    if (gps.encode(c))
    {
      digitalWrite(led, HIGH);
      showFromSpeed((int)gps.f_speed_kmph());
    }
  }
}
