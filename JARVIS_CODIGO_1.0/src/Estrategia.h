#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <robo_hardware2.h>
#include <Servo.h>
#include "Toy.h"
#include "Calibragem.h"
#include "SensoresRefletancia.h"
#include "SensoresCor.h"
#include "Motores.h"
#include "OutrosSensores.h"

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
    Motores motores;
    OutrosSensores outrosSensores;
    
    int numeroDeViradinhas;
    void corrigirViradinha();

    void acaoBPBB();
    void acaoBBPB();
    void acaoPPBB();
    void acaoBBPP(); 
    //void acaoBBPP();
    //void acaoPPPB();
    //void acaoBPPP();
    //void acaoBPPB();
    void acaoPPPP(boolean); //Em Construção 5

    //Métodos de Verificação do Verde
    boolean verificarVerdeParado();
    boolean vaiVerificaVerdeVolta();
    boolean miniVaiVerificaVerdeVolta();
    boolean avancarVerificarVerde(int);

    void alinhamentoBPBB();
    void alinhamentoBBPB();
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
