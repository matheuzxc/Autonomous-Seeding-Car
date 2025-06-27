#include <Arduino.h>
#include "control_motor.hpp"
#include "bussola.hpp"
#include "navigator.hpp"
#include "navigator.hpp"

const int stop_threshold = 10;
const unsigned long intervaloGiro = 100;         // quanto tempo gira
const unsigned long tempoEsperaLeitura = 800;    // tempo parado antes de ler

unsigned long tempoAndarInicio = 0;
bool andando = false;
const unsigned long tempoPara1Metro = 3000; // exemplo: 3 segundos pra 1 metro (calibre!)

unsigned long tempoInicio = 0;

float Navigator::deg2rad(float deg) {
    return deg * PI / 180.0;
}

float Navigator::distance_meters(float lat1, float lon1, float lat2, float lon2) {
    const float R = 6371000.0;  

    float dLat = deg2rad(lat2 - lat1);
    float dLon = deg2rad(lon2 - lon1);

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
              sin(dLon / 2) * sin(dLon / 2);

    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;  
}

Navigator::Navigator(Motor& mA, Motor& mB, Bussola& b):
    motorA(mA),
    motorB(mB),
    bussola(b)
    {}

void Navigator::begin(){
    motorA.begin();
    motorB.begin();
    bussola.begin(21, 22);
}

float Navigator::update(){
    float azimute = bussola.lerAzimuteFiltrado();
    return azimute;
}

float Navigator::calcularErroAzimute(float azimuteAtual) {
    float erro = azimuteAtual;
    if (erro > 180.0) erro -= 360.0;
    return erro;
}

void Navigator::stop() {
    motorA.stop();
    motorB.stop();
}

void Navigator::moveTonorth(float azimuteAtual) {
    switch (estado) {
        case PARADO: {
            float azimute = azimuteAtual;
            float erro = calcularErroAzimute(azimute);

            if (abs(erro) <= stop_threshold) {
                stop();  // Alinhado!
                estado = ALINHADO_NORTH;
            } else {
                motorA.forward(180);
                motorB.forward(180);
                tempoInicio = millis();
                estado = GIRANDO_HORARIO;
            }
            break;
        }

        case GIRANDO_HORARIO:
            if (millis() - tempoInicio >= intervaloGiro) {
                stop();  // Parar fisicamente o motor após o bloco
                tempoInicio = millis();  // Marca início da pausa
                estado = ESPERANDO_LEITURA;
            }
            break;

        case ESPERANDO_LEITURA:
            if (millis() - tempoInicio >= tempoEsperaLeitura) {
                estado = PARADO;  // Volta para medir o azimute
            }
            break;
    }
}

void Navigator::moveTotarget(float anguloDestino, float azimuteAtual) {
 float erro = fmod((anguloDestino - azimuteAtual + 360.0), 360.0);  // resultado sempre entre 0 e 360

    switch (estado) {
        case ALINHADO_NORTH:
            if (abs(erro) <= stop_threshold) {
                
                stop();
                estado = ALINHADO;      
            } else {
                motorA.forward(180);
                motorB.forward(180);
                tempoInicio = millis();
                estado = GIRANDO_HORARIO;
            }
            break;

        case GIRANDO_HORARIO:
            if (millis() - tempoInicio >= intervaloGiro) {
                stop();
                tempoInicio = millis();
                estado = ESPERANDO_LEITURA;
            }
            break;

        case ESPERANDO_LEITURA:
            if (millis() - tempoInicio >= tempoEsperaLeitura) {
                estado = ALINHADO_NORTH;
            }
            break;

        case ALINHADO:
            break;
    }
}

bool Navigator::moveTodestin() {
    if (!andando) {
      motorA.forward(250);
      motorB.backward(250);
      tempoAndarInicio = millis();
      andando = true;
      return true;
    } else {
      if (millis() - tempoAndarInicio >= tempoPara1Metro) {
        motorA.stop();
        motorB.stop();
        andando = false;
        return false;
      }
    }

    return true;
}

float Navigator::calculeAng(float lat1, float lon1, float lat2, float lon2) {
    float dLon = deg2rad(lon2 - lon1);
    float lat1Rad = deg2rad(lat1);
    float lat2Rad = deg2rad(lat2);

    float y = sin(dLon) * cos(lat2Rad);
    float x = cos(lat1Rad) * sin(lat2Rad) - sin(lat1Rad) * cos(lat2Rad) * cos(dLon);

    float angulo = atan2(y, x) * 180.0 / PI;
    if (angulo < 0) angulo += 360.0;

    return angulo;
}

float Navigator::calculeAng(float lat1, float lon1, float lat2, float lon2) {
    float dLon = deg2rad(lon2 - lon1);
    float lat1Rad = deg2rad(lat1);
    float lat2Rad = deg2rad(lat2);

    float y = sin(dLon) * cos(lat2Rad);
    float x = cos(lat1Rad) * sin(lat2Rad) -
              sin(lat1Rad) * cos(lat2Rad) * cos(dLon);

    float angulo = atan2(y, x) * 180.0 / PI;

    if (angulo < 0) angulo += 360.0;
    return angulo;  // Azimute em graus
}

Navigator::EstadoNavegacao Navigator::getEstado() const {
    return estado;
}