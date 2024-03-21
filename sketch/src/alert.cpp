// Incluindo os recursos necessários
#include "../include/EEPROM.hpp"
#include "../include/alert.hpp"
#include "../include/config.hpp"

// Criando as estruturas globalmente
struct Alert Alerts = {.temperature = 0,
                       .humidity = 0,
                       .luminosity = 0,
                       .counter = 0,
                       .selectedMode = 0};
struct Average averages = {.temperature = 0, .humidity = 0, .luminosity = 0};

// Definindo a função de aviso
void warning(short type) {
  switch (type) {
  case 0: // Modo de puxar os dados iniciais da memória
    EEPROM.get(0, Alerts);
    EEPROM_Pointer_begin = sizeof(Alerts);
    EEPROM_Pointer = EEPROM_Pointer_begin;
    break;
  case 1: // Modo de erro de escala da umidade
    Alerts.humidity += 1;
    write.average = averages.humidity;
    write.alert = 1;
    break;
  case 2: // Modo de erro de escala da temperatura
    Alerts.temperature += 1;
    write.average = averages.temperature;
    write.alert = 2;
    break;
  case 3: // Modo de erro de escala de luminosidade
    Alerts.luminosity += 1;
    write.average = averages.luminosity;
    write.alert = 3;
    break;
  }

  if (type != 0) {
    Alerts.counter++;
    WriteEEPROM();
  }

  // Ignora o funcionamento para os dados iniciais
  if (type) {
    EEPROM.put(0, Alerts);

    tone(HUMI_BUZZER_PIN, 440, 100);
  }
}
