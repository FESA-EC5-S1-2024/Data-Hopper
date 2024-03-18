#include "../include/alert.hpp"
#include "../include/config.hpp"

struct Alert Alerts = {.temperature = 0, .humidity = 0, .luminosity = 0};
struct Medias medias = {.temperatura = 0, .umidade = 0, .lumisidade = 0}

void warning(short type) {
  switch (type) {
  case 0:
    EEPROM.get(0, Alerts);
    EEPROM_Pointer = sizeof(Alerts);
    break;
  case 1:
    Alerts.humidity += 1;
    break;
  case 2:
    Alerts.temperature += 1;
    break;
  case 3:
    Alerts.luminosity += 1;
    break;
  }

  EEPROM.put(0, Alerts);

  tone(HUMI_BUZZER_PIN, 440, 100);
}
