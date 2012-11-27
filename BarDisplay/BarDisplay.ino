/*
  BarDisplay - Show a bar value on a series of LEDs
               connected to digital pins
*/

#define pStartLED 2
#define pEndLED 7

void setup() 
{
  for (size_t i = pStartLED; i <= pEndLED; i++)
  {
    pinMode(i, OUTPUT);
  }  
}

void loop() 
{
  // set the LEDs on
  for (size_t i = pStartLED; i <= pEndLED; i++)
  {
    digitalWrite(i, HIGH);
  }  
  
  delay(1000);              // wait for a second
  
  // set the LEDs off
  for (size_t i = pStartLED; i <= pEndLED; i++)
  {
    digitalWrite(i, LOW);
  }  
  
  delay(1000);              // wait for a second
}
