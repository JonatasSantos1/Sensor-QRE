#include <Arduino.h>

// DEFINIÇÃO DOS PINOS - O Pin_D* é o sensor - O numero é o pino na ESP32 (GPIO)
#define PIN_D1 1
#define PIN_D2 2
#define PIN_D3 5
#define PIN_D4 6
#define PIN_D5 7
#define PIN_D6 8
#define PIN_D7 3
#define PIN_D8 9

#define NUM_SENSORES 8

// ARRAY DE PINOS DOS SENSORES
int pinos[NUM_SENSORES] = {
  PIN_D1, PIN_D2, PIN_D3, PIN_D4,
  PIN_D5, PIN_D6, PIN_D7, PIN_D8
};

// CONTROLE DE LEITURA
int ultimaLeitura[NUM_SENSORES];

// SETUP - CONFIGURAÇÃO INICIAL DO SISTEMA
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  for (int i = 0; i < NUM_SENSORES; i++) {
    ultimaLeitura[i] = 0;
  }

  Serial.println("Sistema iniciado ");
}

// LOOP 
void loop() {

  for (int i = 0; i < NUM_SENSORES; i++) {

    int leitura = analogRead(pinos[i]);

    int diferenca = abs(leitura - ultimaLeitura[i]);

    // DETECÇÃO DE SENSOR DESCONECTADO 
    bool desconectado = false;

    if (diferenca > 1000) {
      desconectado = true;
    }

    // SAÍDA 
    Serial.print("P_D");
    Serial.print(i + 1);
    Serial.print(": ");

    if (desconectado) {
      Serial.print("X");  // erro
    } else {
      Serial.print(leitura);
    }

    ultimaLeitura[i] = leitura;

    if (i < NUM_SENSORES - 1) {
      Serial.print(" | ");
    }
  }

  Serial.println();

  delay(10);
}