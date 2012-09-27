//NumCounter
//Use a 4 Digit 7 segment display to count a series of numbers
//Reduce the number of pins from the arduino to the display
//  by using an 8 bit shift register - 74HC595.
//dspinoz@spinoz.com.au
//http://arduino.cc/en/Tutorial/ShftOut11

//PINS for the digits
#define pDIG1 2
#define pDIG2 3
#define pDIG3 4
#define pDIG4 5
// PINS for the shit register
#define pSR_STCP 8  //latch
#define pSR_SHCP 12 //clock
#define pSR_DS 11   //data

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

void displayClear()
{
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
  
  //turn off the segments by setting the latch
  digitalWrite(pSR_STCP, LOW);
  //sending in bits (all off)
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, 0); 
  //releasing the bits 
  digitalWrite(pSR_STCP, HIGH);
  
}

void setup() {
  
  pinMode(pDIG1, OUTPUT);
  pinMode(pDIG2, OUTPUT);
  pinMode(pDIG3, OUTPUT);
  pinMode(pDIG4, OUTPUT);
  
  //set pins to output so you can control the shift register
  pinMode(pSR_STCP, OUTPUT);
  pinMode(pSR_SHCP, OUTPUT);
  pinMode(pSR_DS, OUTPUT);
  
  displayClear();
  
}

void displayNum(int num, int sleep)
{
  int sleepInc = sleep / 4;
  
  int dig1 = num % 10;
  int dig2 = (num / 10) % 10; 
  int dig3 = (num / 100) % 10;
  int dig4 = (num / 1000) % 10;
  
  delay(sleepInc);
  displayClear();
  
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, LOW);
    
  //set segments the segments by setting the latch
  digitalWrite(pSR_STCP, LOW);
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, displayPinVals[dig1]); 
  digitalWrite(pSR_STCP, HIGH);
    
  delay(sleepInc);
  displayClear();

  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, LOW);
  digitalWrite(pDIG4, HIGH);
    
  digitalWrite(pSR_STCP, LOW);
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, displayPinVals[dig2]); 
  digitalWrite(pSR_STCP, HIGH);
    
  delay(sleepInc);
  displayClear();
    
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, LOW);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
    
  digitalWrite(pSR_STCP, LOW);
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, displayPinVals[dig3]); 
  digitalWrite(pSR_STCP, HIGH);
    
  delay(sleepInc);
  displayClear();
  
  digitalWrite(pDIG1, LOW);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
    
  digitalWrite(pSR_STCP, LOW);
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, displayPinVals[dig4]); 
  digitalWrite(pSR_STCP, HIGH);
}

int n=0;
void loop()
{
  displayNum(n, 20);
  n++;
  
  if (n > 10000)
  {
    n=0; 
  }
}

