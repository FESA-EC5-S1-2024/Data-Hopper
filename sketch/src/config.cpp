#include "../include/config.hpp"

// Inicializando o objeto do ldc
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicializando o objeto do rtc
RTC_DS3231 rtc;

// Inicializando o objeto do dht
DHT dht(DHT_PIN, DHT11);
