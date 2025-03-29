#include "control_motor.hpp"

Motor::Motor(int _in1, int _in2, int _pwmPin, int _pwmChannel)
    : in1(_in1), in2(_in2), pwmPin(_pwmPin), pwmChannel(_pwmChannel), velocidade(0) {}

void Motor::begin(int freq, int resolution) {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    ledcSetup(pwmChannel, freq, resolution);
    ledcAttachPin(pwmPin, pwmChannel);
    stop();
}

void Motor::setSpeed(int vel) {
    velocidade = constrain(vel, 0, 255);
    if (velocidade == 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW); // Desliga o motor
    }
    ledcWrite(pwmChannel, velocidade);
}

void Motor::forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    if(velocidade == 0){
        setSpeed(255);
    }
    setSpeed(velocidade);
}

void Motor::backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    if(velocidade == 0){
        setSpeed(255);
    }
    setSpeed(velocidade);
    setSpeed(velocidade);
}

void Motor::stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    setSpeed(0);
}



