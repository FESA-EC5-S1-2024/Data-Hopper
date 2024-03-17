#include "../include/config.hpp"

// Inicializando o lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicializando o rtc
RTC_DS3231 rtc;

// Inicializando o dht
DHT dht(DHT_PIN, DHT11);
