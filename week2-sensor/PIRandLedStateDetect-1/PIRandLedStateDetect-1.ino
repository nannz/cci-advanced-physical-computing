/*
 * PIR sensor tester
 * 2-test analog in from the PIR sensor
 * 3-add led states 
 */
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;//A0;                // choose the input pin (for PIR sensor)
int lastPirState = 0; //LOW;             // we start, assuming no motion detected
int pirState = 0;                    // variable for reading the pin status
int counter = 0;

bool hasSlept = false;
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  pirState = digitalRead(inputPin); // read input value

  if (pirState == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (lastPirState == LOW) {
      // we have just turned on
      counter +=1; 
      Serial.print("Motion detected!");
      Serial.println(counter);
      // We only want to print on the output change, not state
      lastPirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (lastPirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      lastPirState = LOW;
    }
  }
}
