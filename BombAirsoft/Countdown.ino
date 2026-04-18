void TimerCountdown(){
  if (totalTimeRemaining < 0UL)
    totalTimeRemaining = 0UL;
  else if (totalTimeRemaining > 0UL){    
    totalTimeRemaining = ((totalTime - (millis() - startingTime)) - totalTimeDecreased) / 1000UL;

    if (canDecreaseTime){
      canDecreaseTime = false;
      if ((totalTimeRemaining * 1000UL) <= decreaseValue || totalTimeDecreased >= (decreaseValue * errorChances))
        totalTimeRemaining = 0UL;
      else
        totalTimeDecreased += decreaseValue;
    }

    hoursRemaining = totalTimeRemaining / 3600UL;
    minutesRemaining = (totalTimeRemaining - (hoursRemaining * 3600UL)) / 60UL;
    secondsRemaining = totalTimeRemaining - ((minutesRemaining * 60UL) + (hoursRemaining * 3600UL));  
  } 
  else
    bombState = 2;
    
  DisplayTimeOnLCD(); 
}

void FinishedCountdown(){
  lcd.setCursor(0, 0);
  lcd.print("EXPLODIU!!                    ");
  FinishedCountdownLED();
}

void Defused(){
  lcd.setCursor(0, 0);
  lcd.print("BOMBA DESARMADA  ");
  DefusedLED();
}
