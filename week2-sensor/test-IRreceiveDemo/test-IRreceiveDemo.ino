/*
   IRremote: IRreceiveDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Initially coded 2009 Ken Shirriff http://www.righto.com/
*/

#include <IRremote.h>

#if defined(ESP32)
int IR_RECEIVE_PIN = 15;
#elif defined(ARDUINO_AVR_PROMICRO)
int IR_RECEIVE_PIN = 10;
#else
int IR_RECEIVE_PIN = 11;
#endif
IRrecv IrReceiver(IR_RECEIVE_PIN);

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  //Serial.begin(115200);
  Serial.begin(9600);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
  delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__));

  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  IrReceiver.enableIRIn();  // Start the receiver
  IrReceiver.blink13(true); // Enable feedback LED

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop() {
  //  if (IrReceiver.decode()) {
  //    Serial.println(IrReceiver.decode());
  //    IrReceiver.printResultShort(&Serial);
  //    Serial.println();
  //    IrReceiver.resume(); // Receive the next value
  //  }

  if (IrReceiver.decode()) //this checks to see if a code has been received
  {
    //Serial.println(IrReceiver.results.value);
    if (IrReceiver.results.value == 0xFD30CF) //if the button press equals "0" on my remote
    {
      //do something useful here
      Serial.println("you pressed something!");
    } else {
      IrReceiver.printResultShort(&Serial);
      Serial.println();
    }
    IrReceiver.resume(); //receive the next value
  }


  delay(100);
}
