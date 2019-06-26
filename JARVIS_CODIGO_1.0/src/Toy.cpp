#include "Toy.h"

#define DELAY_DESLIGA_LIGA_LED 200

Toy::Toy() {
  //
}

void Toy::ligarLed(int numeroLed){
  if(numeroLed == 1){
    robo.ligarLed(1);
  } else if(numeroLed == 2){
    robo.ligarLed(2);
  } else if(numeroLed == 3){
    robo.ligarLed(3);
  }
}

void Toy::desligarLed(int numeroLed){
  if(numeroLed == 1){
    robo.desligarLed(1);
  } else if(numeroLed == 2){
    robo.desligarLed(2);
  } else if(numeroLed == 3){
    robo.desligarLed(3);
  }
}

void Toy::desligaLigaLed(int numeroLed){
  switch(numeroLed){
    case 1:
      robo.desligarLed(1);
      delay(DELAY_DESLIGA_LIGA_LED);
      robo.ligarLed(1);
      break;
    case 2:
      robo.desligarLed(2);
      delay(DELAY_DESLIGA_LIGA_LED);
      robo.ligarLed(2);
      break;
    case 3:
      robo.desligarLed(3);
      delay(DELAY_DESLIGA_LIGA_LED);
      robo.ligarLed(3);
      break;
  }
}

void Toy::ligarApenasLed(int numeroLed) {
  if(numeroLed == 1){
    desligarLeds();
    robo.ligarLed(1);
  } else if(numeroLed == 2) {
    desligarLeds();
    robo.ligarLed(2);
  } else if(numeroLed == 3){
    desligarLeds();
    robo.ligarLed(3);
  }
}

void Toy::ligarLeds() {
  robo.ligarLed(1);
  robo.ligarLed(2);
  robo.ligarLed(3);
}

void Toy::desligarLeds() {
  robo.desligarLed(1);
  robo.desligarLed(2);
  robo.desligarLed(3);
}

void Toy::ledsEscada(int numeroDeRepeticoes, int tempo) {
  int cont = 0;

  while (cont != numeroDeRepeticoes) {
    desligarLeds();
    delay(tempo);

    robo.ligarLed(1);
    delay(tempo);
    robo.ligarLed(2);
    delay(tempo);
    robo.ligarLed(3);
    delay(tempo);
    cont++;
  }
}

void Toy::ledsAlerta(int numeroDeRepeticoes) {
  int cont = 0;
  boolean primeiroVez = true;

  while (cont != numeroDeRepeticoes) {
    ligarLeds();
    delay(150);
    desligarLeds();
    delay(150);
    cont++;
  }
}

void Toy::ledAlerta(int numeroLed, int numeroDeRepeticoes, int tempo) {
  int cont = 0;

  switch(numeroLed) {
    case 1:
      while (cont != numeroDeRepeticoes) {
        robo.desligarLed(1);
        delay(tempo);
        robo.ligarLed(1);
        delay(tempo);
        cont++;
      }
    case 2:
      while (cont != numeroDeRepeticoes) {
        robo.desligarLed(2);
        delay(tempo);
        robo.ligarLed(2);
        delay(tempo);
        cont++;
      }
    case 3:
      while (cont != numeroDeRepeticoes) {
        robo.desligarLed(3);
        delay(tempo);
        robo.ligarLed(3);
        delay(tempo);
        cont++;
      }
  }
}
