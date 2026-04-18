void Menu(){
  if (!subMenuOption)
    MenuSelection();
  
  switch(menuState)
  {
    case 0: //Começar
      StopAllOutputs(); 
      DisplayMainMenu(menuState);
      if (!digitalRead(pinConfirmBtn)){
        lcd.clear();
        Initialize();
        menuState = 4;
      }
    break;
    
    case 1:  //Alterar tempo
      StopAllOutputs(); 
      if (subMenuOption)
        SetTimeMenu();
      else
        DisplayMainMenu(menuState);

      if (!digitalRead(pinConfirmBtn)){
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("HH:MM:SS");
        setTimeCount = 0;
        totalTime = 0;
        subMenuOption = true;
      } 
    break;

    case 2: //Tipo de Senha
      StopAllOutputs(); 
      if (subMenuOption)
        PasswordMenu();
      else
        DisplayMainMenu(menuState);
      
      if (!digitalRead(pinConfirmBtn)){
        lcd.clear();
        subMenuOption = true;
      }        
    break;

    case 3: //Definir chances de erro
      StopAllOutputs(); 
      if (subMenuOption)
        SetErrorChancesMenu();
      else
        DisplayMainMenu(menuState);

      if (!digitalRead(pinConfirmBtn)){
        lcd.clear();
        subMenuOption = true;
      } 
    break;  
    
    case 4:
      Bomb();
    break;
  }
}

void Bomb(){
  switch (bombState){
    case 0:
      DefinePassword();

      if (!randomPassword && passwordDefined && !digitalRead(pinConfirmBtn)){
        startingTime = millis();
        passwordCount = 0;
        btnDelay = millis();
        hasPressed = false;
        bombState = 1;
      }
    break;
    
    case 1:
      TimerCountdown();
      DefuseCode();
      Blink(500UL);
      DisplayCodeOnLCD();
    break;
    
    case 2:
      FinishedCountdown();

      if (!digitalRead(pinConfirmBtn)){
        StopAllOutputs();
        menuState = 0;
        subMenuOption = false;
        delay(250);
      }
    break;
    
    case 3:
      Defused();
      
      if (!digitalRead(pinConfirmBtn)){
        StopAllOutputs();
        menuState = 0;
        subMenuOption = false;
        delay(250);
      }
    break;
  }
}
