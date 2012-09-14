//NumCounter
//Use the 7 segment display to count a series of numbers
//dspinoz@spinoz.com.au
 
int pin = 2;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(pin, OUTPUT);     
}

void loop() {
  digitalWrite(pin, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(pin, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
