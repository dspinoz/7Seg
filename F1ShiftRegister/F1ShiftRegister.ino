//F1ShiftRegister
//Use a shift register to control a series of LEDs
//dspinoz@spinoz.com.au
//http://arduino.cc/en/Tutorial/ShftOut11

//Pin connected to ST_CP of 74HC595
int latchPin = 7;
//Pin connected to SH_CP of 74HC595
int clockPin = 9;
////Pin connected to DS of 74HC595
int dataPin = 8;

//bits to set in order to display a number on the display
int displayPinVals[9] = { 0, 1, 3, 7, 15, 31, 63, 127, 255 };

void setup() 
{
  Serial.begin(9600);
  
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void displayLEDs(int num)
{
  Serial.println(num);
  
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits
    digitalWrite(latchPin, LOW);
    
    // shift out some bits
    //HIGH = off, LOW = on
    //binary not operator (~) to flip the bits
    shiftOut(dataPin, clockPin, MSBFIRST, displayPinVals[num]); 
    
    //take the latch pin high so the LEDs will turn off
    digitalWrite(latchPin, HIGH);
}


void loop() 
{
  for (int num = 0; num < 8; num++)
  {
    
    displayLEDs(num);
    
    delay(250);
  }
  
  Serial.println("---");
  
  
  for (int num = 8; num > 0; num--)
  {
    displayLEDs(num);
    
    delay(250);
  }
  Serial.println("===");
}
