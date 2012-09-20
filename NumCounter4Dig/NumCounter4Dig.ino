
//NumCounter4Dig
//Use a 4 digit 7 segment display to count a series of numbers
//Because its a common cathode display, HIGH = ON and LOW = OFF.
//Digit pins must be multiplexed!
//dspinoz@spinoz.com.au

//PINS for the 7-segments
#define pA 2
#define pB 1
#define pC 10
#define pD 11
#define pE 7
#define pF 4
#define pG 5
#define pDP 3

//PINS for the digits
#define pDIG1 6
#define pDIG2 8
#define pDIG3 9
#define pDIG4 12

void setup() { 
  
  pinMode(pDIG1, OUTPUT);
  pinMode(pDIG2, OUTPUT);
  pinMode(pDIG3, OUTPUT);
  pinMode(pDIG4, OUTPUT);
  
  pinMode(pA, OUTPUT);
  
  //default - nothing on display
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
  digitalWrite(pA, LOW);
  
}

int showDigit = 0;

void loop() 
{
  if (showDigit >= 4)
  {
    showDigit=0; 
  }
  
  switch (showDigit)
  {
    case 0:
      digitalWrite(pDIG1, LOW); 
      digitalWrite(pDIG2, HIGH); 
      digitalWrite(pDIG3, HIGH);
      digitalWrite(pDIG4, HIGH); 
      break;
    case 1:
      digitalWrite(pDIG1, HIGH); 
      digitalWrite(pDIG2, LOW); 
      digitalWrite(pDIG3, HIGH);
      digitalWrite(pDIG4, HIGH); 
      break;
    case 2:
      digitalWrite(pDIG1, HIGH); 
      digitalWrite(pDIG2, HIGH); 
      digitalWrite(pDIG3, LOW);
      digitalWrite(pDIG4, HIGH); 
      break;
    case 3:
      digitalWrite(pDIG1, HIGH); 
      digitalWrite(pDIG2, HIGH); 
      digitalWrite(pDIG3, HIGH);
      digitalWrite(pDIG4, LOW); 
      break;
    default:
      digitalWrite(pDIG1, HIGH); 
      digitalWrite(pDIG2, HIGH); 
      digitalWrite(pDIG3, HIGH);
      digitalWrite(pDIG4, HIGH); 
  }
  
  showDigit++;
  
  digitalWrite(pA, HIGH);    
  delay(40);  
  
}
