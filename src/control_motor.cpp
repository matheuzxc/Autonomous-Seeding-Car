#include "control_motor.hpp"

Motor::Motor(int in1, int in2, int ch1, int ch2)
    : pin1(in1), pin2(in2), canal1(ch1), canal2(ch2) {}

void Motor::begin() {
    ledcSetup(canal1, 5000, 8); // freq = 5kHz, 8 bits (0–255)
    ledcSetup(canal2, 5000, 8);
    ledcAttachPin(pin1, canal1);
    ledcAttachPin(pin2, canal2);
}

void Motor::forward(int velocidade) {
    velocidade = constrain(velocidade, 0, 255);
    ledcWrite(canal1, velocidade);
    ledcWrite(canal2, 0);
}

void Motor::backward(int velocidade) {
    velocidade = constrain(velocidade, 0, 255);
    ledcWrite(canal1, 0);
    ledcWrite(canal2, velocidade);
}

void Motor::stop() {
    ledcWrite(canal1, 0);
    ledcWrite(canal2, 0);
}
