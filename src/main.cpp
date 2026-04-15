#include <Arduino.h>

#define NUM_SENSORES 8

int pinos[NUM_SENSORES] = {1, 2, 4, 5, 6, 7, 8, 9};

int ultimaLeitura[NUM_SENSORES];

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  for (int i = 0; i < NUM_SENSORES; i++) {
    ultimaLeitura[i] = 0;
  }
}

void loop() {

  for (int i = 0; i < NUM_SENSORES; i++) {

    int leitura = analogRead(pinos[i]);

    int diferenca = abs(leitura - ultimaLeitura[i]);

    // ===== DETECÇÃO DE SENSOR DESCONECTADO =====
    bool desconectado = false;

    if (diferenca > 1000) { // limiar ajustável
      desconectado = true;
    }

    // ===== SAÍDA =====
    if (desconectado) {
      Serial.print("X");  // marca erro
    } else {
      Serial.print(leitura);
    }

    ultimaLeitura[i] = leitura;

    if (i < NUM_SENSORES - 1) {
      Serial.print(",");
    }
  }

  Serial.println();

  delay(10);
}