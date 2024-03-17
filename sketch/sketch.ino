// Pinons analógicos
#define DHT_PIN A2
#define LDR_PIN A3

// Pinos de alerta
#define TEMP_LED_PIN 2
#define HUMI_LED_PIN 3
#define LUZ_LED_PIN 4

// Botões de ações
#define BUTTON1_INPUT_PIN 5
#define BUTTON2_INPUT_PIN 6

// Buzzer de alerta
//#define HUMI_BUZZER_PIN 7

// Lib do LDC I2C - Display
#include<LiquidCrystal_I2C.h>

// Lib da configuração dos cabos analógicos
#include<Wire.h>

// Lib do RTC - Real Time Clock
#include "RTClib.h"

// Lib do DHT22 - sensor de temperatura
#include <DHT.h>

#include "include/logo.hpp"

// Inicializando os objetos
LiquidCrystal_I2C lcd(0x27,  16, 2);

RTC_DS3231 rtc;
DHT dht(DHT_PIN, DHT11);

// Seletor de escala de temperatura
struct EscalaTemperatura{
  unsigned char seletor : 2 ;
} escala = {.seletor = 0};

int intensidade_luz;

// Definição de estado de Botões
struct botoes{
  bool estado_botao1 : 1 ;
  bool estado_botao2 : 1 ;
} botoes = {.estado_botao1 = 0,
            .estado_botao2 = 0};

// Controle de escala
unsigned long marcacao = 0;

const unsigned long intervalo = 300;

const char nomeEmpresa[] = "DATAHOPPER";

void setup() {

  // Configurando Input de Botão
  pinMode(BUTTON1_INPUT_PIN, INPUT);
  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  //pinMode(HUMI_BUZZER_PIN, OUTPUT);

  // Iniciando Sensor de temperatura  
  dht.begin();

  // Iniciando lib de configuração de cabos
  //Wire.begin();

  // Iniciando LCD
  lcd.init();
  lcd.clear();
  lcd.noBacklight();

  // Apresantação da empresa
  entradaEmpresa();

}

void loop() {

  // Leituras físicas
  leituraTemperatura();
  leituraHumidade();
  leituraLuminozidade();

  // Leitura do primeiro botão
  botoes.estado_botao1 = digitalRead(BUTTON1_INPUT_PIN);
  if(botoes.estado_botao1 == HIGH && ((millis() - marcacao) >= intervalo)){
    marcacao = millis();
    mudaEscala();
  }

}

void leituraHumidade(){

  lcd.setCursor(0,1);

  lcd.print("Humi.:");
  lcd.print(dht.readHumidity());
  lcd.print(" %");

  float umidade = dht.readHumidity();

/*  if(!(umidade > 30.0 && umidade < 50.0)){
      tone(HUMI_BUZZER_PIN, 440, 1000);
    }
*/
}

void leituraTemperatura(){

  lcd.setCursor(0,0);
  lcd.print("Temp.:");

  static float celcius_temp = dht.readTemperature();

  if(!(celcius_temp > 15.0 && celcius_temp < 25.0)){
    digitalWrite(TEMP_LED_PIN, HIGH);
  }
  else{
    digitalWrite(TEMP_LED_PIN, LOW);
  }

  switch(escala.seletor){
    case 0:
      lcd.print(celcius_temp);
      lcd.print(" C");
      break;

    case 1:
      lcd.print(dht.readTemperature(true));
      lcd.print(" F");
      break;

    case 2:
      lcd.print(dht.readTemperature() + 273.15);
      lcd.print(" K");
      break;
  }
}

void leituraLuminozidade(){

  intensidade_luz = map(analogRead(LDR_PIN), 0, 1023, 100, 0);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(intensidade_luz);

  delay(5000);
  
}

void mudaEscala(){

  lcd.clear();

  switch(escala.seletor){

    case 0:
      escala.seletor = 1;
      break;

    case 1:
      escala.seletor = 2;
      break;

    case 2:
      escala.seletor = 0;
      break;

  }

}

void entradaEmpresa(){

  lcd.setCursor(2,0);

  for(int i = 0; i < 4; i++){
    lcd.print(nomeEmpresa[i]);
    delay(100);
  }

  lcd.setCursor(2,1);

  for(int i = 4; i < 10; i++){
    lcd.print(nomeEmpresa[i]);
    delay(100);
  }

  lcd.setCursor(9, 0);
  lcd.write(byte(0));
  
  lcd.setCursor(10, 0);
  lcd.write(byte(1));
  
  lcd.setCursor(11, 0);
  lcd.write(byte(2));
  
  lcd.setCursor(12, 0);
  lcd.write(byte(3));
  
  lcd.setCursor(9, 1);
  lcd.write(byte(4));
  
  lcd.setCursor(10, 1);
  lcd.write(byte(5));
  
  lcd.setCursor(11, 1);
  lcd.write(byte(6));
  
  lcd.setCursor(12, 1);
  lcd.write(byte(7));

  intervalo_millis(2500);
  lcd.clear();

}

void intervalo_millis(int tempo){

  while(true){

    if(!((millis() - marcacao) >= tempo)){
      marcacao = millis();
    }
    else{
      break;
      }
    
    }
  
  }
