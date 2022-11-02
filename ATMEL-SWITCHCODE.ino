/* 
ATMEGA 328P -------------
                _____
            01-|°    |-28
BUTTON  (0) 02-|     |-27
RESET   (1) 03-|     |-26
!RESET  (2) 04-|     |-25
LED-R   (3) 05-|     |-24
LED-G   (4) 06-|     |-23
        VCC 07-|     |-22 GND
        GND 08-|     |-21
            09-|     |-20
            10-|     |-19
TOGGLE  (5) 11-|     |-18
!TOGGLE (6) 12-|     |-17
            13-|     |-16
            14-|_____|-15

low:   0xE2
high:  0xDA
ext.:  0x05
unlck: 0x3F
lock:  0x0F

ATtiny84 ----------------
                _____
       VCC  01-|°    |-14 GND
            02-|     |-13 BUTTON  (0)
            03-|     |-12 RESET   (1)
            04-|     |-11 !RESET  (2)
            05-|     |-10 LED-R   (3)
            06-|     |-09 LED-G   (4)
!TOGGLE (6) 07-|_____|-08 TOGGLE  (5)

low:   0xE2
high:  0xD7
ext.:  0xFF
lock:  0xFF

-------------------------

Description:
This mcu code toggles 2 pins high or low upon a button-press.
Feedback is given by 2 LED lines for 2 different colors.
Also a reset signal is sent from separate pins for either active-low or active-high systems.

BUTTON:  Connect a switch to GND. No external pull-up or hardware-debounce needed.
RESET:   Send a reset signal for 150ms to an active-high system.
!RESET:  Send a reset signal for 150ms to an active-low system.
LED-R:   Connect a red LED pin with common-cathode via 220R.
LED-G:   Connect a green LED pin with common-cathode via 220R.
TOGGLE:  Is set either HIGH or LOW depending on which state is active.
!TOGGLE: Is set either LOW or HIGH depending on which state is active.

*/
#include <EEPROM.h>

const int buttonPin = 0;
const int ResetPin = 1;
const int invResetPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int TogglerPin = 5;
const int invTogglerPin = 6;

int GledState;
int RledState;
int resetState = HIGH;
int TogglerState;
int buttonState;
int lastButtonState = HIGH;

int eeprom_test;
int eeprom_value;
int eeprom_location;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int Count = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);  // enable internal pullup

  pinMode(ResetPin, INPUT);
  digitalWrite(ResetPin, LOW);
  pinMode(invResetPin, INPUT);

  pinMode(TogglerPin, OUTPUT);
  pinMode(invTogglerPin, OUTPUT);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);

  eeprom_test = EEPROM.read(0);
  if (eeprom_test < 1) {
    EEPROM.write(0, 1);
    TogglerState = HIGH;
  } else if (eeprom_test == 1) {
    TogglerState = HIGH;
  } else if (eeprom_test == 2) {
    TogglerState = LOW;
  }

  digitalWrite(TogglerPin, TogglerState);
  digitalWrite(invTogglerPin, !TogglerState);

  if (TogglerState == LOW) {
    blinkGreen();
  } else {
    blinkRed();
  }
}

void setStates() {
  digitalWrite(TogglerPin, TogglerState);
  digitalWrite(invTogglerPin, !TogglerState);
  sendReset();
}

void sendReset() {
  // send reset for active-high
  PORTA |= (1 << ResetPin);
  DDRA |= (1 << ResetPin);
  // send reset for active-low
  pinMode(invResetPin, OUTPUT);
  delay(150);
  cancelReset();
}

void cancelReset() {
  // cancel reset for active-high
  DDRA &= ~(1 << ResetPin);
  PORTA &= ~(1 << ResetPin);
  // cancel reset for active-low
  pinMode(invResetPin, INPUT);
}

void toggleNow() {
  TogglerState = !TogglerState;
  setStates();
  digitalWrite(GledPin, LOW);
  digitalWrite(RledPin, LOW);
  if (TogglerState == LOW) {
    EEPROM.write(0, 2);
    blinkGreen();
  } else {
    EEPROM.write(0, 1);
    blinkRed();
  }
}

void blinkRed() {
  int Count = 0;
  while (Count <= 10) {
    delay((50 - ((Count * 10) / 2)) + 10);
    digitalWrite(RledPin, LOW);
    delay((50 - ((Count * 10) / 2)) + 10);
    digitalWrite(RledPin, HIGH);
    Count++;
  }
}

void blinkGreen() {
  int Count = 0;
  while (Count <= 10) {
    delay((50 - ((Count * 10) / 2)) + 10);
    digitalWrite(GledPin, LOW);
    delay((50 - ((Count * 10) / 2)) + 10);
    digitalWrite(GledPin, HIGH);
    Count++;
  }
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        toggleNow();
      }
    }
  }
  lastButtonState = reading;
}