/**
 * @file RemoteControl.hpp
 * @brief Classe para controle remoto de robô via Bluetooth utilizando ESP32 e dois motores.
 *
 * Esta classe permite o controle do robô por meio de comandos recebidos via Bluetooth Serial,
 * utilizando um app como o "Arduino Bluetooth Control". Os comandos são interpretados para
 * movimentar dois motores (MotorA e MotorB), permitindo ações como mover para frente, trás,
 * virar para esquerda, direita e executar comandos personalizados como "plantar sementes".
 *
 * Bibliotecas utilizadas:
 * - Arduino.h: biblioteca base do Arduino.
 * - control_motor.hpp: controle dos motores.
 * - BluetoothSerial.h: comunicação Bluetooth via SPP com ESP32.
 *
 * Métodos principais:
 * - Begin(): inicializa o Bluetooth.
 * - RemoteUpdate(): escuta e interpreta comandos recebidos via Bluetooth.
 * - front(), back(), left(), right(): controlam o movimento do robô.
 * - send_seeds(): comando personalizado.
 *
 * @author Matheus
 * @date 2025
 */

#include <Arduino.h>
#include "control_motor.hpp"
#include <BluetoothSerial.h>
//#include <DabbleESP32.h>

#ifndef REMOTE_CONTROL
#define REMOTE_CONTROL



class RemoteControl{

private:

String msgBluetooth;
BluetoothSerial SerialBT;


Motor& MotorA;
Motor& MotorB;

public:

    /**
     * @brief Construtor da classe RemoteControl.
     * 
     * Inicializa as referências dos motores A e B.
     * 
     * @param _MotorA Referência ao motor do lado A (esquerdo ou direito).
     * @param _MotorB Referência ao motor do lado B (esquerdo ou direito).
     */
    RemoteControl(Motor& _MotorA, Motor& _MotorB);

    /**
     * @brief Inicializa o módulo Bluetooth.
     * 
     * Começa a comunicação serial Bluetooth com o nome "ESP32-Control".
     */
    void Begin();

    /**
     * @brief Atualiza o estado com comandos recebidos via Bluetooth (Dabble).
     * 
     * Método legado para integração com o app Dabble, se necessário.
     */
    void RemoteUpdateFromDabble();

    /**
     * @brief Atualiza o estado com comandos recebidos via Bluetooth Serial.
     * 
     * Lê comandos do Bluetooth e chama funções correspondentes.
     * Comandos esperados: 'F', 'B', 'L', 'R', 'S' etc.
     */
    void RemoteUpdate();

    /**
     * @brief Move o robô para frente.
     */
    void front();

    /**
     * @brief Move o robô para trás.
     */
    void back();

    /**
     * @brief Vira o robô para a esquerda.
     */
    void left();

    /**
     * @brief Vira o robô para a direita.
     */
    void right();
    
    /**
     * @brief Executa o comando de plantar sementes.
     * 
     * Pode ser mapeado para um servo ou atuador.
     */
    void send_seeds();

};

#endif //REMOTE_CONTROL
