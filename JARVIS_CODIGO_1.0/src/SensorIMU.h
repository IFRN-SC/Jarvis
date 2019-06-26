/*
 * Classe para a Utilização improvisada do IMU (Funções ainda em Testes)
 * By: DuduCMT
 * -------------------------------------------
 * 
 * Essas funções não funcionarão caso você esteja usando os sensores de Cor com Wire no seu robô 
 * e não foram testadas em uma estrategia completa pela má estabilidade do modulo IMU preso ao Shilde 
 */

#ifndef SENSORIMU_H
#define SENSORIMU_H

#include <robo_hardware2.h>
#include <Wire.h>

class SensorIMU{
  public:
    SensorIMU();
    void start();
    //Caso Você use as funsões dessa classe no seu Robô, a função start() deve ser chamada no seu Setup()

    //Funções de Captura dos Valores
    double getValorAcX(); //Valor 'X' do Acelerômetro
    double getValorAcY(); //Valor 'Y' do Acelerômetro
    double getValorAcZ(); //Valor 'Z' do Acelerômetro
    double getValorGyX(); //Valor 'X' do Giroscôpio
    double getValorGyY(); //Valor 'Y' do Giroscôpio
    double getValorGyZ(); //Valor 'Z' do Giroscôpio

    //Funções de Impressão de Valores
    void printImuA(); //Imprimir Apenas os Valores do Acelerômetro
    void printImuG(); //Imprimir Apenas os Valores do Giroscôpio
    void printImuTudo(); //Imprimir os Valores do Acelerômetro e Giroscôpio

  private:
    const int MPU = 0x68; //Constante para Configuração
    int acX,acY,acZ,gyX,gyY,gyZ; //Variaveis para Retorno

    void setIMU();
    void solicitarIMU();
};

#endif


