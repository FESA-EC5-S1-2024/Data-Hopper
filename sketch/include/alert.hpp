#pragma once

// Definição da estrutura de alertas
struct Alert {
  unsigned char temperature;
  unsigned char humidity;
  unsigned char luminosity;
};

// Definição da estrutura de médias
struct Average {
  float temperature;
  float humidity;
  float luminosity;
};

// Exportando a estrutura de medias
extern struct Average averages;

// Criando a definição da função de aviso
void warning(short type);
