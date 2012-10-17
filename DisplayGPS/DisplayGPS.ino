//DisplayGPS
//Use two 7 segment displays to show values from a GPS
//Reduce the number of pins from the arduino to the display
//  by using two 8 bit shift register - 74HC595.
//also writes CSV-formatted GPS information to Serial port.
//NOTE: Makes use of TinyGPS, http://arduiniana.org/libraries/tinygps/
//dspinoz@spinoz.com.au

#include <TinyGPS.h>

TinyGPS gps;

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;
//Pin connected to LED
int led = 13;

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
  
  Serial.println("date,time,timeage,lat,lon,posage,speed,altitude,satellites,hdop");
}

//display a number on the two digits
//suports 0-99
void displayNum(int i)
{
  int dig1 = i % 10;
  int dig2 = (i / 10) % 10; 
    
  digitalWrite(latchPin, LOW);
  
  int num = ~displayPinVals[dig2];
  for (int j =0; j < 8; j++)
  {
      int val = num >> j;
      
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, (val & 0x1));
      digitalWrite(clockPin, HIGH);
  }
  
  num = ~displayPinVals[dig1];
  for (int j =0; j < 8; j++)
  {
      int val = num >> j;
      
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, (val & 0x1));
      digitalWrite(clockPin, HIGH);
  }
  
  digitalWrite(latchPin, HIGH);
}

//output some gps information in csv format
void loop() 
{
  digitalWrite(led, LOW);
  while (Serial.available())
  {
    if (gps.encode(Serial.read()))
    {
      digitalWrite(led, HIGH);
      displayNum(gps.f_speed_kmph());
      
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
    }
  }
}
