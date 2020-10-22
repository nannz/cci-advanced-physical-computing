const int buttonPin = 2;
const int ledPin = 13;

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

const int bulletLimit = 10;
  
void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  
  if(buttonState != lastButtonState){
    if (buttonState == HIGH){
      buttonPushCounter ++;
        Serial.println("ON");
        Serial.print("number of button pushes: ");//push the button to attack
        Serial.println(buttonPushCounter);
    }else{
      Serial.println("OFF");//release the hand/finger
    }
    delay(50);//to avoid bouncing
  }
  lastButtonState = buttonState;
  
  //if running out the bullets, turn on the LED.
  if (buttonPushCounter >= bulletLimit){
    digitalWrite(ledPin, HIGH);
    //buttonPushCounter = 0;
  }else{
    digitalWrite(ledPin, LOW);
  }
}
