#pragma once

#include "Arduino.h"

void leituraTemperatura();
void leituraHumidade();
void leituraLuminosidade();

void mudaEscala();

void apresentacaoMedicaoTempUmid();
void apresentacaoMedicaoLumi();

struct Medidas {
  float temperatura;
  float umidade;
  float luminosidade;
};

struct EscalaTemperatura {
  unsigned char seletor : 2;
};
