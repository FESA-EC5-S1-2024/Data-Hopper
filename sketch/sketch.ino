// Lib da configuração dos cabos analógicos
#include <Wire.h>

// Arquivos Externos
#include "include/alert.hpp"
#include "include/config.hpp"
#include "include/logo.hpp"
#include "include/medidas.hpp"

// Definição de estado de Botões
struct botoes {
  bool estado_botao1 : 1;
  bool estado_botao2 : 1;
} botoes = {.estado_botao1 = 0, .estado_botao2 = 0};

// Controle de tempo
unsigned long temporizador_reset = 0;
unsigned long marcacao_troca_de_escala = 0;
unsigned long ultima_medicao_media = 0;
unsigned long ultimo_calculo_media = 0;
unsigned long ultima_medicao_visualizacao = 0;
unsigned long tempo_medicao_media = 10000;
unsigned long tempo_calculo_media = 60000;

const unsigned long tempo_reset = 5000;
const unsigned long tempo_troca_medidas = 5000;
const unsigned long intervalo_troca_de_escala = 300;

void resetEEPROM();

void setup() {
  warning(0);

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
  leituraRelogio();

  // Visualizações
  if ((millis() - ultima_medicao_visualizacao) >= tempo_troca_medidas) {
    ultima_medicao_visualizacao = millis();

    if (ultima_medicao_visualizacao % 15000 >= 10000) {
      apresentacaoMedicaoTempUmid();
    } else if (ultima_medicao_visualizacao % 15000 >= 5000) {
      apresentacaoMedicaoLumi();
    } else {
      apresentacaoRelogio();
    }
  }

  // Valores para média
  if ((millis() - ultima_medicao_media) >= tempo_medicao_media) {
    ultima_medicao_media = millis();

    medias.temperatura += medidas.temperatura;
    medias.umidade += medidas.umidade;
    medias.luminosidade += medidas.luminosidade;

  }

  // Calculando Médias
  if ((millis() - ultimo_calculo_media) >= tempo_calculo_media) {
    ultimo_calculo_media = millis();

    medias.temperatura /= 6.0;
    medias.umidade /= 6.0;
    medias.luminosidade /= 6.0;

    if(!(medias.umidade > 30.0 && medias.umidade < 50.0)){
      // Adiciona no contador de problemas na umidade
      warning(1);
    }

    if(!(medias.temperatura > 15.0 && medias.temperatura < 25.0)){
      // Adiciona no contador de problemas na temperatura
      warning(2);
    }

    if(medias.luminosidade > 30.0)){
      // Adiciona no contador de problemas na luminosidade
      warning(3);
    }

    // Reset dos valores de média
    medias.temperatura = 0;
    medias.umidade = 0;
    medias.luminosidade = 0;

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

void leituraHumidade() {

  lcd.setCursor(0, 1);

  lcd.print("Humi.:");
  lcd.print(dht.readHumidity());
  lcd.print(" %");

  medicoes.humidade = dht.readHumidity();

  if (!(medicoes.humidade > 30.0 && medicoes.humidade < 50.0)) {
    tone(HUMI_BUZZER_PIN, 440, 100);
    tone(HUMI_BUZZER_PIN, 440, 100);
  }
}

void leituraTemperatura() {

  lcd.setCursor(0, 0);
  lcd.print("Temp.:");

  medicoes.temperatura = (char)dht.readTemperature();

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

void resetEEPROM() {}
