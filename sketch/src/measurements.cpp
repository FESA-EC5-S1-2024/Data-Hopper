// Incluindo os recursos necessários
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

// Função para mudar a escala de temperatura
void changeScale() {
  switch (scale.selector) {
  case 0:
    scale.selector = 1;
    break;

  case 1:
    scale.selector = 2;
    break;

  case 2:
    scale.selector = 0;
    break;
  }
}

// Função para exibir a medição de temperatura e umidade
void displayTempHumidMeasurement() {
  lcd.setCursor(0, 0);

  lcd.print("Temp.: ");

  switch (scale.selector) {

  case 0:
    lcd.print(measurements.temperature);
    lcd.print((char)223);
    lcd.print("C");
    break;

  case 1:
    lcd.print(((measurements.temperature) * 1.8) + 32);
    lcd.print((char)223);
    lcd.print("F");
    break;

  case 2:
    lcd.print(measurements.temperature + 273.15);
    lcd.print(" K");
    break;
  }

  // Imprimir umidade
  lcd.setCursor(0, 1);
  lcd.print("Umid.: ");
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
  lcd.print("Time:");
  lcd.print(" ");
  lcd.print(measurements.now.hour());
  lcd.print(':');
  lcd.print(measurements.now.minute());
  lcd.print(':');
  lcd.print(measurements.now.second());
  lcd.print("  ");

  lcd.setCursor(0, 1);
  lcd.print(daysOfTheWeek[measurements.now.dayOfTheWeek()]);
  lcd.print(" : ");
  lcd.print(measurements.now.day());
  lcd.print('/');
  lcd.print(measurements.now.month());
  lcd.print('/');
  lcd.print(measurements.now.year());
  lcd.print("  ");
}
