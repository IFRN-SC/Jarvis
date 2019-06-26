#include "SensoresRefletancia.h"

SensoresRefletancia::SensoresRefletancia(){
  pegarDadosEEPROM();
}

void SensoresRefletancia::start(){
  //
}

//Branco Branco Branco Branco (Andar para Frente)
boolean SensoresRefletancia::bbbb(){  
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('B') && sensorDir('B') && sensorMaisDir('B')){
    resposta = true;
  }else{
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Branco Preto Branco Branco (Direita)
boolean SensoresRefletancia::bpbb(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('P') && sensorDir('B') && sensorMaisDir('B')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Branco Branco Preto Branco (Esquerda)
boolean SensoresRefletancia::bbpb(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('B') && sensorDir('P') && sensorMaisDir('B')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Branco Preto Preto Branco (Continuar ação anterior)
boolean SensoresRefletancia::bppb(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('P') && sensorDir('P') && sensorMaisDir('B')){
    resposta = true;
  }else{
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Preto Branco Branco Branco
boolean SensoresRefletancia::pbbb(){
  boolean resposta;
  if(sensorMaisEsq('P') && sensorEsq('B') && sensorDir('B') && sensorMaisDir('B')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Branco Branco Branco Preto
boolean SensoresRefletancia::bbbp(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('B') && sensorDir('B') && sensorMaisDir('P')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;  
}

//Branco Branco Preto Preto
boolean SensoresRefletancia::bbpp(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('B') && sensorDir('P') && sensorMaisDir('P')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;   
}

//Preto Preto Branco Branco
boolean SensoresRefletancia::ppbb(){
  boolean resposta;
  if(sensorMaisEsq('P') && sensorEsq('P') && sensorDir('B') && sensorMaisDir('B')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta; 
}

//Branco Preto Preto Preto
boolean SensoresRefletancia::bppp(){
  boolean resposta;
  if(sensorMaisEsq('B') && sensorEsq('P') && sensorDir('P') && sensorMaisDir('P')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta; 
}

//Preto Preto Preto Branco
boolean SensoresRefletancia::pppb(){
  boolean resposta;
  if(sensorMaisEsq('P') && sensorEsq('P') && sensorDir('P') && sensorMaisDir('B')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta; 
}

//Preto Preto Preto Preto
boolean SensoresRefletancia::pppp(){
  boolean resposta;
  if(sensorMaisEsq('P') && sensorEsq('P') && sensorDir('P') && sensorMaisDir('P')){
    resposta = true;
  } else {
    if(isOnRedutor()){
      motores.acaoRedutor();
    }
    resposta = false;
  }
  return resposta;
}

//Verificador do Sensor Mais Esquerdo, 'P' para Preto e 'B' para Branco 
boolean SensoresRefletancia::sensorMaisEsq(char entrada){
  boolean resposta;
  switch(entrada){
    case 'P':
      if(robo.lerSensorLinhaMaisEsq() < cinzaMaisEsq){
        resposta = true;
      }else{
        resposta = false;
      }
      break;   
    case 'B':
      if((robo.lerSensorLinhaMaisEsq() > cinzaMaisEsq) && (robo.lerSensorLinhaMaisEsq() < corteRedutorMaisEsq)){
        resposta = true;
      }else{
        resposta = false;
      }
      break;  
  }
  return resposta;
}

//Verificador do Sensor Esquerdo, 'P' para Preto e 'B' para Branco 
boolean SensoresRefletancia::sensorEsq(char entrada){
  boolean resposta;
  switch(entrada){
    case 'P':
      if(robo.lerSensorLinhaEsq() < cinzaEsq){
        resposta = true;
      }else{
        resposta = false;
      }
      break;   
    case 'B':
      if((robo.lerSensorLinhaEsq() > cinzaEsq) && (robo.lerSensorLinhaEsq() < corteRedutorEsq)){
        resposta = true;
      }else{
        resposta = false;
      }
      break;  
  }
  return resposta;
}

//Verificador do Sensor Direito, 'P' para Preto e 'B' para Branco 
boolean SensoresRefletancia::sensorDir(char entrada){
  boolean resposta;
  switch(entrada){
    case 'P':
      if(robo.lerSensorLinhaDir() < cinzaDir){
        resposta = true;
      }else{
        resposta = false;
      }
      break;   
    case 'B':
      if((robo.lerSensorLinhaDir() > cinzaDir) && (robo.lerSensorLinhaDir() < corteRedutorDir)){
        resposta = true;
      }else{
        resposta = false;
      }
      break;  
  }
  return resposta;
}

//Verificador do Sensor Mais Direito, 'P' para Preto e 'B' para Branco 
boolean SensoresRefletancia::sensorMaisDir(char entrada){
  boolean resposta;
  switch(entrada){
    case 'P':
      if(robo.lerSensorLinhaMaisDir() < cinzaMaisDir){
        resposta = true;
      }else{
        resposta = false;
      }
      break;   
    case 'B':
      if((robo.lerSensorLinhaMaisDir() > cinzaMaisDir) && (robo.lerSensorLinhaMaisDir() < corteRedutorMaisDir)){
        resposta = true;
      }else{
        resposta = false;
      }
      break;  
  }
  return resposta;
}

void SensoresRefletancia::ondeEstouAlinhado(){
  if(pppp()){ //Estou em todos pretos

  }
}

void SensoresRefletancia::comoEstaoMeusSensores(){
  robo.acionarMotores(0,0);
  delay(500);

  if(sensorMaisEsq('P')){
    robo.desligarLed(1);
    delay(500);
    robo.ligarLed(1);
    delay(500);    
    robo.desligarLed(1);
  } else {
    robo.desligarLed(2);
    delay(500);
    robo.ligarLed(2);
    delay(500);  
    robo.desligarLed(2); 
  }

  if(sensorEsq('P')){
    robo.desligarLed(1);
    delay(500);
    robo.ligarLed(1);
    delay(500);    
    robo.desligarLed(1);
  } else {
    robo.desligarLed(2);
    delay(500);
    robo.ligarLed(2);
    delay(500);   
    robo.desligarLed(2);
  }

  if(sensorDir('P')){
    robo.desligarLed(1);
    delay(500);
    robo.ligarLed(1);
    delay(500);    
    robo.desligarLed(1);
  } else {
    robo.desligarLed(2);
    delay(500);
    robo.ligarLed(2);
    delay(500);   
    robo.desligarLed(2);
  }

  if(sensorMaisDir('P')){
    robo.desligarLed(1);
    delay(500);
    robo.ligarLed(1);
    delay(500);    
    robo.desligarLed(1);
  } else {
    robo.desligarLed(2);
    delay(500);
    robo.ligarLed(2);
    delay(500);   
    robo.desligarLed(2);
  }
  delay(500);
}

boolean SensoresRefletancia::isOnRedutor(){
  boolean resposta = false;
  if(robo.lerSensorLinhaEsq() > corteRedutorEsq){
    resposta = true;
  } else {
    resposta = false;
  }
  return resposta;
}

void SensoresRefletancia::printSensoresDeRefletancia(){
  valorSensorMaisEsq = robo.lerSensorLinhaMaisEsq();
  valorSensorEsq = robo.lerSensorLinhaEsq();
  valorSensorDir = robo.lerSensorLinhaDir();
  valorSensorMaisDir = robo.lerSensorLinhaMaisDir();
            
  Serial.print(F("Sensores refletancia: +esq; esq; dir; +dir "));
  Serial.print(valorSensorMaisEsq);
  Serial.print(F("; "));
  Serial.print(valorSensorEsq);
  Serial.print(F("; "));
  Serial.print(valorSensorDir);
  Serial.print(F("; "));
  Serial.println(valorSensorMaisDir);
}


void SensoresRefletancia::pegarDadosEEPROM(){
  robo.lerCalibracao(val);
  
  cinzaMaisEsq = val.refletanciaMaisEsq;
  cinzaEsq = val.refletanciaEsq;
  cinzaDir = val.refletanciaDir;
  cinzaMaisDir = val.refletanciaMaisDir;
}