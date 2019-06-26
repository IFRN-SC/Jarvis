#ifndef SENSORESREFLETANCIA_H
#define SENSORESREFLETANCIA_H

#include <robo_hardware2.h>
#include <Servo.h>
#include <Wire.h>

#include "Motores.h"
#include "Calibragem.h"

class SensoresRefletancia{
  public:
    SensoresRefletancia();
    void start();
    boolean bbbb();
    boolean bbbp();
    boolean pbbb();
    boolean bbpp();
    boolean ppbb();
    boolean bppp();
    boolean pppb();
    boolean bbpb();
    boolean bpbb(); 
    boolean bppb();
    boolean pppp();

    boolean sensorMaisEsq(char);
    boolean sensorEsq(char);
    boolean sensorDir(char);
    boolean sensorMaisDir(char);

    void ondeEstouAlinhado();
    void comoEstaoMeusSensores();

    boolean isOnRedutor();

    void printSensoresDeRefletancia();
    
  private:
    Motores motores;
    Calibragem calibragem;
    calibracao_dados val;
    void pegarDadosEEPROM();

    float cinzaMaisEsq;
    float cinzaEsq;
    float cinzaDir;
    float cinzaMaisDir;

    float valorSensorMaisEsq;
    float valorSensorEsq;
    float valorSensorDir;
    float valorSensorMaisDir;

    float corteRedutorMaisEsq = 100;
    float corteRedutorEsq = 100;
    float corteRedutorDir = 100;
    float corteRedutorMaisDir = 100;
};

#endif
