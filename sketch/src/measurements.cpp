// Incluindo os recursos necessários
#include "../include/alert.hpp"
#include "../include/config.hpp"
#include "../include/measurements.hpp"

// Inicializando a estrutura de medições
struct Measurement measurements = {
    .temperature = 0.0, .humidity = 0.0, .luminosity = 0.0};

// Inicializando a estrutura de escala de temperatura
struct TemperatureScale scale = {.selector = 0};

// Função para ler a temperatura do sensor DHT
void readTemperature() { measurements.temperature = dht.readTemperature(); }

// Função para ler a umidade do sensor DHT
void readHumidity() { measurements.humidity = dht.readHumidity(); }

// Função para ler a luminosidade do LDR
void readLuminosity() {
  measurements.luminosity = map(analogRead(LDR_PIN), 0, 1023, 100, 0);
}

// Função para ler o relógio em tempo real
void readClock() { measurements.now = rtc.now(); }

// Função para exibir a medição de temperatura e umidade
void displayTempHumidMeasurement() {
  lcd.setCursor(0, 0);

  lcd.print("Temp.: ");

  if (Alerts.selectedMode == 1 || Alerts.selectedMode == 4 ||
      Alerts.selectedMode == 7) {
    lcd.print(measurements.temperature);
    lcd.print((char)223);
    lcd.print("C");
  } else if (Alerts.selectedMode == 2 || Alerts.selectedMode == 5 ||
             Alerts.selectedMode == 8) {
    lcd.print(((measurements.temperature) * 1.8) + 32);
    lcd.print((char)223);
    lcd.print("F");
  } else if (Alerts.selectedMode == 3 || Alerts.selectedMode == 6 ||
             Alerts.selectedMode == 9) {
    lcd.print(measurements.temperature + 273.15);
    lcd.print(" K");
  }

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Umid.: ");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Humid.: ");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Humed.: ");
  }

  lcd.print(measurements.humidity);
  lcd.print(" %");
}

// Função para exibir a medição de luminosidade
void displayLuminosityMeasurement() {
  lcd.setCursor(0, 0);
  lcd.print("Lumi.: ");

  lcd.print(measurements.luminosity);
  lcd.print(" %");
}

// Função para exibir o relógio
void displayClock() {
  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Hora:");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Time:");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Tiempo:");
  }

  lcd.print(" ");
  lcd.print(measurements.now.hour());
  lcd.print(':');
  lcd.print(measurements.now.minute());
  lcd.print(':');
  lcd.print(measurements.now.second());
  lcd.print("  ");

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print(daysOfTheWeekPOR[measurements.now.dayOfTheWeek()]);
    lcd.print(" : ");
    lcd.print(measurements.now.day());
    lcd.print('/');
    lcd.print(measurements.now.month());
    lcd.print('/');
    lcd.print(measurements.now.year());
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print(daysOfTheWeekENG[measurements.now.dayOfTheWeek()]);

    lcd.print(measurements.now.month());
    lcd.print('/');
    lcd.print(measurements.now.day());
    lcd.print('/');
    lcd.print(measurements.now.year());
    lcd.print(" ");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print(daysOfTheWeekESP[measurements.now.dayOfTheWeek()]);
    lcd.print(" : ");
    lcd.print(measurements.now.day());
    lcd.print('/');
    lcd.print(measurements.now.month());
    lcd.print('/');
    lcd.print(measurements.now.year());
  }
}
