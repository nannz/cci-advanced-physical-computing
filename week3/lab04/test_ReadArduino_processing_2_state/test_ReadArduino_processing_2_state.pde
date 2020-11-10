/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;
import processing.sound.*;
SoundFile sound1;
SoundFile sound2;
SoundFile sound3;
SoundFile sound4;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
int lastVal;

int soundNow = 0;
void setup() 
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[3];
  println( portName);
  myPort = new Serial(this, portName, 9600);
  
  sound1 = new SoundFile(this, "sounds/01-ahh.mp3");
  sound2 = new SoundFile(this, "sounds/02-sneezing.wav");
  sound3 = new SoundFile(this, "sounds/03-giggle.mp3");
  sound4 = new SoundFile(this, "sounds/04-gibberish.wav");
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
  }
  background(255); // Set background to white
  if (val == 0 || val == 4 || val == 7 || val == 10){
    //println(val);
  }
  
  if(val != lastVal){
    if (val == 10){
      soundNow = 1;
      println("sound 1!");
    }else if (val == 7){
      soundNow = 2;
      println("sound 2!");
    }else if (val == 4){
      soundNow = 3;
      println("sound 3!");
    }else if (val == 0){
      soundNow = 4;
      println("sound 4!");
    }else{
      soundNow = 0;
    }
  }
  
  switch(soundNow) {
    case 1:
      sound1.play();
      break;
    case 2:
      sound2.play();
      break;
    case 3:
      sound3.play();
      break;
    case 4:
      sound4.play();
      break;   
  }
  lastVal = val;
  //rect(50, 50, 100, 100);
  delay(100);
}



/*

// Wiring / Arduino Code
// Code for sensing a switch status and writing the value to the serial port.

int switchPin = 4;                       // Switch connected to pin 4

void setup() {
  pinMode(switchPin, INPUT);             // Set pin 0 as an input
  Serial.begin(9600);                    // Start serial communication at 9600 bps
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.write(1);               // send 1 to Processing
  } else {                               // If the switch is not ON,
    Serial.write(0);               // send 0 to Processing
  }
  delay(100);                            // Wait 100 milliseconds
}

*/
