
/**************************************************************
*   @brief: Omlet Chicken Coop Controller   
*
*   @Details: Chicken coop weather station that allows
*             remote monitoring of the chicken coop enviroment 
*             and control of motors and devices. 
*
*   @Author: Alex Hubbard | Electrical Engineer
*
*   @Date: 07-06-2025
***************************************************************/

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

const int lm35 = A0;

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

void setup() {
  Serial.begin(9600);
  pinMode(lm35, INPUT);
  waitUntil(Particle.connected);
  Serial.println("Omlet Weather Station Starting...");

  
}

void loop() {
  static unsigned long lastPublish = 0;
  const unsigned long publishInterval = 30000; // 30 seconds
  unsigned long now = millis();

  Particle.process(); // Maintain cloud connection

  if (now - lastPublish >= publishInterval) {
    float tempC = readTemperatureC(lm35);
    float tempF = (tempC * 1.8f) + 32.0f;

    Serial.printf("Temp: %.2f °C | %.2f °F\n", tempC, tempF);

    if (Particle.connected()) {
      char payload[64];
      snprintf(payload, sizeof(payload), "{\"temp_c\": %.2f, \"temp_f\": %.2f}", tempC, tempF);
      Particle.publish("Current Temperature", payload, PRIVATE);
    } else {
      Serial.println("Not connected to Particle Cloud.");
    }

    lastPublish = now;
  }
}

float readTemperatureC(int sensePin) {
  float voltage = analogRead(sensePin) * (3.3 / 4095.0); // Photon uses 3.3V ADC ref
  float temperatureC = voltage * 100.0; // LM35: 10mV per °C
  return temperatureC;
}

int foodLevelSense(int foodSense ) {

  int tube_a = D0;
  int tube_b = D1;
  int tube_c = D2;
  int tube_d = D3;

  pinMode(tube_a, tube_b, tube_c, tube_d, INPUT_PULLDOWN, INPUT_PULLDOWN, INPUT_PULLDOWN, INPUT_PULLDOWN);




}
