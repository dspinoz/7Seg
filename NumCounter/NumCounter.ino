//NumCounter
//Use the 7 segment display to count a series of numbers
//dspinoz@spinoz.com.au
 
int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for (int i = 0; i< 8; i++)
  {
    pinMode(pins[i], OUTPUT);
  }  
}

void loop() {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(pins[i], LOW);   // set the LED on
    delay(1000);              // wait for a second
    digitalWrite(pins[i], HIGH);    // set the LED off
    delay(1000);              // wait for a second
  }
}
