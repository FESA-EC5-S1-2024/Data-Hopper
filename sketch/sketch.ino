// Biblioteca de configuração de cabos analógicos
#include <Wire.h>

// Arquivos externos
#include "include/EEPROM.hpp"
#include "include/alert.hpp"
#include "include/config.hpp"
#include "include/logo.hpp"
#include "include/measurements.hpp"

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
  pinMode(HUMI_LED_PIN, OUTPUT);
  pinMode(LUMI_LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(HUMI_BUZZER_PIN, OUTPUT);

  Serial.begin(9600);

  // Início e configuração da data do RTC
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Iniciando o sensor de temperatura
  dht.begin();

  // Iniciando o LCD
  lcd.init();
  lcd.clear();

  // Apresentação da empresa
  companyEntry();
  if (Alerts.selectedMode == 0) {
    setLanguageAndScale();
  }
  // Tempo do setup, para subtrair do millis()
  startMillis = millis();
}

void loop() {
  // Leituras físicas
  readTemperature();
  readHumidity();
  readLuminosity();
  readClock();

  // Troca as informações da tela e limpa a cada 5s
  if ((currentTime() % 15000) >= 10000) {
    if (clearScreens.luminosity) {
      clearScreens.luminosity = false;
      clearScreens.clock = true;
      lcd.clear();
    }
    displayLuminosityMeasurement();
  } else if ((currentTime() % 15000) >= 5000) {
    if (clearScreens.tempHumid) {
      clearScreens.tempHumid = false;
      clearScreens.luminosity = true;
      lcd.clear();
    }
    displayTempHumidMeasurement();
  } else if ((currentTime() % 15000) >= 0) {
    if (clearScreens.clock) {
      clearScreens.clock = false;
      clearScreens.tempHumid = true;
      lcd.clear();
    }
    displayClock();
  }

  // Valores para a média
  if ((currentTime() - last_average_measurement) >= AVERAGE_MEASUREMENT_TIME) {
    last_average_measurement = currentTime();

    averages.temperature += measurements.temperature;
    averages.humidity += measurements.humidity;
    averages.luminosity += measurements.luminosity;
  }

  // Calculando as médias
  if ((currentTime() - last_average_calculation) >= AVERAGE_CALCULATION_TIME) {
    last_average_calculation = currentTime();

    // Dividir pelo número de medições
    averages.temperature /= 6.0;
    averages.humidity /= 6.0;
    averages.luminosity /= 6.0;
    averages.now = rtc.now();

    write.time = averages.now;

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

  // Lendo o segundo botão - modo de pause e demonstração de valoes da EEPROM
  buttons.button1_state = digitalRead(BUTTON1_INPUT_PIN);
  if (buttons.button1_state == HIGH &&
      (currentTime() - eeprom_data_marker) >= EEPROM_DATA_INTERVAL) {

    lcd.backlight();
    startPauseTime = currentTime();
    eeprom_data_marker = currentTime();

    byte selectedMode = DisplayOptions();

    ReadEEPROM(selectedMode);
    lcd.setCursor(0, 0);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
      lcd.print("Leitura");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Reading");
    } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("Lectura");
    }

    lcd.setCursor(0, 1);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
      lcd.print("Realizada!");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Completed!");
    } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("Completada!");
    }
    delay(2000);
    totalPauseTime += currentTime() - startPauseTime;

    lcd.noBacklight();
  }

  // Lê ambos os botôes - Reset da EEPROM
  eeprom_reset_timer = currentTime();
  while (digitalRead(BUTTON0_INPUT_PIN) == HIGH) {

    if ((currentTime() - eeprom_reset_timer) >= EEPROM_RESET_TIME) {
      ResetEEPROM();
      DisplayReset();

      // Reseta o Arduino
      void (*resetFunc)(void) = 0;
      resetFunc();
    }
  }
}
