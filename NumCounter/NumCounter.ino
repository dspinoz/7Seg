//NumCounter
//Use the 7 segment display to count a series of numbers
//Because its a common anode display, HIGH = OFF and LOW = ON.
//dspinoz@spinoz.com.au

//PINS for the 7-segment display
#define pA 2
#define pB 3
#define pC 4
#define pD 5
#define pE 6
#define pF 7
#define pG 8
#define pDP 9

int p7SegDisplayNum = 8;
int p7SegDisplay[] = {pA, pB, pC, pD, pE, pF, pG, pDP};

// Pin values for the 7 segment display
char displayPinVals[][8] = { 
  //A     B     C     D     E     F     G     DP
  {LOW , LOW , LOW , LOW , LOW , LOW , HIGH, HIGH}, //0
  {HIGH, LOW , LOW , HIGH, HIGH, HIGH, HIGH, HIGH}, //1
  {LOW , LOW , HIGH, LOW , LOW , HIGH, LOW , HIGH}, //2
  {LOW , LOW , LOW , LOW , HIGH, HIGH, LOW , HIGH}, //3
  {HIGH, LOW , LOW , HIGH, HIGH, LOW , LOW , HIGH}, //4
  {LOW , HIGH, LOW , LOW , HIGH, LOW , LOW , HIGH}, //5
  {LOW , HIGH, LOW , LOW , LOW , LOW , LOW , HIGH}, //6
  {LOW , LOW , LOW , HIGH, HIGH, HIGH, HIGH, HIGH}, //7
  {LOW , LOW , LOW , LOW , LOW , LOW , LOW , HIGH}, //8
  {LOW , LOW , LOW , HIGH, HIGH, LOW , LOW , HIGH}  //9
};

void setup() {
  
  Serial.begin(9600);
  
  // 7-segment display initialisation
  for (int i = 0; i < p7SegDisplayNum; i++)
  {
    pinMode(p7SegDisplay[i], OUTPUT);
    digitalWrite(p7SegDisplay[i], HIGH);
  }
}

void loop() {
  
  //Vals from 0 - 9
  for (int num = 0; num < 10; num++)
  {
    //Set values for pins
    for (int pin = 0; pin < p7SegDisplayNum; pin++)
    {
      digitalWrite(p7SegDisplay[pin], displayPinVals[num][pin]);
    }
      
    delay(500);
  }
}

