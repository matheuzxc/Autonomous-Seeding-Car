#include <Arduino.h>

#ifndef CONTROL_MOTOR_HPP
#define CONTROL_MOTOR_HPP

/**
 * @brief Classe que representa um motor controlado por ponte H com PWM.
 * 
 * Permite controle de direção (frente, ré, esquerda, direita) e velocidade.
 */
class Motor{

private:

    int in1,in2,pwmPin,pwmChannel;
    int velocidade;

public:

    /**
     * @brief Construtor da classe Motor.
     * 
     * @param _in1 Pino de controle IN1.
     * @param _in2 Pino de controle IN2.
     * @param _pwmPin Pino de saída PWM.
     * @param _pwmChannel Canal PWM a ser usado.
     */
    Motor(int _in1, int _in2, int _pwmPin, int _pwmChannel);

    /**
     * @brief Inicializa os pinos e configura o canal PWM.
     * 
     * @param freq Frequência do PWM (padrão 10 kHz).
     * @param resolution Resolução do PWM (padrão 8 bits).
     */
    void begin(int freq = 10000, int resolution = 8);

    /**
     * @brief Define a velocidade do motor.
     * 
     * @param vel Valor de 0 a 255 para controle de velocidade PWM.
     */
    void setSpeed(int vel);
    
    /**
     * @brief Faz o motor girar para frente.
     */
    void forward ();

    /**
     * @brief Faz o motor girar para trás.
     */
    void backward ();

    /**
     * @brief Para o motor (velocidade 0).
     */
    void stop();

};

#endif //CONTROL_MOTOR_HPP
