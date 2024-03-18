#include "../include/config.hpp"
#include "../include/medidas.hpp"

struct Medidas medicoes = {
    .temperatura = 0.0, .umidade = 0.0, .luminosidade = 0.0};
struct EscalaTemperatura escala = {.seletor = 0};

void leituraTemperatura() { medicoes.temperatura = dht.readTemperature(); }

void leituraUmidade() { medicoes.umidade = dht.readHumidity(); }

void leituraLuminosidade() {
  medicoes.luminosidade = map(analogRead(LDR_PIN), 0, 1023, 100, 0);
}

void leituraRelogio(){
  medicoes.now = rtc.now();
}

void mudaEscala() {

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

void apresentacaoMedicaoTempUmid() {

  lcd.clear();
  lcd.setCursor(0, 0);

  // Print temperatura

  lcd.print("Temp.: ");

  switch (escala.seletor) {

  case 0:
    lcd.print(medicoes.temperatura);
    lcd.print((char)223);
    lcd.print("C");
    break;

  case 1:
    lcd.print(((medicoes.temperatura) * 1.8) + 32);
    lcd.print((char)223);
    lcd.print("F");
    break;

  case 2:
    lcd.print(medicoes.temperatura + 273.15);
    lcd.print("K");
    break;
  }

  // Print umidade
  lcd.setCursor(0, 1);
  lcd.print("Umid.: ");
  lcd.print(medicoes.umidade);
  lcd.print(" %");
}

void apresentacaoMedicaoLumi() {

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Lumi.: ");
  lcd.print(medicoes.luminosidade);
  lcd.print(" %");
}

void apresentacaoRelogio() {
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Hora: ");
  lcd.print(medicoes.now.hour(), DEC);
  lcd.print(':');
  lcd.print(medicoes.now.minute(), DEC);
  lcd.print(':');
  lcd.print(medicoes.now.second(), DEC);
}

void apresentacaoReset() {

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("EEPROM REINICIADA!!");
  delay(5000);
}
