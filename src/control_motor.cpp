#include "control_motor.hpp"

Motor::Motor(int _in1, int _in2)
    : in1(_in1), in2(_in2), velocidade(255) {}

void Motor::begin() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    stop();  
}

void Motor::setSpeed(int vel) {
    velocidade = 255;  
}

void Motor::forward() {
    digitalWrite(in1, HIGH);   
    digitalWrite(in2, LOW);    
}

void Motor::backward() {
    digitalWrite(in1, LOW);    
    digitalWrite(in2, HIGH);   
}

void Motor::stop() {
    digitalWrite(in1, LOW);    
    digitalWrite(in2, LOW);    
}
