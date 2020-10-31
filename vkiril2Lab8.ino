// Viktor Kirillov - 677621632
// Lab 8 - Interrupts
// Description - Pressing a button would cause an interrupt, display would be in waiting state
        // pressing a second button would revert display to previous state to display time after last interrupt button press
// Assumptions: interurpt pin - 2, 2nd btn pin = 8, lcd is conencted to pins 12,11,5,7,3,4
// References: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
//             https://www.arduino.cc/reference/en/language/functions/time/millis/
//             https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
//             https://www.arduino.cc/en/tutorial/button

const byte ledPin = 13;
const byte interruptPin = 2;
const byte btn2Pin = 8;
volatile byte state = LOW;

unsigned long time;
unsigned long lastPressTime;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 7, d6 = 3, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(btn2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), showInterruptReceived, RISING);

  lcd.begin(16, 2);
  time = millis();
  lastPressTime = time;
}

void loop() {
  if (state == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting");
    lcd.setCursor(0, 1);
    lcd.print("For ");
    time = millis();
    lcd.print((time - lastPressTime)/1000);
    lcd.print(" seconds");
    delay(1000);
  }
  else {
    int val = digitalRead(btn2Pin);
    if (val == HIGH) {
      state = LOW;
      lastPressTime = millis();
    }
  }
}

void showInterruptReceived() {
  if (state == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Interrupt received!");
    lcd.setCursor(0, 1);
    lcd.print("Press button 2 to continue");
    state = HIGH;
  }
}
