#include <Arduino.h>

#ifndef CONTROL_MOTOR_HPP
#define CONTROL_MOTOR_HPP

/**
 * @brief Classe que representa um motor controlado por ponte H.
 * 
 * Permite controle de direção (frente, ré) e velocidade constante.
 */
class Motor {

private:
    int in1, in2;
    int velocidade;

public:
    /**
     * @brief Construtor da classe Motor.
     * 
     * @param _in1 Pino de controle IN1.
     * @param _in2 Pino de controle IN2.
     */
    Motor(int _in1, int _in2);

    /**
     * @brief Inicializa os pinos de controle.
     */
    void begin();

    /**
     * @brief Define a velocidade do motor.
     * 
     * @param vel Valor de 0 a 255 para controle de velocidade PWM (não será usado, já que velocidade é constante).
     */
    void setSpeed(int vel);

    /**
     * @brief Faz o motor girar para frente.
     */
    void forward();

    /**
     * @brief Faz o motor girar para trás.
     */
    void backward();

    /**
     * @brief Para o motor.
     */
    void stop();
};

#endif //CONTROL_MOTOR_HPP
