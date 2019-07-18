#include "OutrosSensores.h"

#define DISTANCIA_OBSTACULO 14.0
#define DELAY_VERIFICACAO_OBSTACULO 1000

void contagem();

OutrosSensores::OutrosSensores(){
  //
}

void OutrosSensores::beginTimer(){
  if(beginTimerJaAconteceu == false){ //Faz com que aconteça só uma vez; 
    beginTimerJaAconteceu = true;
    Timer3.initialize(1000000); //A cada um segundo ligar ou desligar o led 1
    Timer3.attachInterrupt(contagem);
  } 
}

int contador = 0;

void contagem(){
  contador++;
  Serial.println(contador);
}


void OutrosSensores::startTimer(){
  Timer3.start();
}

void OutrosSensores::stopTimer(){
  Timer3.stop();
  contador = 0;
}

boolean OutrosSensores::verificarObstaculo(){
  boolean resposta = false;
  if(robo.lerSensorSonarFrontal() <= DISTANCIA_OBSTACULO){
    delay(DELAY_VERIFICACAO_OBSTACULO);

    if(robo.lerSensorSonarFrontal() <= DISTANCIA_OBSTACULO){
      resposta = true;
    }
  }
  return resposta;
}

void OutrosSensores::printSensoresDeDistancia(){
  valorSensorLateralDir = robo.lerSensorSonarDir();
  valorSensorLateralEsq = robo.lerSensorSonarEsq();
  valorSensorFrontal = robo.lerSensorSonarFrontal();

  Serial.print(F("Valor do sensor frontal: "));
  Serial.print(valorSensorFrontal);
  Serial.print(F("  Esquerdo: "));
  Serial.print(valorSensorLateralEsq);
  Serial.print(F("  Direito: "));
  Serial.println(valorSensorLateralDir);
}


