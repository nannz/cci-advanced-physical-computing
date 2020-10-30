//send the signal and receive it each 2 second
//as long as a signal is received, the led will be on

#include <IRLibSendBase.h> //the send base
#include <IRLib_P01_NEC.h> //the protocol
#include <IRLibCombo.h>

#include <IRLibRecvPCI.h>

IRrecvPCI myReceiver(2);//pin number for the receiver
IRsend mySender;
bool sending = true;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  mySender.send(NEC, 0x61a0f00f, 0);
  //Serial.println(F("Sent signal."));
  delay(2000);

  //Continue looping until you get a complete signal received
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

  if (sending) {
    digitalWrite(LED_BUILTIN, HIGH);
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
