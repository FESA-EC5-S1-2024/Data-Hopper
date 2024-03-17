#pragma once

void leituraTemperatura();
void leituraUmidade();
void leituraLuminosidade();

void mudaEscala();

void apresentacaoMedicaoTempUmid();
void apresentacaoMedicaoLumi();

void apresentacaoReset();

struct Medidas {
  float temperatura;
  float umidade;
  float luminosidade;
};

struct EscalaTemperatura {
  unsigned char seletor : 2;
};
