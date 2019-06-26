#ifndef MENUINICIAR_H
#define MENUINICIAR_H

#include <Arduino.h>
#include <robo_hardware2.h>
#include "Toy.h"
#include "Calibragem.h"
#include "Estrategia.h"
#include "SensoresRefletancia.h"
#include "SensoresCor.h"
#include "SensoresDistancia.h"
#include "SensorIMU.h"

class MenuIniciar{
  public:
    Calibragem calibragem;
    MenuIniciar();
    
    void menuBotoes();
  
  private:
    void menuSerial();
    
    Toy toy;
    calibracao_dados val;
    SensoresRefletancia refletancia;
    SensoresCor cor;
    SensoresDistancia sonar;
    SensorIMU imu;
    Estrategia estrategia;
};

#endif
