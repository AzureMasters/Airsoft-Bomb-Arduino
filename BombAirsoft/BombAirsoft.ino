#include <LiquidCrystal.h>
#include <Keypad.h>

#define pinGreenLED 3
#define pinRedLED 4
#define pinBuzzer 5
#define pinConfirmBtn 2

unsigned long startingTime = millis();
unsigned long totalTime = 5400000UL;
unsigned long totalTimeRemaining, secondsRemaining, minutesRemaining, hoursRemaining, totalTimeDecreased;
unsigned long btnDelay, resetBtnHoldingTime;
unsigned long decreaseValue = 600000UL;
unsigned long errorChances;

byte menuState, bombState;
byte passwordCount, setTimeCount;
bool randomPassword, subMenuOption, passwordDefined;
bool hasPressed, canDecreaseTime = false;

char bombPassword[4];

LiquidCrystal lcd(7, 6, 8, 10, 11, 12);

void setup() {
  lcd.begin(16,2);
  //Serial.begin(9600); 
  pinMode(pinGreenLED, OUTPUT);
  pinMode(pinRedLED, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinConfirmBtn, INPUT_PULLUP);

  randomPassword = false;
  
  StopAllOutputs();
  menuState = 0;
  errorChances = 2UL;
  subMenuOption = false;

  Event();
}

void loop() {
  Menu();
}

void Initialize(){
  passwordCount = 0;
  setTimeCount = 0;
  passwordDefined = false;
  bombState = 0;
  totalTimeRemaining = totalTime;
  totalTimeDecreased = 0UL;
  lcd.clear();
  digitalWrite(pinRedLED, LOW);
  digitalWrite(pinGreenLED, LOW);
  noTone(pinBuzzer);
  delay(250);
}
