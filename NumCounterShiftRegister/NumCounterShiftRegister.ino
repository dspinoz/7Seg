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

//bits to set in order to display a number on the display
char displayPinVals[10] = { 
  0x3F, //0
  0x6, //1
  0x5B, //2
  0x4F, //3
  0x66, //4
  0x6D, //5
  0x7D, //6
  0x07, //7
  0x7F, //8
  0x67 //9
};

void setup() 
{
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() 
{
  //Vals from 0 - 9
  for (int num = 0; num < 10; num++)
  {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits
    digitalWrite(latchPin, LOW);
    
    // shift out some bits
    //HIGH = off, LOW = on
    //binary not operator (~) to flip the bits
    shiftOut(dataPin, clockPin, MSBFIRST, ~displayPinVals[num]); 
    
    //take the latch pin high so the LEDs will turn off
    digitalWrite(latchPin, HIGH);
    
    delay(250);
  }
}
