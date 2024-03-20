#pragma once

// Libs
#include "../lib/List/src/List.hpp"
#include "../include/config.hpp"

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

export struct Data write;
export struct Data read;
export List<Data> eepromList;