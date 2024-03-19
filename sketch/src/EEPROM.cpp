#include "../include/EEPROM.hpp"

struct Data write = {.average = 0, .alert = 0};
struct Data read;

void WriteEEPROM() {
    EEPROM.put(EEPROM_Pointer, write);
    EEPROM_Pointer += sizeof(write);
}

void ReadEEPROM() {
    int i = EEPROM_Pointer_begin;

    while (i < counter) {
        EEPROM.get(i, read);
        i += sizeof(write);
        //add read to array
    }
}