/*
 * PIR sensor tester
 * 2-test analog in from the PIR sensor
 */
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;//A0;                // choose the input pin (for PIR sensor)
int pirState = 0; //LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int counter = 0;
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);//analogRead(inputPin);  // read input value
  
//  if (val != 0){
//    Serial.print("val= ");
//    Serial.println(val);
//   }
// 
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      counter +=1; 
      Serial.print("Motion detected!");
      Serial.println(counter);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
