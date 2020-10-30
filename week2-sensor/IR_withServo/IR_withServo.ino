//send the signal and receive it each 2 second
//as long as a signal is received, the led will be on
//if the signal is received, the servo will sweeps.
#include <Servo.h>
#include <IRLibSendBase.h> //the send base
#include <IRLib_P01_NEC.h> //the protocol
#include <IRLibCombo.h>

#include <IRLibRecvPCI.h>

IRrecvPCI myReceiver(2);//pin number for the receiver
IRsend mySender;
bool sending = false;

Servo myservo;
int pos = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  //delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));

  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(9);
}

void loop() {
  unsigned long currentMillis = millis();
  
  //delay(2000);
  if (currentMillis - previousMillis >= interval) {//each 2 seconds send the signal.
     previousMillis = currentMillis;   
     mySender.send(NEC, 0x61a0f00f, 0); 
     Serial.println(F("Sent signal."));
    if (myReceiver.getResults()) {
      //printResults();
      Serial.println("received!");
      sending = true;
      myReceiver.enableIRIn();      //Restart receiver
    } else {
      Serial.println("something blocked!");
      sending = false;
      myReceiver.enableIRIn(); //do i need it here?
    }
  }


  if (sending) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void printResults() {
  Serial.println(F("Do a cut-and-paste of the following lines into the "));
  Serial.println(F("designated location in rawSend.ino"));
  Serial.print(F("\n#define RAW_DATA_LEN "));
  Serial.println(recvGlobal.recvLength, DEC);
  Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));
  for (bufIndex_t i = 1; i < recvGlobal.recvLength; i++) {
    Serial.print(recvGlobal.recvBuffer[i], DEC);
    Serial.print(F(", "));
    if ( (i % 8) == 0) Serial.print(F("\n\t"));
  }
  Serial.println(F("1000};"));//Add arbitrary trailing space
}
