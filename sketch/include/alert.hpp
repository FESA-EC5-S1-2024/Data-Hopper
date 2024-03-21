#pragma once

#include <RTClib.h>

// Definição da estrutura de alertas
struct Alert {
  byte temperature;
  byte humidity;
  byte luminosity;
  byte counter;
  byte selectedMode;
};

// Definição da estrutura de médias
struct Average {
  float temperature;
  float humidity;
  float luminosity;
  DateTime now;
};

// Exportando a estrutura de alertas
extern struct Alert Alerts;

// Exportando a estrutura de medias
extern struct Average averages;

// Criando a definição da função de aviso
void warning(short type);
