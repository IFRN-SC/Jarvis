#ifndef CALIBRAGEM_H
#define CALIBRAGEM_H

#include <robo_hardware2.h>
#include "Toy.h"

class Calibragem{
  public:
    Calibragem();
    boolean voltarMenu;

    void printDadosEEPROM();
    void iniciarCalibragem();
  private:
    Toy toy;
    calibracao_dados val;
  
    //Variaveis para a Calibração dos Sensores de Refletancia
    float mediaBrancoRefletanciaMaisEsq;
    float mediaBrancoRefletanciaEsq;
    float mediaBrancoRefletanciaDir;
    float mediaBrancoRefletanciaMaisDir;
    
    float mediaPretoRefletanciaMaisEsq;
    float mediaPretoRefletanciaEsq;
    float mediaPretoRefletanciaDir;
    float mediaPretoRefletanciaMaisDir;

    float cinzaMaisDir;
    float cinzaDir;
    float cinzaEsq;
    float cinzaMaisEsq;

    //Variaveis para calibração dos Sensores de Cor
    HSV capturadorDeCorAuxEsqHSV;
    HSV capturadorDeCorAuxDirHSV;
    
    RGB capturadorDeCorAuxRGB;

    HSV mediaBrancoCorEsq;
    HSV mediaBrancoCorDir;
    HSV mediaPretoCorEsq;
    HSV mediaPretoCorDir;
    HSV mediaVerdeCorEsqHSV;
    HSV mediaVerdeCorDirHSV;

    RGB mediaVerdeCorEsqRGBmaior;
    RGB mediaVerdeCorDirRGBmaior;
    RGB mediaVerdeCorEsqRGBmenor;
    RGB mediaVerdeCorDirRGBmenor; 

    //Métodos para calibração de Sensores
    void calibracaoPretoRefletancia();
    void calibracaoPretoCor();
    void calibracaoBrancoRefletanciaCor();
    void calibracaoVerdeEsq();
    void calibracaoVerdeDir();

    void calcularCinzaRefletancia();
    void guardarDadosEEPROM();
};

#endif
