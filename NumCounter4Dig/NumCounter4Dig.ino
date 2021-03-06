
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

int p7SegDisplayNum = 8;
int p7SegDisplay[] = {pA, pB, pC, pD, pE, pF, pG, pDP};

// Pin values for the 7 segment display
char displayPinVals[][8] = {
  //A B C D E F G DP
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW , LOW }, //0
  {LOW , HIGH, HIGH, LOW , LOW , LOW , LOW , LOW }, //1
  {HIGH, HIGH, LOW , HIGH, HIGH, LOW , HIGH, LOW }, //2
  {HIGH, HIGH, HIGH, HIGH, LOW , LOW , HIGH, LOW }, //3
  {LOW , HIGH, HIGH, LOW , LOW , HIGH, HIGH, LOW }, //4
  {HIGH, LOW , HIGH, HIGH, LOW , HIGH, HIGH, LOW }, //5
  {HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, //6
  {HIGH, HIGH, HIGH, LOW , LOW , LOW , LOW , LOW }, //7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, //8
  {HIGH, HIGH, HIGH, LOW , LOW , HIGH, HIGH, LOW } //9
};

void displayClear()
{
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
  digitalWrite(pA, LOW);
  digitalWrite(pB, LOW);
  digitalWrite(pC, LOW);
  digitalWrite(pD, LOW);
  digitalWrite(pE, LOW);
  digitalWrite(pF, LOW);
  digitalWrite(pG, LOW);
  digitalWrite(pDP, LOW); 
}

void setup() {
  
  pinMode(pDIG1, OUTPUT);
  pinMode(pDIG2, OUTPUT);
  pinMode(pDIG3, OUTPUT);
  pinMode(pDIG4, OUTPUT);
  
  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
  pinMode(pC, OUTPUT);
  pinMode(pD, OUTPUT);
  pinMode(pE, OUTPUT);
  pinMode(pF, OUTPUT);
  pinMode(pG, OUTPUT);
  pinMode(pDP, OUTPUT);
  
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
    
  //Set values for pins
  for (int pin = 0; pin < p7SegDisplayNum; pin++)
  {
    digitalWrite(p7SegDisplay[pin], displayPinVals[dig1][pin]);
  }
    
  delay(sleepInc);
  displayClear();

  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, LOW);
  digitalWrite(pDIG4, HIGH);
    
  //Set values for pins
  for (int pin = 0; pin < p7SegDisplayNum; pin++)
  {
    digitalWrite(p7SegDisplay[pin], displayPinVals[dig2][pin]);
  }
    
  delay(sleepInc);
  displayClear();
    
    
  digitalWrite(pDIG1, HIGH);
  digitalWrite(pDIG2, LOW);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
    
  //Set values for pins
  for (int pin = 0; pin < p7SegDisplayNum; pin++)
  {
    digitalWrite(p7SegDisplay[pin], displayPinVals[dig3][pin]);
  }
    
  delay(sleepInc);
  displayClear();
  
  digitalWrite(pDIG1, LOW);
  digitalWrite(pDIG2, HIGH);
  digitalWrite(pDIG3, HIGH);
  digitalWrite(pDIG4, HIGH);
    
  //Set values for pins
  for (int pin = 0; pin < p7SegDisplayNum; pin++)
  {
    digitalWrite(p7SegDisplay[pin], displayPinVals[dig4][pin]);
  }
}

int n=0;
void loop()
{
  displayNum(n, 1000);
  n++;
  
  if (n > 10000)
  {
    n=0; 
  }
}
