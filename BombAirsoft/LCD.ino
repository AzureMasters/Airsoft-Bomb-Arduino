void DisplayTimeOnLCD(){
    lcd.setCursor(0, 0);
    lcd.print("Tempo restante: ");
    lcd.setCursor(PadLeftValue(hoursRemaining, 0), 1);
    lcd.print(hoursRemaining);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3 + PadLeftValue(minutesRemaining, 3), 1);
    lcd.print(minutesRemaining);
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(6 + PadLeftValue(secondsRemaining, 6), 1);
    lcd.print(secondsRemaining);
}

void DisplayCodeOnLCD(){
    for (int count = 0; count < 4; count++){
      lcd.setCursor(12 + count, 1);
      if (passwordCount > count || bombState == 3)        
        lcd.print(bombPassword[count]);
      else
        lcd.print('*');
    }
}

bool PadLeftValue(unsigned long timeValue, int cursorPoint){
    if (timeValue < 10){
      lcd.setCursor(cursorPoint, 1);
      lcd.print("0");
      return 1;
    }
    else
      return 0;
}

void DisplayMainMenu(int menuState){
  lcd.setCursor(0, 0);
  switch (menuState){
    case 0:
      lcd.print("Iniciar Contagem           ");
      break;
    case 1:
      lcd.print("Alterar Tempo              ");
      break;
    case 2:
      lcd.print("Tipo de Senha        ");
      break;
    case 3:
      lcd.print("Chances de Erro            ");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("                                ");
}

void PasswordMenu(){
  lcd.setCursor(0, 0);
  lcd.print("A - Manual               ");
  lcd.setCursor(0, 1);
  lcd.print("B - Aleatoria            ");
  SetPasswordType();
}

void DisplayPassword(int index){    
  lcd.setCursor(index, 1);
  lcd.print(bombPassword[index]);
}

void SetTimeMenu(){  
  lcd.setCursor(0, 0);
  lcd.print("Escolha o tempo:    ");
  lcd.setCursor(0, 1);
  
  DefineTime();
}

void SetErrorChancesMenu(){
  lcd.setCursor(0, 0);
  lcd.print("Numero de chances:    ");
  lcd.setCursor(0, 1);
  DefineErrorChances();
}

void DisplayTimeMenu(char value){
  lcd.print(value);
}
