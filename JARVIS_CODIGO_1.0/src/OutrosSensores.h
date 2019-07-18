#ifndef OUTROSSENSORES_H
#define OUTROSSENSORES_H

#include <robo_hardware2.h>
#include <TimerThree.h>
#include <Servo.h>
#include <Wire.h>

class OutrosSensores{
  public:
    OutrosSensores();

    boolean verificarObstaculo();
    
    void beginTimer();
    void startTimer();
    void stopTimer();
    void zerarContador();

    void printSensoresDeDistancia();

  private:
    boolean beginTimerJaAconteceu;

    float valorSensorFrontal;
    float valorSensorLateralEsq;
    float valorSensorLateralDir;
};

#endif
