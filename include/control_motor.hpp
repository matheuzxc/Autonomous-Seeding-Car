#pragma once

#include <Arduino.h>

class Motor {
private:
    int pin1, pin2;
    int canal1, canal2;

public:
    Motor(int in1, int in2, int ch1, int ch2);
    void begin();
    void forward(int velocidade = 255);
    void backward(int velocidade = 255);
    void stop();
};
