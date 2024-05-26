#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EspMQTTClient.h>
// Defina os pinos onde os potenciômetros estão conectados
const int pHpin = 34;   // GPIO34 para o potenciômetro de pH
const int turbPin = 35; // GPIO35 para o potenciômetro de turbidez


char SSIDName[] = "Wokwi-GUEST"; //nome da rede WiFi
char SSIDPass[] = ""; //senha da rede WiFI
// Inicializa o display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço I2C do display 16 colunas e 2 linhas


char BrokerURL[] = "test.mosquitto.org"; //URL do broker MQTT
char BrokerUserName[] = ""; //nome do usuario para autenticar no broker MQTT
char BrokerPassword[] = ""; //senha para autenticar no broker MQTT
char MQTTClientName[] = "MQTT"; //nome do cliente MQTT
int BrokerPort = 1883; //porta do broker MQTT


String TopicoPrefixo = "g3mack"; //prefixo do topico
String Topico_01 = TopicoPrefixo+"/pH1"; //nome do topico 01
String Topico_02 = TopicoPrefixo+"/Turbidez1"; //nome do topico 02
String Topico_03 = TopicoPrefixo+"/Qualidade1";


EspMQTTClient clienteMQTT(SSIDName, SSIDPass, BrokerURL, BrokerUserName, BrokerPassword, MQTTClientName, BrokerPort); //inicializa o cliente MQTT

void onConnectionEstablished() {
}
void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  lcd.init();                      // Inicializa o display LCD
  lcd.backlight();                 // Acende o backlight do display
}

void loop() {
  clienteMQTT.loop();
  int pHValue = analogRead(pHpin);
  float pH = pHValue * (14.0 / 4095.0);  // Calcula o valor de pH
  String qualidade ="";

  int turbValueRaw = analogRead(turbPin);
  float turbidity = (turbValueRaw * (35.0 / 4095.0)); // Diretamente mapeado para 0-35
  turbidity = round(turbidity * 2.0) / 2.0;  // Arredonda para o múltiplo mais próximo de 0.5

  // Exibe os valores de pH e turbidez no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(pH, 2);
  lcd.print("Trb:");
  lcd.print(turbidity, 1);  // Exibe turbidez com uma casa decimal

  // Imprime valores no console serial
  Serial.print("pH: ");
  Serial.print(pH, 2);
  Serial.print(", Turbidez: ");
  Serial.print(turbidity, 1);
  Serial.println(" NTU");

  // Determina a qualidade da água
  lcd.setCursor(0, 1);
  if (pH >= 6.5 && pH <= 8.5 && turbidity <= 5) {
    lcd.print("Qualidade: Boa");
    Serial.println("Qualidade da água: Boa");
    qualidade = "Boa";
  } else {
    lcd.print("Qualidade: Ruim");
    qualidade = "Ruim";
    Serial.println("Qualidade da água: Ruim");
  }

if (clienteMQTT.isWifiConnected() == 1) {
    Serial.println("Conectado ao WiFi!");
  } else {
    Serial.println("Nao conectado ao WiFi!");
  }
if (clienteMQTT.isMqttConnected() == 1) {
    Serial.println("Conectado ao broker MQTT!");
    clienteMQTT.publish(Topico_02, String(turbidity, 2)); 
    clienteMQTT.publish(Topico_01, String(pH, 2)); 
    clienteMQTT.publish(Topico_03, qualidade); 
  } else {
    Serial.println("Nao conectado ao broker MQTT!");
  }

  delay(2000);  // Atualiza a cada 2 segundos
}
