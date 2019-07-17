#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <robo_hardware2.h>
#include <Servo.h>
#include "Toy.h"
#include "Calibragem.h"
#include "SensoresRefletancia.h"
#include "SensoresCor.h"
#include "SensoresDistancia.h"
#include "Motores.h"

class Estrategia{
  public:
    Estrategia();
    int ultimoMovimentoRegistrado();
    void executar();
    void seguirLinhaRampa();
    
  private:
    Calibragem calibragem;
    Toy toy;
    SensoresRefletancia refletancia;
    SensoresCor cor;
    SensoresDistancia distancia;
    Motores motores;
    
    void acaoBPBB(); //Em Construção 2
    void acaoBBPB(); //Em Construção 2
    void acaoPPBB(); //Em Construção 5
    //void acaoBBPP();
    //void acaoPPPB();
    //void acaoBPPP();
    //void acaoBPPB();
    void acaoPPPP(); //Em Construção 5

    void alinhamentoBPBB();
    void alinharComPPBB(); //Em Construção
    void alinharComPPBBAlternativo();
    //void alinharComBBPP();
    //void alinharComPPPB();
    //void alinharComBPPP();
    //void alinharComBPPB();
    void alinharComPPPP(); //Em Construção

    boolean acaoVerde();

    void enrolarEsquinaParaEsq(boolean);
    void enrolarEsquinaParaDir(boolean);

    boolean frente;
    boolean direita;
    boolean esquerda;
    
    boolean dadosCapturados;
    void start();
    void seguirLinha();
    void desviarObstaculo();

    void setFrente();
    void setEsquerda();
    void setDireita();

    void frearUltimoMovimento();

    void voltarAtePPPP();

};

#endif
