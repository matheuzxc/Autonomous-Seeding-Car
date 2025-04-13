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

    RemoteControl(Motor& _MotorA, Motor& _MotorB);
    void RemoteUpdateFromDabble();
    void RemoteUpdate();
    void Begin();
    void front();
    void back();
    void left();
    void right();
    void send_seeds();

};

#endif //REMOTE_CONTROL
