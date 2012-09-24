//NumCounter
//Use the 7 segment display to count a series of numbers
//Reduce the number of pins from the arduino to the display
//  by using an 8 bit shift register - 74HC595.
//dspinoz@spinoz.com.au
//http://arduino.cc/en/Tutorial/ShftOut11

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() 
{
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() 
{
  delay(1000);
  digitalWrite(1, HIGH);
  
  // take the latchPin low so 
  // the LEDs don't change while you're sending in bits
  digitalWrite(latchPin, LOW);
  
  // shift out some bits
  shiftOut(dataPin, clockPin, MSBFIRST, 0); 
  
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  
  delay(1000);
  
  
  // take the latchPin low so 
  // the LEDs don't change while you're sending in bits
  digitalWrite(latchPin, LOW);
  
  // shift out some bits
  shiftOut(dataPin, clockPin, MSBFIRST, 7); 
  
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(1, LOW);
}
