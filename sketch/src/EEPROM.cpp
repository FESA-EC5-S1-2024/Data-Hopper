#include "../include/EEPROM.hpp"
#include "../include/alert.hpp"
#include "../include/config.hpp"

struct Data write;
struct Data read;
int readAddress;

void WriteEEPROM() {

  if ((EEPROM.length() - EEPROM_Pointer) < sizeof(write)) {
    // Sem espaço ma memória
    // Resetar ponteiro de endereço da EEPROM
    EEPROM_Pointer = EEPROM_Pointer_begin;
  }

  EEPROM.put(EEPROM_Pointer, write);
  EEPROM_Pointer += sizeof(write);
}

void ReadEEPROM(byte selectedMode) {

  // Local de onde começa a leitura
  readAddress = EEPROM_Pointer_begin;

  while (readAddress < EEPROM_Pointer) {
    // Pega dados da EEPROM
    EEPROM.get(readAddress, read);
    // Atualiza próximo endereço para pegar
    readAddress += sizeof(write);

    DisplayEEPROMReadings();

    buttons.button1_state = digitalRead(BUTTON1_INPUT_PIN);
    if (buttons.button1_state == HIGH) {
      return; // Sai da função se o botão 1 for pressionado
    }

    // Verifica se é modo manual e aguarda pressionar dos botões
    if (selectedMode == 1) {
      while (true) {
        
        if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
          lcd.setCursor(0, 0);
          lcd.print("Pressione o botão");
          lcd.setCursor(0, 1);
          lcd.print("Para continuar!");
        } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
          lcd.setCursor(0, 0);
          lcd.print("Press the button");
          lcd.setCursor(0, 1);
          lcd.print("To continue!");
        } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
          lcd.setCursor(0, 0);
          lcd.print("Presione el botón");
          lcd.setCursor(0, 1);
          lcd.print("Para continuar!");
        }
        
        buttons.button0_state = digitalRead(BUTTON0_INPUT_PIN);
        if (buttons.button0_state == HIGH) {
          break; // Sai do loop se o botão 0 for pressionado
        }

        delay(100); // Pequeno atraso para não sobrecarregar o processamento
      }
    }
  }
}

byte DisplayOptions() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
      Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Modo:");

  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Mode:");
  }
  lcd.setCursor(0, 1);
  lcd.print("2-Manual 1-Auto");

  delay(2000);
  byte selectedMode = 0;
  unsigned long startMillis = millis();
  while (millis() - startMillis < 8000) {
    buttons.button0_state = digitalRead(BUTTON0_INPUT_PIN);
    if (buttons.button0_state == HIGH) {
      selectedMode = 0; // Modo auto
      break;
    }

    buttons.button1_state = digitalRead(BUTTON1_INPUT_PIN);
    if (buttons.button1_state == HIGH) {
      selectedMode = 1; // Modo manual
      break;
    }
  }

  // Exibir modo selecionado no display
  lcd.clear();
  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Modo selecionado");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Selected mode");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Modo seleccionado");
  }

  lcd.setCursor(0, 1);
  if (selectedMode == 0) {
    lcd.print("Auto");
  } else if (selectedMode == 1) {
    lcd.print("Manual");
  }
  delay(2000);
  lcd.clear();

  return selectedMode;
}

void DisplayEEPROMReadings() {
  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Lendo EEPROM...");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Reading EEPROM...");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Leyendo EEPROM...");
  }
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Erro #");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 9) {
    lcd.print("Error #");
  }
  lcd.print((int)(readAddress - EEPROM_Pointer_begin) / sizeof(read));

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Data e Hora:");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Date and Time:");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Fecha y Hora:");
  }
  delay(2000);
  lcd.clear();

  // Display DateTime
  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Hora:");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Time:");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Tiempo:");
  }

  lcd.print(" ");
  lcd.print(read.time.hour());
  lcd.print(':');
  lcd.print(read.time.minute());
  lcd.print(':');
  lcd.print(read.time.second());
  lcd.print("  ");

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print(daysOfTheWeekPOR[read.time.dayOfTheWeek()]);
    lcd.print(" : ");
    lcd.print(read.time.day());
    lcd.print('/');
    lcd.print(read.time.month());
    lcd.print('/');
    lcd.print(read.time.year());
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print(daysOfTheWeekENG[read.time.dayOfTheWeek()]);

    lcd.print(read.time.month());
    lcd.print('/');
    lcd.print(read.time.day());
    lcd.print('/');
    lcd.print(read.time.year());
    lcd.print(" ");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print(daysOfTheWeekESP[read.time.dayOfTheWeek()]);
    lcd.print(" : ");
    lcd.print(read.time.day());
    lcd.print('/');
    lcd.print(read.time.month());
    lcd.print('/');
    lcd.print(read.time.year());
  }
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Erro #");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 9) {
    lcd.print("Error #");
  }
  lcd.print((int)(readAddress - EEPROM_Pointer_begin) / sizeof(read));

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
    lcd.print("Tipo e Valor:");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("Type and Value:");
  } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("Tipo y Valor:");
  }
  delay(2000);
  lcd.clear();

  // Display Value
  lcd.setCursor(0, 0);
  switch (read.alert) {
  case 1:
    digitalWrite(HUMI_LED_PIN, HIGH);
    lcd.setCursor(0, 0);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3) {
      lcd.print("Alerta Umid.!!");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Humi. Alert!!");
    } else if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("Alerta Humed.!!");
    }

    lcd.setCursor(0, 1);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
        Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("valor: ");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Value:");
    }
    lcd.print(read.average);
    lcd.print(" %");

    break;

  case 2:
    digitalWrite(TEMP_LED_PIN, HIGH);
    lcd.setCursor(0, 0);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
        Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("Alerta Temp.!!");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Temp. Alert!!");
    }

    lcd.setCursor(0, 1);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
        Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("valor: ");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Value:");
    }
    if (Alerts.selectedMode == 1 || Alerts.selectedMode == 4 ||
        Alerts.selectedMode == 7) {
      lcd.print(read.average);
      lcd.print((char)223);
      lcd.print("C");
    } else if (Alerts.selectedMode == 2 || Alerts.selectedMode == 5 ||
               Alerts.selectedMode == 8) {
      lcd.print(((read.average) * 1.8) + 32);
      lcd.print((char)223);
      lcd.print("F");
    } else if (Alerts.selectedMode == 3 || Alerts.selectedMode == 6 ||
               Alerts.selectedMode == 9) {
      lcd.print(read.average + 273.15);
      lcd.print(" K");
    }

    break;

  case 3:
    digitalWrite(LUMI_LED_PIN, HIGH);
    lcd.setCursor(0, 0);
    if (Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("Alerta lumi.!!");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Lumi. Alert!!");
    }

    lcd.setCursor(0, 1);
    if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
        Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
      lcd.print("valor: ");
    } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
      lcd.print("Value:");
    }
    lcd.print(read.average);
    lcd.print(" %");

    break;
  }

  delay(2000);
  digitalWrite(HUMI_LED_PIN, LOW);
  digitalWrite(TEMP_LED_PIN, LOW);
  digitalWrite(LUMI_LED_PIN, LOW);
  lcd.clear();
}

void ResetEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

void DisplayReset() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EEPROM");

  lcd.setCursor(0, 1);
  if (Alerts.selectedMode >= 1 && Alerts.selectedMode <= 3 ||
      Alerts.selectedMode >= 7 && Alerts.selectedMode <= 9) {
    lcd.print("REINICIADA!!");
  } else if (Alerts.selectedMode >= 4 && Alerts.selectedMode <= 6) {
    lcd.print("RESTARTED!!");
  }
  delay(5000);
}
