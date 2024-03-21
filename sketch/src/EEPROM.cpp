#include "../include/EEPROM.hpp"
#include "../include/config.hpp"

struct Data write;
struct Data read;
int readAddress;

void WriteEEPROM() {

    if ((EEPROM.length() - EEPROM_Pointer) < sizeof(write)) {
      //Sem espaço ma memória
      //Resetar ponteiro de endereço da EEPROM
      EEPROM_Pointer = EEPROM_Pointer_begin;
    }

    EEPROM.put(EEPROM_Pointer, write);
    EEPROM_Pointer += sizeof(write);

}

void ReadEEPROM() {

    //Local de onde começa a leitura
    readAddress = EEPROM_Pointer_begin;

    while (readAddress < EEPROM_Pointer) {
        // Pega dados da EEPROM
        EEPROM.get(readAddress, read);
        //Atualiza próximo endereço para pegar
        readAddress += sizeof(write);
        
        DisplayEEPROMReadings();
    }
	
	lcd.print("Leitura Realizada!");
	delay(1500);
	
	lcd.clear();
	

}

void ResetEEPROM() {
    for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
    }
}

void DisplayEEPROMReadings() {

lcd.setCursor(0, 0);
lcd.print("Reading EEPROM...");
delay(2000);
lcd.clear();

lcd.setCursor(0, 0);
lcd.print("Error #");
lcd.print((int)(readAddress - EEPROM_Pointer_begin)/sizeof(read));
lcd.setCursor(0, 1);
lcd.print("Date and Time:");
delay(2000);
lcd.clear();

//Display DateTime
lcd.setCursor(0, 0);
lcd.print("Time:");
lcd.print(" ");

lcd.print(read.time.hour());
lcd.print(':');
lcd.print(read.time.minute());
lcd.print(':');
lcd.print(read.time.second());
lcd.print("  ");

lcd.setCursor(0, 1);
lcd.print(daysOfTheWeek[read.time.dayOfTheWeek()]);
lcd.print(" : ");
lcd.print(read.time.day());
lcd.print('/');
lcd.print(read.time.month());
lcd.print('/');
lcd.print(read.time.year());
lcd.print("  ");

delay(2000);
lcd.clear();

lcd.setCursor(0, 0);
lcd.print("Error #");
lcd.print((int)(readAddress - EEPROM_Pointer_begin)/sizeof(read));
lcd.setCursor(0, 1);
lcd.print("Type and Value:");
delay(2000);
lcd.clear();

//Display Value
lcd.setCursor(0, 0);

switch(read.alert){

  case 1:

  lcd.setCursor(0,0);
  lcd.print("Humi. Alert!!");

  lcd.setCursor(0,1);

  lcd.print("Value: ");
  lcd.print(read.average);
  lcd.print(" %");

  break;

  case 2:

  lcd.setCursor(0,0);
  lcd.print("Temp. Alert!!");

  lcd.setCursor(0,1);

  lcd.print("Value: ");
  lcd.print(read.average);
  lcd.print(" %");

  break;

  case 3:

  lcd.setCursor(0,0);
  lcd.print("Lumi. Alert!!");

  lcd.setCursor(0,1);

  lcd.print("Value: ");
  lcd.print(read.average);
  lcd.print(" %");

  break;
}



delay(2000);

lcd.clear();
    
 }


void DisplayReset() {
  lcd.setCursor(0, 0);

  lcd.print("EEPROM REINICIADA!!");
  delay(5000);
}