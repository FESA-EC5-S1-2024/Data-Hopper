#pragma once

//Definição da estrutura de gravação na EEPROM
struct Write {
    DateTime time;
    float average;
    char alert;
};

void WriteEEPROM();
void ReadEEPROM();

export struct Data write;
export struct Data read;