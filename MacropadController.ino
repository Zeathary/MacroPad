#include <Keypad.h>
#include <Encoder.h>
#include <Bounce2.h>
#include "HID-Project.h"
//Keypad buttons
int R1 = 18;
int R2 = 20;
int R3 = 5;
int R4 = 6;
int C1 = 9;
int C2 = 8;
int C3 = 7;
const byte ROWS = 4;
const byte COLS = 3;
char keys[COLS][ROWS] = {
  {'X','7','4','1'},
  {'*','8','5','2'},
  {'-','9','6','3'}
};
byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS);

//State LED pins
int S1 = 10;
int S2 = 16;
int S3 = 14;
int S4 = 15;
const int numStates = 4;
const int States[numStates] = {S1, S2, S3, S4};
int currentState = 0;

int lastDebounceTime = 0;
const int debounceTime = 250;

//Encoder
int SW = 19;
int DT = 2;
int CLK = 3;
Encoder volumeKnob(DT,CLK);
Bounce encoderButton = Bounce(SW,10);
int timeLimit = 500;
long oldPosition = -999;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < numStates; i++){
    pinMode(States[i], OUTPUT);
    digitalWrite(States[i], LOW);
  }

  pinMode(CLK, INPUT_PULLUP);
  
  Keyboard.begin();
  //Consumer.begin();
  
  Serial.print("Ready");
  
  StartAnimation();
  digitalWrite(States[currentState], HIGH);
}

void StartAnimation(){
  int waitTime = 250;
  digitalWrite(S1, HIGH);
  delay(waitTime);
  digitalWrite(S2, HIGH);
  delay(waitTime);
  digitalWrite(S3, HIGH);
  delay(waitTime);
  digitalWrite(S4, HIGH);
  delay(waitTime);
  digitalWrite(S1, LOW);
  delay(waitTime);
  digitalWrite(S2, LOW);
  delay(waitTime);
  digitalWrite(S3, LOW);
  delay(waitTime);
  digitalWrite(S4, LOW);
  delay(waitTime);
  return;
}

void ChangeState(){
  digitalWrite(States[currentState], LOW);
  currentState++;
  if (currentState == numStates){
    currentState = 0;
  }
  digitalWrite(States[currentState], HIGH);
  //Serial.print("State Changed. Current State: "); Serial.println(currentState);
  delay(100);
  return;
}

// Number Pad Layout (1-9 as labeled)
void Layout1(char button){
  switch(button){
    case '1':
      Keyboard.print('1');
      break;
    case '2':
      Keyboard.print('2');
      break;
    case '3':
      Keyboard.print('3');
      break;
    case '4':
      Keyboard.print('4');
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':
      Keyboard.print('7');
      break;
    case '8':
      Keyboard.print('8');
      break;
    case '9':
      Keyboard.print('9');
      break;
  };
}
// F1-F9
void Layout2(char button){
  switch(button){
    case '1': // F1
      Keyboard.press(KEY_F1); 
      Keyboard.releaseAll();
      break;
    case '2':// F2
      Keyboard.press(KEY_F2); 
      Keyboard.releaseAll();
      break;
    case '3':// F3
      Keyboard.press(KEY_F3); 
      Keyboard.releaseAll();
      break;
    case '4':// F4
      Keyboard.press(KEY_F4); 
      Keyboard.releaseAll();
      break;
    case '5':// F5
      Keyboard.press(KEY_F5); 
      Keyboard.releaseAll();
      break;
    case '6':// F6
      Keyboard.press(KEY_F6); 
      Keyboard.releaseAll();
      break;
    case '7':// F7
      Keyboard.press(KEY_F7); 
      Keyboard.releaseAll();
      break;
    case '8':// F8
      Keyboard.press(KEY_F8); 
      Keyboard.releaseAll();
      break;
    case '9':// F9
      Keyboard.press(KEY_F9); 
      Keyboard.releaseAll();
      break;
  };
}
// WoW Macros 
void Layout3(char button){
  switch(button){
    case '1': // Combustion Sequence
      Keyboard.press(KEY_F5);  // Fireball
      Keyboard.release(KEY_F5);
      
      Keyboard.press(KEY_RIGHT_SHIFT); // Combust
      Keyboard.press(KEY_F2); 
      Keyboard.releaseAll();
      
      Keyboard.press(KEY_F2); // Fireblast
      Keyboard.releaseAll(); 

      delay(2100); // Wait for Cast to finish
      Keyboard.press(KEY_F1); // Pyroblast
      Keyboard.releaseAll(); 
      Keyboard.press(KEY_F2); // Fireblast
      Keyboard.releaseAll(); 

      delay(1400); // Wait for Global (1.26s)
      Keyboard.press(KEY_F1); // Pyroblast
      Keyboard.releaseAll(); 
      Keyboard.press(KEY_F2); // Fireblast
      Keyboard.releaseAll(); 

      delay(1400); // Wait for Global
      Keyboard.press(KEY_F1); // Pyroblast
      Keyboard.releaseAll(); 

      delay(1400); // Wait for Global
      Keyboard.press(KEY_F3); // Phoenix Flames
      Keyboard.releaseAll();

      delay(1400); // Wait for Global
      Keyboard.press(KEY_F1); // Pyro
      Keyboard.releaseAll();

      delay(1400); // Wait for Global (1.26s)
      Keyboard.press(KEY_F2); // Fireblast
      Keyboard.releaseAll(); 
      delay(200);
      Keyboard.press(KEY_F1); // Pyroblast
      Keyboard.releaseAll(); 

      delay(1400); // Wait for Global
      Keyboard.press(KEY_F3); // Phoenix Flames
      Keyboard.releaseAll();

      delay(1400); // Wait for Global
      Keyboard.press(KEY_F1); // Pyro
      Keyboard.releaseAll();
       
      break;
    case '2':
      Keyboard.print('8');
      break;
    case '3':
      Keyboard.print('9');
      break;
    case '4':
      Keyboard.print('4');
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':
      Keyboard.print('1');
      break;
    case '8':
      Keyboard.print('2');
      break;
    case '9':
      Keyboard.print('3');
      break;
  };
}

// Spotify Hot Keys
// Must be used in conjunction with the spotifiycontroller.ahk auto hot key script
void Layout4(char button){
  switch(button){
    case '1': // Play/Pause
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press('p'); 
      Keyboard.releaseAll();
      break;
    case '2': // Seek Backwards
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_LEFT_ARROW); 
      Keyboard.releaseAll();
      break;
    case '3': // Seek Forwards
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_RIGHT_ARROW); 
      Keyboard.releaseAll();
      break;
    case '4': // Like Current Song
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press('l'); 
      Keyboard.releaseAll();
      break;
    case '5': // Previous Song
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_DOWN_ARROW); 
      Keyboard.releaseAll();
      break;
    case '6': // Next Song
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_UP_ARROW); 
      Keyboard.releaseAll();
      break;
    case '7':
      Keyboard.print('7');
      break;
    case '8':
      Keyboard.print('8');
      break;
    case '9': // Toggle Spotify
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press('o'); 
      Keyboard.releaseAll();
      break;
  };
}

void loop() {
  //check the key matrix first
  char key = kpd.getKey();
  if(key) {
    switch(key){
      case '*':
        ChangeState();
        break;
      case '-':
        Keyboard.press(KEY_RIGHT_CTRL);
        Keyboard.press('s');
        delay(10);
        Keyboard.releaseAll();
        break;
      default:
        switch(currentState){
          case 0:
            Layout1(key);
            break;
          case 1:
            Layout2(key);
            break;
          case 2:
            Layout3(key);
            break;
          case 3: 
            Layout4(key);
            break;
        }
    }
  }

  //check the encoder button
  if(encoderButton.update()) {
    if(encoderButton.fallingEdge()) {
      int fall = millis();
      while(!encoderButton.update()){}
      if(encoderButton.risingEdge()){
        int rise = millis();
        //Serial.println(rise - fall);
        if(rise - fall > timeLimit){
          Consumer.write(MEDIA_NEXT);
          Serial.print("Next");
        } else {
          Consumer.write(MEDIA_PLAY_PAUSE);
          Serial.print("Play/Pause");
        }
      }
      Keyboard.releaseAll();
    }
  }

  //check encoder rotation
  long newPosition = volumeKnob.read();
  if(newPosition != oldPosition){
    Serial.print(newPosition);

    if((newPosition - oldPosition) > 0) {
      //volumeup
      Serial.println("volume up");
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      //volumedown
      Serial.println("volume down");
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    oldPosition = newPosition;
    Keyboard.releaseAll();
    delay(200); //a delay of 200 seems to be the sweet spot for this encoder.
  }  
}
