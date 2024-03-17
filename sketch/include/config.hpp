#pragma once

// Libs dos componentes
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <EEPROM.h>

// Pinos analógicos
#define DHT_PIN A1
#define LDR_PIN A2

// Pinos de alerta
#define TEMP_LED_PIN 1
#define HUMI_LED_PIN 2
#define LUZ_LED_PIN 3

// Botões de ações
#define BUTTON0_INPUT_PIN 5
#define BUTTON1_INPUT_PIN 6

// Buzzer de alerta
#define HUMI_BUZZER_PIN 7

// Inicializando o objeto do lcd
extern LiquidCrystal_I2C lcd;

// Inicializando o objeto do rtc
extern RTC_DS3231 rtc;

// Inicializando o objeto do dht
extern DHT dht;

extern size_t EEPROM_Pointer;

const char nomeEmpresa[] = "DATAHOPPER";
