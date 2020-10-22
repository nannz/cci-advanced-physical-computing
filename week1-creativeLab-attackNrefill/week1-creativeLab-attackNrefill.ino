//For UAL CCI Physical Computing
//Week 1 assignment Creative Project
//Imagine in an interstellar ship, you need to click a "button" to attack aliens
//And whenever you are run out of bullets, you need to refill it. 

//thus the following features:
//1.the green led on when an attack is excuted (showing the machine has detected the attack order
//2.1 the red led on when there is no bullet
//2.2 the green led cannot be turned on when no bullet
//3.the yellow led fading in and out to indicate "refilling" state
//4.once finish refilling, the green led blinks
//5.then you can click to attack again.

//circuit can be access here: https://www.tinkercad.com/things/7MFEH8y0ytD
//Nan 20201022

const int btnAttack = 2;
const int btnRefill = 3;
const int ledPinR = 13;
const int ledPinG = 12;
const int ledPinRefill = 11;
  
int buttonPushCounter = 0;
int btnStateAttack = 0;
int btnStateRefill = 0;
int lastBtnStateAttack = 0;
int lastBtnStateRefill = 0;

const int bulletLimit = 10;
bool bulletIsRunOut = false;
bool isRefilling = false;

//to count the refilling time
unsigned long previousMillis = 0;
const long refillInterval = 5000;// interval at which to refill (milliseconds)


void setup()
{
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinRefill,OUTPUT);
  pinMode(btnAttack, INPUT);
  Serial.begin(9600);
}

void loop()
{
  btnStateAttack = digitalRead(btnAttack);
  btnStateRefill = digitalRead(btnRefill);
  
  //attack
  if(btnStateAttack != lastBtnStateAttack){
    if (btnStateAttack == HIGH){
      buttonPushCounter ++;//add the counter
        Serial.println("ON");
        Serial.print("number of button pushes: ");//push the button to attack
        Serial.println(buttonPushCounter);
        
    }else{
      Serial.println("OFF");//release the hand/finger
    }
    delay(50);//to avoid bouncing
  }
  lastBtnStateAttack = btnStateAttack;
  
  //if the btn is pushed and there are still bullets, 
  //turn on the GREEN LED
  if(btnStateAttack == HIGH && !bulletIsRunOut){
    digitalWrite(ledPinG, HIGH);
  }else{
    digitalWrite(ledPinG, LOW);
  }
  
  //if running out the bullets, turn on the RED LED.
  //set the bulletIsRunOut to true;
  if (buttonPushCounter >= bulletLimit){
    digitalWrite(ledPinR, HIGH);
    bulletIsRunOut = true;
  }else{
    digitalWrite(ledPinR, LOW);
  }
  
  //click the refill btn
  if(btnStateRefill != lastBtnStateRefill){
    if(btnStateRefill == HIGH){
      Serial.println("refill!");
        isRefilling = true;
        bulletIsRunOut = false;
        buttonPushCounter = 0;
    }
    delay(50);//to avoid bouncing
  }
  lastBtnStateRefill = btnStateRefill;
  
  if(isRefilling){
    unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= refillInterval) {//refill for 5 secs
       previousMillis = currentMillis;
       isRefilling = false;
       Serial.println("refill finish!");
       digitalWrite(ledPinG, HIGH);
       delay(500);
       digitalWrite(ledPinG, LOW);
     }else{
      //doing the fade effect
       //fade in
      for(int fadeValue = 0; fadeValue<=255; fadeValue+=5){
          analogWrite(ledPinRefill,fadeValue);
          delay(30);
      }
      //fade out
      for(int fadeValue = 255; fadeValue>=0; fadeValue -=5){
          analogWrite(ledPinRefill,fadeValue);
          delay(30);
      }
     }   
  }
  
}
