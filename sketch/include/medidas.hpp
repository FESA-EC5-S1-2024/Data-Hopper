#pragma once

void leituraTemperatura();
void leituraUmidade();
void leituraLuminosidade();
void leituraRelogio();

void mudaEscala();

void apresentacaoMedicaoTempUmid();
void apresentacaoMedicaoLumi();
void apresentacaoRelogio();

void apresentacaoReset();

struct Medidas {
  float temperatura;
  float umidade;
  float luminosidade;
  DateTime now;
};

struct EscalaTemperatura {
  unsigned char seletor : 2;
};
