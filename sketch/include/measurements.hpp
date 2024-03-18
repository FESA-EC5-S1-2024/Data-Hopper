#pragma once

// Definição da estrutura de medições
struct Measurement {
  float temperature;
  float humidity;
  float luminosity;
  DateTime now;
};

// Exportando a estrutura de medições
extern struct Measurement measurements;

// Definição da estrutura escalas
struct TemperatureScale {
  unsigned char selector : 2;
};

// Criando as definições das funções de leitura
void readTemperature();
void readHumidity();
void readLuminosity();
void readClock();

// Criando as definições das funções que exibem informções
void displayTempHumidMeasurement();
void displayLuminosityMeasurement();
void displayClock();
void displayReset();

// Criando a definição da função de mudar a escala
void changeScale();
