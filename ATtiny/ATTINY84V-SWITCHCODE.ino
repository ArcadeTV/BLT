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
