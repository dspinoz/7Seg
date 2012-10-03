//DisplayForces
//Use a 7 segment display to show the forces from an accelerometer MMA7341L
//dspinoz@spinoz.com.au

//PINS for MMA7341L
#define pSleep 2
#define pSelect 3
#define pX A1 //analog
#define pY A2 //analog
#define pZ A3 //analog

//Analog to Digital conversion
//analogRead returns 0-1023 for 5V input
//for 3.3V input, max value is...
#define ATD3VMAX (3.3 / (5.0 / 1024))
//center value is
#define ATD3VMAXCENTER (ATD3VMAX / 2)

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
  increment = (float)6 / ATD3VMAX;
  //do -11g to +11g
  //digitalWrite(pSelect, HIGH);
  //increment = (float)22 / ATD3VMAX;
  
}

void loop() 
{
  int x = analogRead(pX);
  int y = analogRead(pY);
  int z = analogRead(pZ);
  
  //calculate g value
  float gX = (x - ATD3VMAXCENTER) * increment;
  float gY = (y - ATD3VMAXCENTER) * increment;
  float gZ = (z - ATD3VMAXCENTER) * increment;
  
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
  
  //delay(200);
}
