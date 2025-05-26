#include "remote_control.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

static const char* TAG = "REMOTE CONTROL";

// Construtor
RemoteControl::RemoteControl(Motor& _MotorA, Motor& _MotorB)
    : MotorA(_MotorA), MotorB(_MotorB) {}

// Variável para armazenar o comando atual
String comandoAtual = "S";

void RemoteControl::RemoteUpdate() {
    if (SerialBT.available()) {
        String comando = SerialBT.readStringUntil('\n');
        comando.trim();

        if (comando.length() == 0 || comando[0] == '\0' || comando == "\r") return;

        if (comando == "F" || comando == "B" || comando == "L" || comando == "R" || comando == "S") {
            comandoAtual = comando;
        } else {
            Serial.println("Mensagem não reconhecida: " + comando);
        }
    }

    // Executa continuamente o último comando válido
    if (comandoAtual == "F") {
        front();
    } else if (comandoAtual == "B") {
        back();
    } else if (comandoAtual == "L") {
        left();
    } else if (comandoAtual == "R") {
        right();
    } else if (comandoAtual == "S") {
        stop();
    }

    delay(50); // Pequeno atraso para evitar sobrecarga
}

void RemoteControl::Begin() {
    bool sucesso = SerialBT.begin("Autonomous Car Remote");
    if (sucesso) {
        Serial.println("Bluetooth iniciado com sucesso, conecte-se.");
    } else {
        Serial.println("Falha ao iniciar o Bluetooth!");
    }
}

void RemoteControl::front() {
    MotorA.forward();
    MotorB.forward();
    Serial.println("Ir para frente.");
}

void RemoteControl::back() {
    MotorA.backward();
    MotorB.backward();
    Serial.println("Ir para trás.");
}

void RemoteControl::left() {
    MotorA.backward();
    MotorB.forward();
    Serial.println("Ir para esquerda.");
}

void RemoteControl::right() {
    MotorA.forward();
    MotorB.backward();
    Serial.println("Ir para direita.");
}

void RemoteControl::stop() {
    MotorA.stop();
    MotorB.stop();  // Adicionei stop também ao MotorB, caso não estivesse incluído
    Serial.println("Parar.");
}
