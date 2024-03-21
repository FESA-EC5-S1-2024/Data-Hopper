#pragma once

// Libs
#include "../include/config.hpp"
#include <RTClib.h>

// Definição da estrutura de gravação e recuperação de dados na EEPROM
struct Data {
    DateTime time;
    float average;
    char alert;
};

// Métodos de acesso a EEPROM
void WriteEEPROM();
void ReadEEPROM();
void ResetEEPROM();

void DisplayReset();
void DisplayEEPROMReadings();

extern struct Data write;
extern struct Data read;
extern int readAdress;