![Data_Hopper](doc/Data_Hopper.png)

## Índice

1. [Sobre](#sobre)
2. [Objetivo](#objetivo)
3. [Especificações técnicas](#especificações-técnicas)
   1. [Materiais utilizados](#materiais-utilizados)
   2. [Funcionalidade](#funcionalidade)
4. [Manual de operação do Data Hopper](#manual-de-operação-do-data-hopper)
   1. [Inicialização](#inicialização)
   2. [Uso Geral](#uso-geral)
6. [Montagem do projeto e seu diagrama elétrico](#montagem-do-projeto-e-seu-diagrama-elétrico)
   1. [Montagem](#montagem)
   2. [Diagrama](#diagrama)

## Sobre
Data Hopper é um dispositivo baseado na plataforma Arduino UNO R3 capaz de medir e apresentar ao usuário os valores médios de luminosidade, temperatura e umidade de um ambiente industrial a qual estiver inserido em um display, além de armazenar e apresentar os instantes em que os valores estiverem fora dos intervalos especificados, capaz de guardar até 92 registros.

## Objetivo
O objetivo principal é realizar padronizadamente o monitoramento das condições ambientais em ambientes industriais, permitindo calcular a média ponderada, estabelecer níveis de referência e alertar de forma sonora e visual discrepâncias das variaveis monitoradas.

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

## Funcionalidade
O dispositivo é capaz de medir e exibir os valores médios de luminosidade, temperatura e umidade de um ambiente industrial em um display. Com a ação de um EEPROM Data Logger, ele lê e armazena os instantes em que os valores estão fora dos intervalos especificados, fornecendo ontrole sobre as condições ambientais. Casos os valores de referência sejam ultrapassados ou nao atingidos pelo sensor DHT-11, será acionado um alarme sonoro (buzzer) para alertar a discrepância e um ou mais LEDs serão acesos para indicar a leitura discrepante.

## Manual de operação do Data Hopper
![Manual](doc/Manual.png)

A navegação do dispositivo dispõe-se do uso de dois botões acionáveis e um display LCD para exibir as informações processadas ao usuário. A temperatura pode ser apresentada dentre as três escalas disponíveis (Kelvin, Celsius ou Fahreinheit).

### Inicialização
Ao ligar o dispositivo, será pedido ao usuário a configuração inicial das informações exibidas: a escala de temperatura e a linguagem. As opções podem ser confirmadas pelo acionamento do primeiro botão e serem alternadas com o segundo.

### Uso Geral
Abaixo da temperatura, é apresentada o valor da porcentagem da umidade e, após curtos instantes, o valor da luminosidade. O primeiro botão alterna entre as escalas de temperatura, enquanto o segundo alterna entre os valores atuais e os de discrepância registrados, revelando os valores médios e o horário e data do registro. Pressionando ambos ao mesmo tempo por alguns instantes permite que o usuário restaure o EEPROM, eliminando os registros anteriores.


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


