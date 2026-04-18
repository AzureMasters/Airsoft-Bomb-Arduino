const byte ROWS = 4; 
const byte COLS = 4; 
bool filter = false;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[COLS] = {25, 24, 23, 22}; 
byte rowPins[ROWS] = {29, 28, 27, 26}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void MenuSelection(){
    char key = customKeypad.getKey();

    if (key != NO_KEY){
      switch (key)
      {
        case 'A':
          menuState = 0;
          break;
        case 'B':
          menuState = 1;
          break;
        case 'C':
          menuState = 2;
          break;
        case 'D':
          menuState = 3;
          break;
      }
    }
}

void SetPasswordType(){
    char key = customKeypad.getKey();

    if (key != NO_KEY){
      switch (key)
      {
        case 'A':
          randomPassword = false;
          subMenuOption = false;
          lcd.clear();
          delay(1000);
          break;
        case 'B':
          randomPassword = true;
          subMenuOption = false;
          lcd.clear();
          delay(1000);
          break;
      }
    }
}

void DefinePassword(){
  lcd.setCursor(0, 0);
      
  if (randomPassword){
    lcd.print("Senha gerada:           ");
    for(int count = 0; count<4; count++){
      bombPassword[count]= 0x30 | (micros() / 10U) % 10U;
      delay(15);
      DisplayPassword(count);
    }

    delay(3000);
    startingTime = millis();
    bombState = 1;
  }
  
  else{  
    lcd.print("Digite a senha:           ");
    char key = customKeypad.getKey();
  
    if (key != NO_KEY){
      switch (passwordCount){
        case 0:
          if (KeyFilter(key, false)){
            bombPassword[passwordCount] = key;
            DisplayPassword(0);
            passwordCount = 1;
          }
        break;
        case 1:
          if (KeyFilter(key, false)){
            bombPassword[passwordCount] = key;
            DisplayPassword(1);
            passwordCount = 2;
          }
        break;
        case 2:
          if (KeyFilter(key, false)){
            bombPassword[passwordCount] = key;
            DisplayPassword(2);
            passwordCount = 3;
          }
        break;
        case 3:
          if (KeyFilter(key, false)){
            bombPassword[passwordCount] = key;
            DisplayPassword(3);
            passwordDefined = true;
          }
        break;
      }
    }
  }
}

void DefineTime(){
  char key = customKeypad.getKey();

  if (filter){
    if (setTimeCount == 1){
      lcd.setCursor(1, 1);
      lcd.print("0:00:00");
      delay(1000);
      lcd.clear();
      subMenuOption = false;  
      filter = false;
    }
    else if (setTimeCount == 3){
      lcd.setCursor(4, 1);
      DisplayTimeMenu('0');
      setTimeCount = 4;  
      delay(100);
      filter = false;
    }
    else if (setTimeCount == 5){
      lcd.setCursor(7, 1);
      DisplayTimeMenu('0');
      delay(1000);
      lcd.clear();
      subMenuOption = false;  
      filter = false;
    }
  }
  
  if (key != NO_KEY){  
    unsigned long keyValue = key - '0';
      
    switch (setTimeCount){   
      case 0: //HOUR IN DECIMAL
        if (key != '0')
          filter = true;
        if (KeyFilter(key, false)){   
          lcd.setCursor(0, 1);
          if (keyValue != 0UL){
            totalTime += 36000000UL;
            DisplayTimeMenu('1');
          }
          else
            DisplayTimeMenu('0');
          setTimeCount = 1;
          delay(100);
        }
      break;
      case 1: //HOUR UNIT
        if (KeyFilter(key, false)){
          lcd.setCursor(1, 1);
          if (keyValue != 0UL)
            totalTime += keyValue * 3600000UL;
          DisplayTimeMenu(key);
          setTimeCount = 2;
          delay(100);
        }
      break;
      case 2: //MINUTE DECIMAL
        if (key == '6')
          filter = true;
        if (KeyFilter(key, true)){
          lcd.setCursor(3, 1);
          if (key != '0')
            totalTime += keyValue * 600000UL;
          DisplayTimeMenu(key);
          setTimeCount = 3;
          delay(100);
        }
      break;
      case 3: //MINUTE UNIT   
        if (KeyFilter(key, false)){
          lcd.setCursor(4, 1);
          if (key != '0')
            totalTime += keyValue * 60000UL;
          DisplayTimeMenu(key);
          setTimeCount = 4;
          delay(100);
        }
      break;
      case 4: //SECONDS DECIMAL
        if (key == '6')
          filter = true;
        if (KeyFilter(key, true)){
          lcd.setCursor(6, 1);
          if (keyValue != 0UL)
            totalTime += keyValue * 10000UL;
          DisplayTimeMenu(key);
          setTimeCount = 5;
          delay(100);
        }
      break;
      case 5: //SECONDS UNIT
        if (KeyFilter(key, false)){
          lcd.setCursor(7, 1);
          if (key != '0')
            totalTime += keyValue * 1000UL;
          DisplayTimeMenu(key);
          delay(1000);
          lcd.clear();
          subMenuOption = false;          
        }
      break;
    }
  }
}

void DefineErrorChances(){
  char key = customKeypad.getKey();

  if (key != NO_KEY){  
    unsigned long keyValue = key - '0';

    if (key != '0' && KeyFilter(key, false)){
      errorChances = keyValue;
      lcd.print(key);
      delay(1000);
      lcd.clear();
      subMenuOption = false;
    }
  }
}

bool KeyFilter(char key, bool isFiltering){
  if (isFiltering){
    if (key == '#' || key == '*' || key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '7' || key == '8' || key == '9')
      return false;
    else
      return true;
  }
  else{
    if (key == '#' || key == '*' || key == 'A' || key == 'B' || key == 'C' || key == 'D')
      return false;
    else
      return true;
  }
}

void DefuseCode(){
  char key = customKeypad.getKey();

  if (millis() - btnDelay > 250)
    hasPressed = false;
  
  if (key != NO_KEY && !hasPressed && KeyFilter(key, false)){  
    hasPressed = true;         
    btnDelay = millis();
    
    switch (passwordCount){ 
      case 0:
        if (!strcmp(key, bombPassword[passwordCount]))
          passwordCount = 1;         
        else
          canDecreaseTime = true;
      break;
  
      case 1:
        if (!strcmp(key, bombPassword[passwordCount]))
          passwordCount = 2; 
        else
          canDecreaseTime = true;
      break;
  
      case 2:
        if (!strcmp(key, bombPassword[passwordCount]))
          passwordCount = 3; 
        else
          canDecreaseTime = true;
      break;
  
      case 3:
        if (!strcmp(key, bombPassword[passwordCount]))
          bombState = 3;
        else
          canDecreaseTime = true;
      break;
    }
  }
}

void Event(){
  customKeypad.setHoldTime(3000);
  customKeypad.addEventListener(Reset);
}

void Reset(KeypadEvent key){
  switch(customKeypad.getState()){
    case HOLD:
      if (key == '#'){
        menuState = 0;
        errorChances = 2UL;
        totalTime = 5400000UL;
        subMenuOption = false;
        randomPassword = false;
        StopAllOutputs();        
        Initialize();
        delay(2000);
      }
    break;
  }
}
