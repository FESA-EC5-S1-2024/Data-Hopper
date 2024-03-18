// Biblioteca de configuração de cabos analógicos
#include <Wire.h>

// Arquivos externos
#include "include/alert.hpp"
#include "include/config.hpp"
#include "include/logo.hpp"
#include "include/measurements.hpp"

// Definição do estado dos botões
struct buttons {
  bool button0_state : 1;
  bool button1_state : 1;
} buttons = {.button0_state = 0, .button1_state = 0};

// Controle de tempo
unsigned long startMillis = 0;
unsigned long currentTime = 0;
unsigned long eeprom_reset_timer = 0;
unsigned long scale_change_marker = 0;
unsigned long last_average_measurement = 0;
unsigned long last_average_calculation = 0;
unsigned long last_displayed_measurement = 0;
unsigned long average_measurement_time = 10000;
unsigned long average_calculation_time = 60000;

const unsigned long eeprom_reset_time = 5000;
const unsigned long measurement_change_time = 5000;
const unsigned long scale_change_interval = 300;

void resetEEPROM();

// Definição da limpeza de tela
struct clearScreen {
  bool tempHumid : 1;
  bool clock : 1;
  bool luminosity : 1;
} clearScreens = {.tempHumid = true, .clock = true, .luminosity = true};

void setup() {
  warning(0);

  // Configurando a entrada dos botões
  pinMode(BUTTON0_INPUT_PIN, INPUT);
  pinMode(BUTTON1_INPUT_PIN, INPUT);
  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(HUMI_BUZZER_PIN, OUTPUT);

  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // Iniciando o sensor de temperatura
  dht.begin();

  // Iniciando o LCD
  lcd.init();
  lcd.clear();

  // Apresentação da empresa
  companyEntry();

  // Tempo do setup, para subtrair do millis()
  startMillis = millis();
}

void loop() {
  // Define o tempo atual com base no início do loop e não do setup
  currentTime = millis() - startMillis;

  // Leituras físicas
  readTemperature();
  readHumidity();
  readLuminosity();
  readClock();

  // Troca as informações da tela e limpa a cada 5s
  if ((currentTime % 15000) >= 10000) {
    if (clearScreens.luminosity) {
      clearScreens.luminosity = false;
      clearScreens.clock = true;

      // Definição a mais para não atualizar a tela com o botão de escala
      clearScreens.tempHumid = true;
      lcd.clear();
    }
    displayLuminosityMeasurement();
  } else if ((currentTime % 15000) >= 5000) {
    if (clearScreens.tempHumid) {
      clearScreens.tempHumid = false;
      clearScreens.luminosity = true;
      lcd.clear();
    }
    displayTempHumidMeasurement();
  } else if ((currentTime % 15000) >= 0) {
    if (clearScreens.clock) {
      clearScreens.clock = false;
      clearScreens.tempHumid = true;
      lcd.clear();
    }
    displayClock();
  }

  // Valores para a média
  if ((currentTime - last_average_measurement) >= average_measurement_time) {
    last_average_measurement = currentTime;

    averages.temperature += measurements.temperature;
    averages.humidity += measurements.humidity;
    averages.luminosity += measurements.luminosity;
  }

  // Calculando as médias
  if ((currentTime - last_average_calculation) >= average_calculation_time) {
    last_average_calculation = currentTime;

    // Dividir pelo número de medições
    averages.temperature /= 6.0;
    averages.humidity /= 6.0;
    averages.luminosity /= 6.0;

    if (!(averages.humidity > 30.0 && averages.humidity < 50.0)) {
      warning(1); // Adiciona ao contador de problemas de umidade
    }

    if (!(averages.temperature > 15.0 && averages.temperature < 25.0)) {
      warning(2); // Adiciona ao contador de problemas de temperatura
    }

    if (averages.luminosity > 30.0) {
      warning(3); // Adiciona ao contador de problemas de luminosidade
    }

    // Resetando os valores médios
    averages.temperature = 0;
    averages.humidity = 0;
    averages.luminosity = 0;
  }

  // Lendo o primeiro botão - mudança de escala de temperatura
  buttons.button0_state = digitalRead(BUTTON0_INPUT_PIN);
  if (buttons.button0_state == HIGH &&
      ((currentTime - scale_change_marker) >= scale_change_interval)
      && !clearScreens.tempHumid) {
    scale_change_marker = currentTime;
    changeScale();
    lcd.clear();
  }

  // Lendo o segundo botão - reset da EEPROM
  eeprom_reset_timer = currentTime;
  while (digitalRead(BUTTON0_INPUT_PIN) == HIGH &&
         digitalRead(BUTTON1_INPUT_PIN) == HIGH) {

    if ((currentTime - eeprom_reset_timer) >= eeprom_reset_time) {
      resetEEPROM();
      displayReset();
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
