# Projeto de Monitoramento da Qualidade da Água com IoT

## Descrição

Este projeto visa desenvolver um sistema de monitoramento da qualidade da água utilizando a tecnologia da Internet das Coisas (IoT). Utilizando o ESP32 como controlador principal, o sistema simula sensores de pH e turbidez através de potenciômetros para coletar dados em tempo real. Esses dados são exibidos em um display LCD e transmitidos via protocolo MQTT para serem analisados e visualizados em uma plataforma de dashboard como Grafana.

## Objetivos

- Monitorar em tempo real os parâmetros críticos que definem a qualidade da água, como pH e turbidez.
- Utilizar tecnologias de baixo custo para facilitar a replicação do sistema em diferentes localidades.
- Promover a gestão eficaz e sustentável dos recursos hídricos através da tecnologia IoT.

## Componentes do Hardware

- ESP32 Dev Module
- Display LCD 16x2 com interface I2C
- Dois potenciômetros (10k ohm)
- Cabos Jumper
- Breadboard

## Software e Bibliotecas

- Arduino IDE ou PlatformIO
- Bibliotecas:
  - `Wire.h` para comunicação I2C
  - `LiquidCrystal_I2C.h` para o controle do display LCD
  - `EspMQTTClient.h` para comunicação MQTT

## Configuração e Montagem

1. **ESP32 com Potenciômetros:**

   - Conecte cada potenciômetro ao ESP32 (GPIO 34 para pH e GPIO 35 para turbidez).
   - Ligue os terminais de alimentação dos potenciômetros ao VCC e GND do ESP32.

2. **Display LCD:**
   - Conecte SDA e SCL do LCD aos pinos GPIO 21 e GPIO 22 do ESP32, respectivamente.
   - Ligue VCC e GND do LCD ao VCC e GND do ESP32.

## Uso

Após montar o hardware conforme as instruções:

1. Carregue o código fornecido ao ESP32.
2. Ajuste os potenciômetros para simular diferentes leituras de pH e turbidez.
3. Observe as leituras no display LCD e monitore a transmissão dos dados via MQTT.

## Contribuindo

Contribuições para o projeto são bem-vindas! Se você tem sugestões para melhorar o sistema, por favor, faça um fork do repositório e crie um pull request, ou abra um issue com as tags adequadas.

## Licença

Este projeto é distribuído sob a licença MIT.

## Contato

- Álvaro Claver - [email](mailto:10368757@mackenzista.br)
- Marcello Conti - [email](mailto:10388422@mackenzista.br)
- Murilo Martins - [email](mailto:10402410@mackenzie.br)
- Wallace Santana - [email](mailto:1165744@mackenzie.br)
