// Incluindo os recursos necessários
#include "../include/alert.hpp"
#include "../include/config.hpp"

// Criando as estruturas globalmente
struct Alert Alerts = {.temperature = 0, .humidity = 0, .luminosity = 0};
struct Average averages = {.temperature = 0, .humidity = 0, .luminosity = 0};

// Definindo a função de aviso
void warning(short type) {
  switch (type) {
  case 0: // Modo de puxar os dados iniciais da memória
    EEPROM.get(0, Alerts);
    EEPROM_Pointer = sizeof(Alerts);
    break;
  case 1: // Modo de erro de escala da umidade
    Alerts.humidity += 1;
    break;
  case 2: // Modo de erro de escala da temperatura
    Alerts.temperature += 1;
    break;
  case 3: // Modo de erro de escala de luminosidade
    Alerts.luminosity += 1;
    break;
  }

  // Ignora o funcionamento para os dados iniciais
  if (type) {
    EEPROM.put(0, Alerts);

    tone(HUMI_BUZZER_PIN, 440, 100);
  }
}
