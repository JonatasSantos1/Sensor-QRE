#include <Arduino.h>

// DEFINIÇÃO DOS PINOS
#define PIN_D1 1
#define PIN_D2 2
#define PIN_D3 5
#define PIN_D4 6
#define PIN_D5 7
#define PIN_D6 8
#define PIN_D7 3
#define PIN_D8 9

#define NUM_SENSORES 8
#define NUM_AMOSTRAS 500 // Quantidade de leituras para estatística

const int pinos[NUM_SENSORES] = {PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, PIN_D8};

void setup() {
    Serial.begin(115200);
    
    analogReadResolution(12); // 0 a 4095
    
    Serial.println("\n--- ANALISADOR DE RUÍDO (ESTATÍSTICA) ---");
    Serial.println("Mantenha o robô estático sobre a superfície de teste.");
    delay(3000);
}

void loop() {
    float medias[NUM_SENSORES] = {0};
    float variancias[NUM_SENSORES] = {0};
    int leituras[NUM_SENSORES][NUM_AMOSTRAS];

    // 1. Coleta de dados
    for (int a = 0; a < NUM_AMOSTRAS; a++) {
        for (int s = 0; s < NUM_SENSORES; s++) {
            leituras[s][a] = analogReadMilliVolts(pinos[s]);
            medias[s] += leituras[s][a];
        }
        delay(1); // Pequeno intervalo para estabilidade
    }

    // 2. Cálculo das Médias
    for (int s = 0; s < NUM_SENSORES; s++) {
        medias[s] /= NUM_AMOSTRAS;
    }

    // 3. Cálculo da Variância e Desvio Padrão
    // Variância = Soma((leitura - media)^2) / N
    for (int s = 0; s < NUM_SENSORES; s++) {
        float somaDiferencasQuadradas = 0;
        for (int a = 0; a < NUM_AMOSTRAS; a++) {
            somaDiferencasQuadradas += pow(leituras[s][a] - medias[s], 2);
        }
        variancias[s] = somaDiferencasQuadradas / NUM_AMOSTRAS;
    }

    // 4. Exibição dos resultados formatada
    Serial.println("\nID | Média(mV) | Variância(R) | Desvio Padrão(σ)");
    Serial.println("----------------------------------------------");
    for (int s = 0; s < NUM_SENSORES; s++) {
        Serial.printf("D%d | %8.2f | %12.4f | %12.4f\n", 
                      s + 1, 
                      medias[s], 
                      variancias[s], 
                      sqrt(variancias[s]));
    }

    Serial.println("\n----------------------------------------------");
    Serial.println("Reiniciando leitura em 10 segundos...");
    delay(10000);
}
