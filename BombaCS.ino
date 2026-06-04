#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

byte pinosLinhas[]  = {8,2,3,5}; // pinos para linhas do teclado
byte pinosColunas[] = {7,9,4};    // pinos para colunas do teclado
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
int segundosrestantes;
int key=-1;
int buzzer = 6;
char var;
int chances = 0;  
             
                     
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
  lcd.print("Rangers Airsoft");
  //lcd.setCursor(0, 1);
  //lcd.print("");
  delay(3000);
  keypad.setHoldTime(50);
  keypad.setDebounceTime(50);
  //keypad.addEventListener(keypadEvent);
  lcd.clear();
  pinMode(buzzer, OUTPUT);   
  
}

void loop() {
   menu();
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

void iniciar(){
  while(1){
    if(chances !=0){
    cronTempo(segundos);
    compSenha();
    }
    else{
    cronTempo(segundosrestantes);
    compSenha();
    }
   }
  }

void compSenha(){
  int i,j;
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("DESARMAR");
  delay(1000);
  lcd.clear();
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
    delay(2000);
    lcd.clear();
    bombadesarmada(chances,segundos);
  }
  else{
    lcd.setCursor(0, 0);  
    lcd.print("Senha incorreta!");
    chances++;
    delay(2000);
    bombaexplodiu(chances, segundos);
    }
}

void bombaexplodiu(int chances, int segundos){
      if(chances == 3 || segundos == 0){
        while(1){
          lcd.setCursor(0, 0);
          lcd.print("Bomba explodida");
          digitalWrite(buzzer, HIGH);  
          delay(5000);
          lcd.clear();
      }
    }
  }

void bombadesarmada(int chances, int segundos){
    while(1){
      lcd.setCursor(0, 0);
      lcd.print("Bomba desarmada");
      delay(5000);
      lcd.clear();
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
    segundosrestantes = segundos;
    delay(500);
    digitalWrite(buzzer, HIGH);
    if(chances == 1){
      lcd.setCursor(0, 1);  
      lcd.print("#");
      }
    if(chances == 2){
      lcd.setCursor(0, 1);  
      lcd.print("##");}
      
    if(chances == 3){
      lcd.setCursor(0, 1);  
      lcd.print("###");}
    
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
      
    delay(150);
    digitalWrite(buzzer, LOW);
    delay(350);
  }
  segundos = 2;
}

int menu(){
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Menu");
  lcd.setCursor(0, 1);  
  lcd.print("Aperte o botao");
  lcd.clear();
  delay(1000);
  lcd.setCursor(0, 0);  
  lcd.print("1-Configurar");
  lcd.setCursor(0, 1);  
  lcd.print("2-Iniciar");
  var = keypad.waitForKey();
  lcd.clear();
  if (var == '1'){// 
      setSenha();
      lcd.clear();
      setTempo();
      segundos = calcTempo();
      lcd.clear();
  }
  else if (var == '2'){
    iniciar();
    lcd.clear();
  }
  else{
    menu();
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
        return 0;
        break;
      }

    }
    return 11;
  }
}
