#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h> 

byte pinosLinhas[]  = {10,9,8,7}; // pinos para linhas do teclado
byte pinosColunas[] = {4,2,3};    // pinos para colunas do teclado
char teclas[4][3] = {
                     {'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'},
                     {'*','0','#'}
                    };
int senha[4];
int tentativa[4];
int tempo[4];
int segundos;
int key=-1;
char var;                  
                     
//função biblioteca para teclado
Keypad keypad = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);  

// cria uma instância do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  //inicializa serial
  Serial.begin(9600);
  // iniciailiza o LCD com as dimensões corretas
  lcd.init();
  // aciona a luz de fundo (backlight)
  lcd.backlight();
  //introdução
  lcd.setCursor(0, 0);  
  lcd.print("UTOPIA");
  lcd.setCursor(0, 1);
  lcd.print("Productions");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Rangers");
  lcd.setCursor(0, 1);
  lcd.print("Airsoft");
  delay(3000);
  keypad.setHoldTime(50);
  keypad.setDebounceTime(50);
  lcd.clear();
  setSenha();
  lcd.clear();
  displaySenha();
  lcd.clear();
  compSenha();
  lcd.clear();
  setTempo();
  lcd.clear();
  segundos = calcTempo();
  cronTempo(segundos);
}

void loop() {
  
  }

void setSenha(){
  int i,j;
  lcd.setCursor(0, 0);  
  lcd.print("Defina a Senha");
  for(i=0;i<4;i++){
    senha[i] = 0;
  }  
  for(i=0;i<4;i++){
    senha[i] = tradutorkeypad();
    lcd.setCursor(i, 1);  
    lcd.print(senha[i]);
  }
  delay(1000);
}

void displaySenha(){
  int i,j;
  lcd.setCursor(0, 0);  
  lcd.print("Resposta");
  for(i=0;i<4;i++){
    lcd.setCursor(i, 1);  
    lcd.print(senha[i]);
  }
  delay(1000);
}

void compSenha(){
  int i,j;
  lcd.setCursor(0, 0);  
  lcd.print("Qual a senha?");
  for(i=0;i<4;i++){
    tentativa[i] = 0;
  }  
  for(i=0;i<4;i++){
    tentativa[i] = tradutorkeypad();
    lcd.setCursor(i, 1);  
    lcd.print(tentativa[i]);
  }
  if(senha[0] == tentativa[0] && senha[1] == tentativa[1] && senha[2] == tentativa[2] && senha[3] == tentativa[3]){
  lcd.setCursor(0, 0);  
  lcd.print("Senha correta!");
  lcd.setCursor(0, 1);
  lcd.print("Bomba desarmada");
  delay(5000); 
  }
  else{
  lcd.setCursor(0, 0);  
  lcd.print("Senha incorreta!");
  lcd.setCursor(0, 1);
  lcd.print("Bomba explodida"); 
  delay(5000);
    }
}

void setTempo(){
  int i,j;
  lcd.setCursor(0, 0);  
  lcd.print("Quanto tempo de");
  lcd.setCursor(0, 1);  
  lcd.print("partida?");
  for(i=0;i<4;i++){
    tempo[i] = 0;
  } 
    lcd.setCursor(13, 1);  
    lcd.print(":"); 
  for(i=0;i<2;i++){
    tempo[i] = tradutorkeypad();
    lcd.setCursor(i+11, 1);  
    lcd.print(tempo[i]);
  }
  for(i=2;i<4;i++){
    tempo[i] = tradutorkeypad();
    lcd.setCursor(i+12, 1);  
    lcd.print(tempo[i]);
  }
  delay(1000);
}

int calcTempo(){
  return(10*tempo[0]*60+tempo[1]*60+10*tempo[2]+tempo[3]);
}

int cronTempo(int segundos){
  lcd.setCursor(0, 0);  
  lcd.print("Tempo restante:");
  while(segundos !=0){
    segundos--; 
    delay(1000);
    if(segundos>=1000){
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("Tempo restante:");
      lcd.setCursor(12, 1);  
      lcd.print(segundos);
      }
    if(segundos<1000){
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("Tempo restante:");
      lcd.setCursor(13, 1);  
      lcd.print(segundos);
      }
      
    if(segundos<100){
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("Tempo restante:");
      lcd.setCursor(14, 1);  
      lcd.print(segundos);
      }
      
    if(segundos<10){
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("Tempo restante:");
      lcd.setCursor(15, 1);  
      lcd.print(segundos);
      }
  }
}

int menu(){
  while(1){
    var = keypad.waitForKey();
    if (var){//
      switch (var) {
      case '1': 

        break;
      case '2': 
        
        break;
      case '3': 

        break;
      case '4': 

        break;
      case '5': 

        break;
      case '6': 

      case '7': 

        break;
      case '8': 

        break;
      case '9': 

        break;
      case '0': 

        break;
      case '*': 

        break;
      case '#': 

        break;

      }

    }
  }
}

int tradutorkeypad(){
  while(1){
    var = keypad.waitForKey();
    if (var){//
      switch (var) {
      case '1': 
        return 1;
        break;
      case '2': 
        return 2;
        break;
      case '3': 
        return 3;
        break;
      case '4': 
        return 4;
        break;
      case '5': 
        return 5;
        break;
      case '6': 
        return 6;
      case '7': 
        return 7;
        break;
      case '8': 
        return 8;
        break;
      case '9': 
        return 9;
        break;
      case '0': 
        return 0;
        break;
      default:
        return 11;
        break;
      }

    }
    return 11;
  }
}
