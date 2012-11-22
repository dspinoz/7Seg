//Counter

#include <TinyGPS.h>

TinyGPS gps;

//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
//Pin connected to DS of 74HC595
int dataPin = 6;
//Pin connected to LED
int led = 13;


//PINS for MMA7341L
#define pSleep 3
#define pSelect 4
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

void setup() 
{
  Serial.begin(57600);
  
  pinMode(led, OUTPUT);
  
  digitalWrite(led, LOW);
  
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  //reset display
  digitalWrite(latchPin, LOW); //set to enable setting pins
  for (int j =0; j < 16; j++)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, HIGH); //sets a single pin on the shift register
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH); //flush the register
  
  displayNum(0);
  
  Serial.println("speed and G");
  
  
  
  
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

//display a number on the two digits
//suports 0-99
void displayNum(int i)
{
  //Serial.println(i);
  int dig1 = i % 10;
  int dig2 = (i / 10) % 10; 
  int dig3 = (i / 100) % 10; 
    
  digitalWrite(latchPin, LOW);
  
  int num = ~displayPinVals[dig1];
  for (int j =0; j < 8; j++)
  {
      int val = ~num >> j;
      
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, (val & 0x1));
      digitalWrite(clockPin, HIGH);
  }
  
  num = ~displayPinVals[dig2];
  for (int j =0; j < 8; j++)
  {
      int val = num >> j;
      
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, (val & 0x1));
      digitalWrite(clockPin, HIGH);
  }
  
  num = ~displayPinVals[dig3];
  for (int j =0; j < 8; j++)
  {
      int val = num >> j;
      
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, (val & 0x1));
      digitalWrite(clockPin, HIGH);
  }
  
  digitalWrite(latchPin, HIGH);
}

int readGs()
{
  
  
    int x = analogRead(pX);
    int y = analogRead(pY);
    int z = analogRead(pZ);
    
    //calculate g value
    float gX = (x - ATD3VMAXCENTER) * increment;
    float gY = (y - ATD3VMAXCENTER) * increment;
    float gZ = (z - ATD3VMAXCENTER) * increment;
    
    //pad a 3 digit number for display
    //float to int val
    x=gX*10;
    y=gY*10;
    z=gZ*10;
    
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
      
      int gval = x + y;
      
      if (gval > 9)
      {
        gval=0; 
      }
      
      Serial.print("x = ");
      Serial.print(gX);
      Serial.print(" y = ");
      Serial.print(gY);
      Serial.print(" z = ");
      Serial.print(gZ);
      Serial.print(" : ");
      Serial.println(gval);
      
      return gval;
}


int n=0;

//output some gps information in csv format
void loop() 
{
      digitalWrite(led, LOW);
/*  displayNum(n);
  n++;
  delay(200);
  
  if (n>10)
  {
    //n=0; 
  }
  */
  n++;
  
  //    int gval = readGs();
  //    displayNum(gval);
      
//      Serial.println("before");
  
  
  //while (!Serial.available())
  //{
  //  displayNum(n%10);
  //  delay(1000);
  //  n++;
  //}
  
  
  
  while (Serial.available())
  {
      digitalWrite(led, LOW);
      digitalWrite(clockPin, HIGH);
    if (gps.encode(Serial.read()))
    {
      digitalWrite(led, HIGH);
      
      int gval = readGs();
      
      
      
      
      long flat, flon = 0;
      unsigned long age, date, time = 0;
  
      gps.get_datetime(&date, &time, &age);
  
      Serial.print(date);
      Serial.print(",");
      Serial.print(time);
      Serial.print(",");
      Serial.print(age);
      Serial.print(",");
      
      gps.get_position(&flat, &flon, &age);
      
      Serial.print(flat);
      Serial.print(",");
      Serial.print(flon);
      Serial.print(",");
      Serial.print(age);
      Serial.print(",");
      
      Serial.print(gps.f_speed_kmph());
      Serial.print(",");
      Serial.print(gps.altitude());
      Serial.print(",");
      Serial.print(gps.satellites());
      Serial.print(",");
      Serial.print(gps.hdop());
      Serial.println("");
      
      
      
      Serial.print(" ; ");
      Serial.println(((int)gps.f_speed_kmph() * 10) + gval);
      
      
      
      
      if (gval > 10)
      {
        gval = 9; 
      }
      //displayNum(gval);
      
      
      
      displayNum(((int)gps.f_speed_kmph() * 10) + gval);
    }
  }
  
  //delay(500);
  //    Serial.println("done");
  
  
}
