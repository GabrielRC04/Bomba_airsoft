#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h> 

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

// Definição do Buzzer no pino 6
const int pinoBuzzer = 6;

// Variáveis para controle não-bloqueante
unsigned long tempoAnterior = 0;
int indiceTentativa = 0;
bool bombaAtiva = false;
bool jogoFinalizado = false;

// função biblioteca para teclado
Keypad keypad = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);  

// cria uma instância do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Configura o pino do buzzer como saída
  pinMode(pinoBuzzer, OUTPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  // Introdução
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
  
  // Fase de Configuração
  lcd.clear();
  setSenha();
  
  lcd.clear();
  setTempo();
  
  segundos = calcTempo();
  
  // Prepara a tela para o jogo começar
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Tempo:");
  atualizarDisplayTempo();
  lcd.setCursor(0, 1);
  lcd.print("Senha: ");
  
  // Inicia o jogo
  bombaAtiva = true;
  tempoAnterior = millis();
}

void loop() {
  if (bombaAtiva && !jogoFinalizado) {
    unsigned long tempoAtual = millis();

    // 1. LÓGICA DO CRONÔMETRO (Não-bloqueante)
    if (tempoAtual - tempoAnterior >= 1000) {
      tempoAnterior = tempoAtual; 
      segundos--;
      atualizarDisplayTempo();

      // Apita a cada segundo que passa (frequência de 1000Hz por 100ms)
      tone(pinoBuzzer, 1000, 100);

      // Checa se o tempo acabou
      if (segundos <= 0) {
        bombaAtiva = false;
        jogoFinalizado = true;
        lcd.clear();
        lcd.setCursor(0, 0);  
        lcd.print("TERRORISTS WIN!");
        lcd.setCursor(0, 1);
        lcd.print("Bomba explodida"); 
        
        // --- ROTINA DE EXPLOSÃO ---
        // Apita a cada 50ms por 2 minutos (120.000 ms)
        // 50ms ligado + 50ms desligado = 100ms por ciclo
        // 1200 ciclos * 100ms = 120.000ms = 2 minutos
        for(int i = 0; i < 1200; i++) {
          tone(pinoBuzzer, 1500); // Liga o buzzer
          delay(50);
          noTone(pinoBuzzer);     // Desliga o buzzer
          delay(50);
        }
      }
    }

    // 2. LÓGICA DE DESARMAR A BOMBA (Não-bloqueante)
    char tecla = keypad.getKey(); 
    
    if (tecla && tecla != '*' && tecla != '#') { 
      tentativa[indiceTentativa] = tecla - '0';  
      
      lcd.setCursor(7 + indiceTentativa, 1); 
      lcd.print(tentativa[indiceTentativa]);
      
      indiceTentativa++;

      // Verifica a senha
      if (indiceTentativa == 4) {
        if (verificarSenha()) {
          // Senha correta
          bombaAtiva = false;
          jogoFinalizado = true;
          lcd.clear();
          lcd.setCursor(0, 0);  
          lcd.print("CT WIN!");
          lcd.setCursor(0, 1);
          lcd.print("Bomba desarmada");
        } else {
          // Senha incorreta: limpa a tela para tentar de novo
          lcd.setCursor(7, 1);
          lcd.print("    "); 
          indiceTentativa = 0;
        }
      }
    }
  }
}

// ================= FUNÇÕES AUXILIARES =================

bool verificarSenha() {
  if(senha[0] == tentativa[0] && senha[1] == tentativa[1] && 
     senha[2] == tentativa[2] && senha[3] == tentativa[3]) {
    return true;
  }
  return false;
}

void atualizarDisplayTempo() {
  lcd.setCursor(7, 0);
  lcd.print("         "); 
  lcd.setCursor(7, 0);
  lcd.print(segundos);
  lcd.print("s");
}

void setSenha(){
  int i;
  lcd.setCursor(0, 0);  
  lcd.print("Defina a Senha");
  for(i=0;i<4;i++){
    senha[i] = tradutorkeypad();
    lcd.setCursor(i, 1);  
    lcd.print(senha[i]);
  }
  delay(1000);
}

void setTempo(){
  int i;
  lcd.setCursor(0, 0);  
  lcd.print("Tempo (MM:SS)");
  for(i=0;i<4;i++){
    tempo[i] = 0;
  } 
  lcd.setCursor(2, 1);  
  lcd.print(":"); 
  
  for(i=0;i<2;i++){ // Minutos
    tempo[i] = tradutorkeypad();
    lcd.setCursor(i, 1);  
    lcd.print(tempo[i]);
  }
  for(i=2;i<4;i++){ // Segundos
    tempo[i] = tradutorkeypad();
    lcd.setCursor(i+1, 1);  
    lcd.print(tempo[i]);
  }
  delay(1000);
}

int calcTempo(){
  int minutos = (tempo[0] * 10) + tempo[1];
  int segs = (tempo[2] * 10) + tempo[3];
  return (minutos * 60) + segs;
}

int tradutorkeypad(){
  char var;
  while(1){
    var = keypad.waitForKey();
    if (var >= '0' && var <= '9') {
      return var - '0'; 
    }
  }
}
