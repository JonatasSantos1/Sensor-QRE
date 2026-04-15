#include <Arduino.h>

#define NUM_SENSORES 8

int pinos[NUM_SENSORES] = {1, 2, 4, 5, 6, 7, 8, 9};

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // 0 a 4095 (ESP32)
}

void loop() {

  for (int i = 0; i < NUM_SENSORES; i++) {
    int leitura = analogRead(pinos[i]);

    Serial.print(leitura);

    // separador para o Serial Plotter
    if (i < NUM_SENSORES - 1) {
      Serial.print(",");
    }
  }

  Serial.println(); // nova linha

  delay(10); // ~100Hz
}