//DisplayForces
//Use a 7 segment display to show the forces from an accelerometer MMA7341L
//dspinoz@spinoz.com.au


//PINS for the digits
#define pDIG1 2
#define pDIG2 3
#define pDIG3 4
#define pDIG4 5
// PINS for the shit register
#define pSR_STCP 8  //latch
#define pSR_SHCP 12 //clock
#define pSR_DS 11   //data
//PINS for MMA7341L
#define pSleep 6
#define pSelect 7
#define pX A1 //analog
#define pY A2 //analog
#define pZ A3 //analog

//Analog to Digital conversion for MMA7341L
//analogRead returns 0-1023 for 5V input
//for 3.3V input, max value is...
#define ATD3VMAX (3.3 / (5.0 / 1024))
//center value is
#define ATD3VMAXCENTER (ATD3VMAX / 2)
// increment per "g" value
float increment = 0.0f;

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

void setup() 
{
  Serial.begin(9600);
  
  pinMode(pDIG1, OUTPUT);
  pinMode(pDIG2, OUTPUT);
  pinMode(pDIG3, OUTPUT);
  pinMode(pDIG4, OUTPUT);
  
  //set pins to output so you can control the shift register
  pinMode(pSR_STCP, OUTPUT);
  pinMode(pSR_SHCP, OUTPUT);
  pinMode(pSR_DS, OUTPUT);
  
  displayClear();
  
  //MMA7341L
  pinMode(pSleep, OUTPUT);
  pinMode(pSelect, OUTPUT);
  
  //turn accelerometer on
  digitalWrite(pSleep, HIGH);
  //do -3g to +3g
  digitalWrite(pSelect, LOW);
  increment = (float)6 / ATD3VMAX;
  //do -11g to +11g
  //digitalWrite(pSelect, HIGH);
  //increment = (float)22 / ATD3VMAX;
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
  
  /* dont display digit 4
  displayClear();
  
  digitalWrite(pDIG1, LOW);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
    
  digitalWrite(pSR_STCP, LOW);
  shiftOut(pSR_DS, pSR_SHCP, MSBFIRST, displayPinVals[dig4]); 
  digitalWrite(pSR_STCP, HIGH);
  */
}

int n = 0; //number of loops
int d = 0; //number to display

void loop()
{
  if (n%10 == 0)
  {
    //dont read values from the accelerometer faster than can be seen
    int x = analogRead(pX);
    int y = analogRead(pY);
    int z = analogRead(pZ);
    
    //calculate g value
    float gX = (x - ATD3VMAXCENTER) * increment;
    float gY = (y - ATD3VMAXCENTER) * increment;
    float gZ = (z - ATD3VMAXCENTER) * increment;
    
    //pad a 3 digit number for display
    //float to int val
    x=gX;
    y=gY;
    z=gZ;
    
    //no negatives
    if (x < 0)
    {
      x=x* -1;
    }
    if (y < 0)
    {
      y=y* -1;
    }
    if (z < 0)
    {
      z=z* -1;
    }
    
    d=x*100 + y*10 + z;
    
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(" = ");
    Serial.println(d);
  }
  
  displayNum(d, 20);
  n++;
}
