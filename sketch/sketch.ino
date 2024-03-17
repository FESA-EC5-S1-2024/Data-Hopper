// Lib da configuração dos cabos analógicos
#include <Wire.h>

// Arquivos Externos
#include "include/config.hpp"
#include "include/logo.hpp"
#include "include/medidas.hpp"

// Definição de estado de Botões
struct botoes {
  bool estado_botao1 : 1;
  bool estado_botao2 : 1;
} botoes = {.estado_botao1 = 0, .estado_botao2 = 0};

// Controle de tempo
unsigned long marcacao_troca_de_escala = 0;
unsigned long temporizador_reset = 0;
unsigned long ultima_medicao_media = 0;
unsigned long ultima_medicao_visualizacao = 0;
unsigned long tempo_medicao_media = 10000;

const unsigned long tempo_reset = 5000;
const unsigned long tempo_troca_medidas = 5000;
const unsigned long intervalo_troca_de_escala = 300;

void resetEEPROM();

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
  leituraUmidade();
  leituraLuminosidade();

  // Visualizações
  if ((millis() - ultima_medicao_visualizacao) >= tempo_troca_medidas) {

    ultima_medicao_visualizacao = millis();
    apresentacaoMedicaoTempUmid();

  } else {

    apresentacaoMedicaoLumi();
  }

  // Valores para média
  if ((millis() - ultima_medicao_media) >= tempo_medicao_media) {
    ultima_medicao_media = millis();

    // Chamada da função para a passagem dos valores para a realização da média
  }

  // Leitura do primeiro botão - troca de escala de temperatura
  botoes.estado_botao1 = digitalRead(BUTTON1_INPUT_PIN);
  if (botoes.estado_botao1 == HIGH &&
      ((millis() - marcacao_troca_de_escala) >= intervalo_troca_de_escala)) {
    marcacao_troca_de_escala = millis();
    mudaEscala();
  }

  // Leitura do segundo botão - reset da EEPROM
  temporizador_reset = millis();
  while (digitalRead(BUTTON0_INPUT_PIN) == HIGH &&
         digitalRead(BUTTON1_INPUT_PIN) == HIGH) {

    if ((millis() - temporizador_reset) >= tempo_reset) {
      resetEEPROM();
      apresentacaoReset();
    }
  }
}

void resetEEPROM() {}
