//BUTTON for .GIF CAM

#include <Keyboard.h>

int btnPin = 7;
int ledPin = 11;

unsigned long currentTime = 0;

//which state? pulsing calm or blinking rapidly?
bool activeState = false;
int stateReturnInterval = 5000;
unsigned long activationTime = 0;

//values for pulsing
int ledStrength = 0;
bool ledShift = true;
int pulseUpdateStep = 1;
int pulseUpdateInterval = 4;
unsigned long pulseLastUpdate = 0;

//values for blinking
bool ledState = false;
int blinkUpdateInterval = 400;
unsigned long blinkLastUpdate = 0;


void setup() {
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  //Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  //Serial.println(digitalRead(btnPin));
  if(!activeState){
    if(digitalRead(btnPin)){
      //Serial.println("Setting active state");
      setActiveState();
      Keyboard.write(32);
    }
  }
  if(activeState){
    stateTimer();
    blinkLed();
  } else {
    pulseLed();
  }
}

void setActiveState(){
  resetValues();
  activationTime = millis();
  activeState = true;
}

void stateTimer(){
  if(millis() - activationTime > stateReturnInterval){
    activeState = false;
  }
}

void pulseLed(){
  if(millis() - pulseLastUpdate > pulseUpdateInterval){
    //Serial.println("Pulsing");
    if(ledShift == true){
      ledStrength += pulseUpdateStep;
      if(ledStrength >= 245){
        ledShift = !ledShift;
      }
    } else {
      ledStrength -= pulseUpdateStep;
      
      if(ledStrength <= 0){
        ledShift = !ledShift;
      }
    }
    analogWrite(ledPin, ledStrength);
    pulseLastUpdate = millis();
  }
}

void blinkLed(){
  if(millis() - blinkLastUpdate > blinkUpdateInterval){
    
    if(ledState){
      digitalWrite(ledPin, LOW);
      ledState = !ledState;
    } else {
      digitalWrite(ledPin, 250);
      ledState = !ledState;
    }
    blinkLastUpdate = millis();
  }
}

void resetValues(){
  ledStrength = 0;
  ledShift = true;
  ledState = false;
}

