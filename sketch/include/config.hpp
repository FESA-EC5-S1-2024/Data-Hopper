#pragma once

// Libs dos componentes
#include <DHT.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Pinos analógicos
#define DHT_PIN A2
#define LDR_PIN A3

// Pinos de alerta
#define TEMP_LED_PIN 2 // Vermelho
#define HUMI_LED_PIN 3 // Amarelo
#define LUMI_LED_PIN 4 // Verde

// Botões de ações
#define BUTTON0_INPUT_PIN 5
#define BUTTON1_INPUT_PIN 6

// Buzzer de alerta
#define HUMI_BUZZER_PIN 7

// Inicializando o objeto do lcd
extern LiquidCrystal_I2C lcd;

// Inicializando o objeto do rtc
extern RTC_DS1307 rtc;

// Inicializando o objeto do dht
extern DHT dht;

extern size_t EEPROM_Pointer;
extern size_t EEPROM_Pointer_begin;
