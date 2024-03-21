// Incluindo o recurso necessário
#include "../include/alert.hpp"
#include "../include/config.hpp"

// Inicializando o objeto do ldc
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicializando o objeto do rtc
RTC_DS1307 rtc;

// Inicializando o objeto do dht
DHT dht(DHT_PIN, DHT11);

// Inicializando ponteiro da EEPROM
size_t EEPROM_Pointer = 0;
size_t EEPROM_Pointer_begin = 0;

char daysOfTheWeekPOR[7][12] = {"Dom", "Seg", "Ter", "Qua",
                                "Qui", "Sex", "Sab"};
char daysOfTheWeekENG[7][12] = {"Sun", "Mon", "Tue", "Wed",
                                "Thu", "Fri", "Sat"};
char daysOfTheWeekESP[7][12] = {"Dom", "Lun", "Mar", "Mié",
                                "Jue", "Vie", "Sáb"};

struct Button buttons = {.button0_state = 0, .button1_state = 0};

unsigned long startMillis = 0;
unsigned long eeprom_data_marker = 0;
unsigned long eeprom_reset_timer = 0;

unsigned long scale_change_marker = 0;

unsigned long last_average_measurement = 0;
unsigned long last_average_calculation = 0;
unsigned long last_displayed_measurement = 0;

unsigned long totalPauseTime = 0;
unsigned long startPauseTime = 0;

unsigned long currentTime() { return millis() - startMillis - totalPauseTime; }

void setLanguageAndScale() {
  byte languageAndScale = 1;
  while (true) {
    buttons.button0_state = digitalRead(BUTTON0_INPUT_PIN);
    if (buttons.button0_state == HIGH) {
      if (languageAndScale == 9) {
        languageAndScale = 1;
      } else {
        languageAndScale++;
      }

      lcd.clear();
      if (languageAndScale >= 1 && languageAndScale <= 3) {
        lcd.setCursor(0, 0);
        lcd.print("Lingua Escala");
      } else if (languageAndScale >= 4 && languageAndScale <= 6) {
        lcd.setCursor(0, 0);
        lcd.print("Language Scale");
      } else if (languageAndScale >= 7 && languageAndScale <= 9) {
        lcd.setCursor(0, 0);
        lcd.print("Idioma Escala");
      }

      lcd.setCursor(0, 1);
      switch (languageAndScale) {
      case 1:
        lcd.print("Portugues - ");
        lcd.print((char)223);
        lcd.print("C");
        break;
      case 2:
        lcd.print("Portugues - ");
        lcd.print((char)223);
        lcd.print("F");
        break;
      case 3:
        lcd.print("Portugues - K");
        break;
      case 4:
        lcd.print("English - ");
        lcd.print((char)223);
        lcd.print("C");
        break;
      case 5:
        lcd.print("English - ");
        lcd.print((char)223);
        lcd.print("F");
        break;
      case 6:
        lcd.print("English - K");
        break;
      case 7:
        lcd.print("Espanol - ");
        lcd.print((char)223);
        lcd.print("C");
        break;
      case 8:
        lcd.print("Espanol - ");
        lcd.print((char)223);
        lcd.print("F");
        break;
      case 9:
        lcd.print("Espanol - K");
        break;
      }
    }

    buttons.button1_state = digitalRead(BUTTON1_INPUT_PIN);
    if (buttons.button1_state == HIGH) {
      lcd.clear();
      Alerts.selectedMode = languageAndScale;
      return;
    }
  }
}
