// Incluindo o recurso necessário
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

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};