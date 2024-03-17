#include "../include/config.hpp"
#include "../include/alert.hpp"

struct Alert Alerts = {.temperature = 0, .humidity = 0, .luminosity = 0};
void warning(short type){
 
  switch (type) {
    case 0:
      Alerts.humidity += 1;
      break;
    case 1:
      Alerts.temperature += 1;
      break;
    case 2:
      Alerts.luminosity += 1;
      break;
  }
  
  tone(HUMI_BUZZER_PIN, 440, 100); 
} 
