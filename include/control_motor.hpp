#include <Arduino.h>

#ifndef CONTROL_MOTOR_HPP
#define CONTROL_MOTOR_HPP

class Motor{

private:

    int in1,in2,pwmPin,pwmChannel;
    int velocidade;

public:

    Motor(int _in1, int _in2, int _pwmPin, int _pwmChannel);

    
    void begin(int freq = 10000, int resolution = 8);

    void setSpeed(int vel);
    void forward ();
    void backward ();
    void stop();

};

#endif //CONTROL_MOTOR_HPP
