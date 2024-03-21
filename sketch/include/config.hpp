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

// Tempo das execuções
#define EEPROM_RESET_TIME 2000
#define EEPROM_DATA_INTERVAL 2000
#define AVERAGE_MEASUREMENT_TIME 10000
#define AVERAGE_CALCULATION_TIME 60000

#define MaxCC 8

struct Button {
  bool button0_state : 1;
  bool button1_state : 1;
};

extern char daysOfTheWeekPOR[7][12];
extern char daysOfTheWeekENG[7][12];
extern char daysOfTheWeekESP[7][12];

// Inicializando o objeto do lcd
extern LiquidCrystal_I2C lcd;

// Inicializando o objeto do rtc
extern RTC_DS1307 rtc;

// Inicializando o objeto do dht
extern DHT dht;

extern size_t EEPROM_Pointer;
extern size_t EEPROM_Pointer_begin;

extern struct Button buttons;

unsigned long currentTime();

void setLanguageAndScale();

// Controle de tempo
extern unsigned long startMillis;
extern unsigned long eeprom_data_marker;
extern unsigned long eeprom_reset_timer;

extern unsigned long scale_change_marker;

extern unsigned long last_average_measurement;
extern unsigned long last_average_calculation;
extern unsigned long last_displayed_measurement;

extern unsigned long totalPauseTime;
extern unsigned long startPauseTime;
