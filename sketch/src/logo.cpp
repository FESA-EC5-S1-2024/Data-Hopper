#include "../include/config.hpp"
#include "../include/logo.hpp"

// Desenho da Apresentação
byte grasshopper0[] = {0b00000, 0b00000, 0b00000, 0b00000,
                       0b00011, 0b01100, 0b10001, 0b01111};

byte grasshopper1[] = {0b00000, 0b00000, 0b00000, 0b00000,
                       0b11100, 0b00010, 0b00001, 0b10000};

byte grasshopper2[] = {0b00000, 0b00000, 0b00000, 0b00000,
                       0b00001, 0b00001, 0b11111, 0b00000};

byte grasshopper3[] = {0b00010, 0b00100, 0b01000, 0b11110,
                       0b00001, 0b00001, 0b00010, 0b11100};

byte grasshopper4[] = {0b00100, 0b00101, 0b00101, 0b00101,
                       0b00101, 0b00101, 0b01010, 0b11100};

byte grasshopper5[] = {0b01111, 0b00000, 0b11111, 0b00000,
                       0b00000, 0b00000, 0b00000, 0b00000};

byte grasshopper6[] = {0b10000, 0b01000, 0b00100, 0b11111,
                       0b00101, 0b00101, 0b01010, 0b11100};

byte grasshopper7[] = {0b01000, 0b01000, 0b01000, 0b11000,
                       0b10100, 0b10110, 0b01001, 0b00110};

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
