#ifndef MOTORES_H
#define MOTORES_H

#include <robo_hardware2.h>
#include "Toy.h"

class Motores{
  public:
    Motores();

    //Movimentos Padrões
    void frente();
    void voltar();
    void parar();
    void frear();
    void girarEsq();
    void girarDir();
    void virarEsq();
    void virarDir();
    void voltarEsq();
    void voltarDir();
    
    //Movimentos Devagar
    void frenteDevagar();
    void voltarDevagar();
    void frearDevagar();
    void girarDevagarEsq();
    void girarDevagarDir();
    void virarDevagarEsq();
    void virarDevagarDir();
    void voltarDevagarEsq();
    void voltarDevagarDir();

    //Movimentos Diferenciados
    void giroDiferenteEsq();
    void giroDiferenteDir();

    //Movimentos de 90 Graus
    void girar90Esq();
    void girar90Dir();

    //Movimentos para o Redutor
    void acaoRedutor();


    //Movimento de Freios
    void frearGiroEsq();
    void frearGiroDir();
    void frearVirarEsq();
    void frearVirarDir();
    void frearVoltarEsq();
    void frearVoltarDir();
    void frarVoltar();

    //Movimentos Especificos
    void frenteCurva();
    void pararPor(int);
    void frearPor(int);
    void pararAteBotao1();
    
  private:
    Toy toy;
};

#endif

/*
COMANDOS PARA TESTES:
  motores.frente();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.voltar();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.girarEsq();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.girarDir();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.virarEsq();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.virarDir();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.voltarEsq();
  delay(1000);
  motores.parar();
  delay(1000);
  motores.voltarDir();
  delay(1000);
  motores.parar();
  delay(1000);
*/
