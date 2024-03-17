#include "../include/config.hpp"
#include "../include/logo.hpp"

// Desenho da Apresentação
byte grasshopper0[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B01100,
  B10001,
  B01111
};

byte grasshopper1[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11100,
  B00010,
  B00001,
  B10000
};

byte grasshopper2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B11111,
  B00000
};

byte grasshopper3[] = {
  B00010,
  B00100,
  B01000,
  B11110,
  B00001,
  B00001,
  B00010,
  B11100
};

byte grasshopper4[] = {
  B00100,
  B00101,
  B00101,
  B00101,
  B00101,
  B00101,
  B01010,
  B11100
};

byte grasshopper5[] = {
  B01111,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte grasshopper6[] = {
  B10000,
  B01000,
  B00100,
  B11111,
  B00101,
  B00101,
  B01010,
  B11100
};

byte grasshopper7[] = {
  B01000,
  B01000,
  B01000,
  B11000,
  B10100,
  B10110,
  B01001,
  B00110
};

void entradaEmpresa() {

  lcd.setCursor(2, 0);

  for (int i = 0; i < 4; i++) {
    lcd.print(nomeEmpresa[i]);
    delay(100);
  }

  lcd.setCursor(2, 1);

  for (int i = 4; i < 10; i++) {
    lcd.print(nomeEmpresa[i]);
    delay(100);
  }

  lcd.createChar(0, grasshopper0);
  lcd.createChar(1, grasshopper1);
  lcd.createChar(2, grasshopper2);
  lcd.createChar(3, grasshopper3);
  lcd.createChar(4, grasshopper4);
  lcd.createChar(5, grasshopper5);
  lcd.createChar(6, grasshopper6);
  lcd.createChar(7, grasshopper7);

  lcd.setCursor(9, 0);
  lcd.write(byte(0));

  lcd.setCursor(10, 0);
  lcd.write(byte(1));

  lcd.setCursor(11, 0);
  lcd.write(byte(2));

  lcd.setCursor(12, 0);
  lcd.write(byte(3));

  lcd.setCursor(9, 1);
  lcd.write(byte(4));

  lcd.setCursor(10, 1);
  lcd.write(byte(5));

  lcd.setCursor(11, 1);
  lcd.write(byte(6));

  lcd.setCursor(12, 1);
  lcd.write(byte(7));

  delay(2500);
  lcd.clear();
}
