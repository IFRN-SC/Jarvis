#include "SensoresDistancia.h"

#define DISTANCIA_OBSTACULO 14.0
#define DELAY_VERIFICACAO_OBSTACULO 1000

SensoresDistancia::SensoresDistancia(){
  //
}

boolean SensoresDistancia::verificarObstaculo(){
  boolean resposta = false;
  if(robo.lerSensorSonarFrontal() <= DISTANCIA_OBSTACULO){
    motores.parar();
    delay(DELAY_VERIFICACAO_OBSTACULO);

    if(robo.lerSensorSonarFrontal() <= DISTANCIA_OBSTACULO){
      resposta = true;
    }
  }
  return resposta;
}

void SensoresDistancia::printSensoresDeDistancia(){
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


