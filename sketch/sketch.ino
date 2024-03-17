// Lib da configuração dos cabos analógicos
#include <Wire.h>

// Arquivos Externos
#include "include/config.hpp"
#include "include/logo.hpp"

// Seletor de escala de temperatura
struct EscalaTemperatura {
  unsigned char seletor : 2;
} escala = {.seletor = 0};

// Definição de estado de Botões
struct botoes {
  bool estado_botao1 : 1;
  bool estado_botao2 : 1;
} botoes = {.estado_botao1 = 0, .estado_botao2 = 0};

// Variaveis físicas a serem mostradas
struct Medidas {
  unsigned int temperatura: 7;
  unsigned int humidade : 7;
  unsigned int luminosidade : 7;
} medicoes = {.temperatura = 0, .humidade = 0, .luminosidade = 0};

unsigned long marcacao = 0;
const unsigned long intervalo = 300;

void setup() {

  // Configurando Input de Botão
  pinMode(BUTTON0_INPUT_PIN, INPUT);
  pinMode(BUTTON1_INPUT_PIN, INPUT);
  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(HUMI_BUZZER_PIN, OUTPUT);

  // Iniciando Sensor de temperatura
  dht.begin();

  // Iniciando lib de configuração de cabos
  Wire.begin();

  // Iniciando LCD
  lcd.init();
  lcd.clear();

  // Apresentação da empresa
  entradaEmpresa();
}

void loop() {

  // Leituras físicas
  leituraTemperatura();
  leituraHumidade();
  leituraLuminosidade();

  // Leitura do primeiro botão - troca de escala de temperatura
  botoes.estado_botao1 = digitalRead(BUTTON1_INPUT_PIN);
  if (botoes.estado_botao1 == HIGH && ((millis() - marcacao) >= intervalo)) {
    marcacao = millis();
    mudaEscala();
  }

  // Leitura do segundo botão - reset dos processos
  botoes.estado_botao2 = digitalRead(BUTTON0_INPUT_PIN);
  if (botoes.estado_botao2 == HIGH) {
    resetFunc();
  }
}

void leituraHumidade() {

  lcd.setCursor(0, 1);

  lcd.print("Humi.:");
  lcd.print(dht.readHumidity());
  lcd.print(" %");

  medicoes.umidade = dht.readHumidity();

  if(!(medicoes.umidade > 30.0 && medicoes.umidade < 50.0)){
        tone(HUMI_BUZZER_PIN, 440, 100);
        tone(HUMI_BUZZER_PIN, 440, 100);
  }

}

void leituraTemperatura() {

  lcd.setCursor(0, 0);
  lcd.print("Temp.:");

  medicoes.temperatura = (char) dht.readTemperature();

  if (!(medicoes.temperatura > 15.0 && medicoes.temperatura < 25.0)) {
    digitalWrite(TEMP_LED_PIN, HIGH);
  } else {
    digitalWrite(TEMP_LED_PIN, LOW);
  }

  switch (escala.seletor) {
  case 0:
    lcd.print(medicoes.temperatura);
    lcd.print((char)223);
    lcd.print(" C");
    break;

  case 1:
    lcd.print(dht.readTemperature(true));
    lcd.print((char)223);
    lcd.print(" F");
    break;

  case 2:
    lcd.print(dht.readTemperature() + 273.15);
    lcd.print(" K");
    break;
  }
}

void leituraLuminosidade() {

  medicoes.luminosidade = map(analogRead(LDR_PIN), 0, 1023, 100, 0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(medicoes.luminosidade);

  delay(5000);
}

void mudaEscala() {

  lcd.clear();

  switch (escala.seletor) {

  case 0:
    escala.seletor = 1;
    break;

  case 1:
    escala.seletor = 2;
    break;

  case 2:
    escala.seletor = 0;
    break;
  }
}

// Função de Reset
void(* resetFunc) (void) = 0;
