![Data_Hopper](doc/Data_Hopper.png)

## Índice

1. [Sobre](#sobre)
2. [Objetivo](#objetivo)
3. [Especificações técnicas](#especificações-técnicas)
   1. [Materiais utilizados](#materiais-utilizados)
   2. [Funcionalidade](#funcionalidade)
4. [Manual de operação do Data Hopper](#manual-de-operação-do-data-hopper)
5. [Montagem do projeto e seu diagrama elétrico](#montagem-do-projeto-e-seu-diagrama-elétrico)
   1. [Montagem](#montagem)
   2. [Diagrama](#diagrama)

## Sobre
Data Hopper é um dispositivo baseado na plataforma Arduino UNO R3 capaz de medir e apresentar ao usuário os valores médios de luminosidade, temperatura e umidade de um ambiente industrial a qual estiver inserido em um display, além de armazenar e apresentar os instantes em que os valores estiverem fora dos intervalos especificados.

## Objetivo
O objetivo do dispositivo é realizar padronizadamente leituras de luminosidade, temperatura e umidade, apresentando os resultados no visor LCD e realizando o armazenamento dos valores em um EEPROM Data Logger, a fim de realizar um cálculo da média ponderada, estabelecendo níveis de referência a se limitar a mudança desses valores. Caso os níveis de referência sejam ultrapassados ou não sejam atingidos pelo sensor DHT-11, será soado um alarme (buzzer) para alertar a discrepância e um ou mais LEDs serão acesos para indicar a leitura discrepante.

## Especificações técnicas
### Materiais utilizados
| Quantidade | Componente                                         |
|------------|----------------------------------------------------|
| 1          | Piezo Buzzer                                       |
| 1          | LCD1602-I2C                                        |
| 1          | Arduino Uno (Rev3)                                 |
| 1          | DS1307 RTC (v1.1)                                  |
| 1          | LED Vermelho                                       |
| 1          | LED Amarelo                                        |
| 1          | LED Verde                                          |
| 1          | DHT11 (Sensor de Umidade e Temperatura)            |
| 1          | LDR (fotocélula)                                   |
| 5          | Resistor (330Ω)                                    |
| 2          | Resistor (10kΩ)                                    |
| 2          | Pushbutton                                         |

### Funcionalidade
>TODO

### Manual de operação do Data Hopper
![Manual](doc/Manual.png)

A navegação do dispositivo dispõe-se do uso de dois botões acionáveis e um display LCD para exibir as informações processadas ao usuário. A temperatura pode ser apresentada dentre as três escalas disponíveis (Kelvin, Celsius ou Fahreinheit), podendo ser alternada com o acionamento do primeiro botão. Abaixo da temperatura, é apresentada o valor da porcentagem da umidade e, após curtos instantes, é mostrado o valor da luminosidade. O segundo botão alterna entre os valores atuais e os de discrepância registrados, revelando os valores médios e o horário e data do registro.

## Montagem do projeto e seu diagrama elétrico

### Montagem

<details>
<summary>Veja a montagem</summary>

![Montagem](doc/Montagem.png)

</details>

### Diagrama

<details>
<summary>Veja o diagrama elétrico</summary>

![Diagrama](doc/Diagrama.jpg)

</details>


