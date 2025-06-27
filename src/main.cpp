#include <Arduino.h>
#include "control_motor.hpp"
#include "bussola.hpp"
#include "navigator.hpp"

float azimuteAtual = 0;

// Motores: pinos do ESP32 (ajuste conforme seu hardware)
Motor motorEsquerda(14, 27, 0, 1);
Motor motorDireita(25, 26, 2, 3);

// Bússola calibrada
Bussola bussola(
    -131.00, -79.50,
    0.0019, 0.0020,
    -33.5, 0.1
);

Navigator nav(motorEsquerda, motorDireita, bussola);

// Variáveis simples de controle
bool alinhouZero = false;
bool alinhouQuarenta = false;
bool terminouMovimento = false;

void setup() {
    Serial.begin(115200);
    nav.begin();

    delay(2000);  // Espera inicial para estabilização da bússola
    Serial.println("Aquecendo leituras da bússola...");

    for (int i = 0; i < 10; i++) {
        float leitura = bussola.lerAzimuteFiltrado();
        Serial.print("Leitura "); Serial.print(i + 1); Serial.print(": ");
        Serial.println(leitura);
        delay(300);  // Pequeno intervalo entre leituras
    }

    Serial.println("Iniciando alinhamento...");
}


void loop() {

    azimuteAtual = bussola.lerAzimuteFiltrado();

    if (!alinhouZero) {
        Serial.println("Entrou north: ");
        nav.moveTonorth(azimuteAtual);
        if (nav.getEstado() == Navigator::ALINHADO_NORTH) {
            alinhouZero = true;
            Serial.println("✔️ Alinhado com 0°");
            delay(4000);
        }
        return;
    }

    if (!alinhouQuarenta) {
        Serial.println("entrou_target: ");
        nav.moveTotarget(40, azimuteAtual);
        if (nav.getEstado() == Navigator::ALINHADO) {
            alinhouQuarenta = true;
            Serial.println("✔️ Alinhado com 40°");
            delay(4000);
        }
        return;
    }

    if (!terminouMovimento) {
        if (!nav.moveTodestin()) {
            Serial.println("✔️ Movimento finalizado (1 metro)");
            terminouMovimento = true;
        }
        return;
    }

    // Final
    nav.stop();
}
