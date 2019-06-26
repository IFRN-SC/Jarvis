#ifndef SENSORESDISTANCIA_H
#define SENSORESDISTANCIA_H

#include <robo_hardware2.h>
#include <Servo.h>
#include <Wire.h>

#include "Motores.h"
#include "SensoresRefletancia.h"
#include "SensoresDistancia.h"

class SensoresDistancia{
  public:
    SensoresDistancia();
    boolean verificarObstaculo();
    void printSensoresDeDistancia();

  private:
    Motores motores;
    SensoresRefletancia refletancia;

    float valorSensorFrontal;
    float valorSensorLateralEsq;
    float valorSensorLateralDir;
      
};

#endif


