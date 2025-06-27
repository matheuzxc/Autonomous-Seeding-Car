#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include <Arduino.h>
#include "control_motor.hpp"
#include "bussola.hpp"

class Navigator {
private:

    Motor& motorA;
    Motor& motorB;
    Bussola& bussola;



    float erroAngular = 0.0;
    unsigned long tempoInicioGiro = 0;
    const unsigned long duracaoGiro = 40; // tempo fixo de giro
    const float stop_threshold = 10.0;


    float deg2rad(float deg);
    float distance_meters(float lat1, float lon1, float lat2, float lon2);
     

public:
    enum EstadoNavegacao { PARADO, GIRANDO_HORARIO, ESPERANDO_LEITURA, ALINHADO_NORTH, ALINHADO, ANDANDO};
    EstadoNavegacao estado = PARADO;

    Navigator(Motor& mA, Motor& mB, Bussola& b);
    void begin();
    float calcularErroAzimute (float azimuteAtual);
    void stop (); // Para os motores e retorna o azimute filtrado
    float update(); // Atualiza o azimute filtrado da bússola e retorna o valor
    void moveTonorth(float azimuteAtual); // Move o robô para o norte com base no azimute filtrado
    void moveTotarget(float angDestino, float azimuteAtual); // Move o robô para o alvo(destino)
    float calculeAng(float lat1, float lon1, float lat2, float lon2); // Compara o azimute atual com o destino e ajusta a direção
    bool moveTodestin(); // Move o robô em direção ao destino especificado
    EstadoNavegacao getEstado() const;
};

#endif // NAVIGATOR_HPP
