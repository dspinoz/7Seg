/*
  BarDisplay - Show a bar value on a series of LEDs
               connected to digital pins
*/

#define pStartLED 2
#define pEndLED 7

void setup() 
{
  Serial.begin(9600);
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

void ledPerc(size_t p, size_t minp, size_t maxp)
{
  if (p < minp)
  {
     show(0);
    return; 
  }
  
  int ledMax = pEndLED - pStartLED;
  
  float incr = (float)ledMax / (maxp-minp);
  
  int num = (p-minp) * incr;
  
  Serial.print(ledMax);
  Serial.print(" ");
  Serial.print(p);
  Serial.print(" ");
  Serial.print((p-minp));
  Serial.print(" ");
  Serial.print(incr);
  Serial.print("  ");
  Serial.print(num);
  Serial.println();
  
  show(num);
  
}

#define maxval 100
size_t i = 0;

void loop() 
{
  i++;
  if (i>maxval+30)
  {
    i=1;
  }
  
  ledPerc(i, 50, maxval);
  
  delay(100);
  
}
