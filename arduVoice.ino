#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

#define RELAY_LIGHT_PIN 19
#define RELAY_FAN_PIN 18

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(115200);
  delay(1500); 

  // Inicializar los relés
  pinMode(RELAY_LIGHT_PIN, OUTPUT);
  pinMode(RELAY_FAN_PIN, OUTPUT);
  
  // Configurar los relés en estado apagado
  digitalWrite(RELAY_LIGHT_PIN, HIGH);
  digitalWrite(RELAY_FAN_PIN, HIGH);

  // Inicializar el sensor BMP180
  if (!bmp.begin()) {
    Serial.println("Error al inicializar el sensor BMP180");
    while (1);
  }

  // Inicializar las propiedades de la thing
  initProperties();

  // Conectar al Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Configurar la función de sincronización
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  // Mantener la conexión con Arduino Cloud
  ArduinoCloud.update();

  // Leer la temperatura del sensor BMP180
  temperature = bmp.readTemperature();

  // Publicar la temperatura en Arduino Cloud
  ArduinoCloud.update();
}

// Funciones de sincronización para las variables de Arduino Cloud
void onLightChange() {
  digitalWrite(RELAY_LIGHT_PIN, light ? LOW : HIGH);
}

void onFanChange() {
  digitalWrite(RELAY_FAN_PIN, fan ? LOW : HIGH);
}

// Función de sincronización para la variable de temperatura
void onTemperatureChange() {
  // No se requiere ninguna acción específica en este ejemplo cuando la temperatura cambia
}
