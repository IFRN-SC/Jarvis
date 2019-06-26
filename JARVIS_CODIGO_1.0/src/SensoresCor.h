#ifndef SENSORESCOR_H
#define SENSORESCOR_H

#include <robo_hardware2.h>
#include <Wire.h>

class SensoresCor{
  public:
    SensoresCor();
    void start();

    boolean verificarVerdeEsq();
    boolean verificarVerdeDir();

    void comoEstaoMeusSensores();

    void testarVerde();
    void printSensoresDeCorRGB();
    void printSensoresDeCorHSV(); 
  
  private:
    calibracao_dados val;
    void pegarDadosEEPROM();
    void calcularDivisores();

    HSV divisorPretoVerdeEsq;
    HSV divisorBrancoVerdeEsq;
    HSV divisorPretoVerdeDir;
    HSV divisorBrancoVerdeDir;

    RGB valorSensorCorRGBEsq;
    RGB valorSensorCorRGBDir;
    
    HSV valorSensorCorHSVEsq;
    HSV valorSensorCorHSVDir;

    HSV mediaBrancoCorEsq;
    HSV mediaBrancoCorDir;
    HSV mediaPretoCorEsq;
    HSV mediaPretoCorDir;
    HSV mediaVerdeCorEsq;
    HSV mediaVerdeCorDir;
    
};

#endif


