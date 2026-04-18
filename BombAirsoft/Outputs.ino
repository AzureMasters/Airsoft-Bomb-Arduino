bool redLedState = LOW;
unsigned long previousBlink = 0;

void Blink(unsigned long interval){  
  if (millis() - previousBlink > interval){
    previousBlink = millis();
    
    if (redLedState == LOW){
      redLedState = HIGH;
      tone(pinBuzzer, 250);
    }
    else{
      redLedState = LOW;
      noTone(pinBuzzer);
    }

    digitalWrite(pinRedLED, redLedState);
  } 
}

void FinishedCountdownLED(){
  digitalWrite(pinRedLED, HIGH);
  digitalWrite(pinGreenLED, LOW);
  tone(pinBuzzer, 200);
}

void DefusedLED(){
  digitalWrite(pinRedLED, LOW);
  digitalWrite(pinGreenLED, HIGH);
  tone(pinBuzzer, 20000);
}

void StopAllOutputs(){
  noTone(pinBuzzer);
  digitalWrite(pinRedLED, LOW);
  digitalWrite(pinGreenLED, LOW);
}
