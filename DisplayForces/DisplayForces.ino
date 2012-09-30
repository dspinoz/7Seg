//DisplayForces
//Use a 7 segment display to show the forces from an accelerometer MMA7341L
//dspinoz@spinoz.com.au

//PINS for MMA7341L
#define pSleep 2
#define pSelect 3
#define pX 1 //analog
#define pY 2 //analog
#define pZ 3 //analog

float increment = 0.0f;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(pSleep, OUTPUT);
  pinMode(pSelect, OUTPUT);
  
  //turn accelerometer on
  digitalWrite(pSleep, HIGH);
  //do -3g to +3g
  digitalWrite(pSelect, LOW);
  increment = (float)6 / 1024;
  //do -11g to +11g
  //digitalWrite(pSelect, HIGH);
  //increment = (float)22 / 1024;
  
}

void loop() 
{
  int x = analogRead(pX);
  int y = analogRead(pY);
  int z = analogRead(pZ);
  
  //calculate g value
  float gX = (x - 512) * increment;
  float gY = (y - 512) * increment;
  float gZ = (z - 512) * increment;
  
  Serial.print("  x=");
  Serial.print(x);
  Serial.print(",");
  Serial.print(gX, 5);
  Serial.print("  y=");
  Serial.print(y);
  Serial.print(",");
  Serial.print(gY, 5);
  Serial.print("  z=");
  Serial.print(z);
  Serial.print(",");
  Serial.println(gZ, 5); 
}
