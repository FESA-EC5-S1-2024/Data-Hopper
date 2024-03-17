// Lib da configuração dos cabos analógicos
#include<Wire.h>

#include "include/config.hpp"
#include "include/logo.hpp"

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

