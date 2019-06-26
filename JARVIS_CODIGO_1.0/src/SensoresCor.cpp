#include "SensoresCor.h"

SensoresCor::SensoresCor(){
  robo.habilitaTCS34();
  pegarDadosEEPROM();
  calcularDivisores();
}

void SensoresCor::testarVerde(){
  if(verificarVerdeEsq()){
    robo.ligarLed(3);
    robo.desligarLed(2);
  } else {
    robo.desligarLed(3);
    robo.ligarLed(2);
  }
}

boolean SensoresCor::verificarVerdeEsq(){
  boolean resposta = false;
  valorSensorCorHSVEsq = robo.getHSVEsquerdo(); 

  //Para o .v: O Verde é maior que o Preto e menor que o Branco
  if(valorSensorCorHSVEsq.v < divisorPretoVerdeEsq.v && valorSensorCorHSVEsq.v < divisorBrancoVerdeEsq.v){
    //Para o .h: O Verde é menor que o Preto e Menor que o Branco
    if(valorSensorCorHSVEsq.h < divisorPretoVerdeEsq.h && valorSensorCorHSVEsq.h < divisorBrancoVerdeEsq.h){
      resposta = true; 
    }
  }else{
    resposta = false;
  }

  return resposta;
}

boolean SensoresCor::verificarVerdeDir(){
  boolean resposta = false;
  valorSensorCorHSVDir = robo.getHSVDireito(); 

  //Para o .v: O Verde é maior que o Preto e menor que o Branco
  if(valorSensorCorHSVDir.v < divisorPretoVerdeDir.v && valorSensorCorHSVDir.v < divisorBrancoVerdeDir.v){
    //Para o .h: O Verde é menor que o Preto e Menor que o Branco
    if(valorSensorCorHSVDir.h < divisorPretoVerdeDir.h && valorSensorCorHSVDir.h < divisorBrancoVerdeDir.h){
      resposta = true; 
    }
  }else{
    resposta = false;
  }

  return resposta;
}  

void SensoresCor::comoEstaoMeusSensores(){
  robo.acionarMotores(0,0);
  delay(500);

  if(verificarVerdeEsq()){
    robo.desligarLed(3);
    delay(500);
    robo.ligarLed(3);
    delay(500);    
    robo.desligarLed(3);
  } else {
    robo.desligarLed(2);
    delay(500);
    robo.ligarLed(2);
    delay(500);  
    robo.desligarLed(2); 
  }

  if(verificarVerdeDir()){
    robo.desligarLed(3);
    delay(500);
    robo.ligarLed(3);
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

void SensoresCor::printSensoresDeCorRGB(){  
    valorSensorCorRGBEsq = robo.getRGBEsquerdo();
    valorSensorCorRGBDir = robo.getRGBDireito(); 

    Serial.print(F("Cor Esquerdo: "));
    Serial.print(valorSensorCorRGBEsq.vermelho);
    Serial.print(F(", "));
    Serial.print(valorSensorCorRGBEsq.verde);
    Serial.print(F(", "));
    Serial.print(valorSensorCorRGBEsq.azul);
    Serial.print(F("   Cor Direito:  "));
    Serial.print(valorSensorCorRGBDir.vermelho);
    Serial.print(F(", "));
    Serial.print(valorSensorCorRGBDir.verde);
    Serial.print(F(", "));
    Serial.print(valorSensorCorRGBDir.azul);
    Serial.println();
}

void SensoresCor::printSensoresDeCorHSV(){
  valorSensorCorHSVEsq = robo.getHSVEsquerdo();
  valorSensorCorHSVDir = robo.getHSVDireito(); 

  Serial.print(F("Cor Esquerdo: "));
  Serial.print(valorSensorCorHSVEsq.h);
  Serial.print(F(", "));
  Serial.print(valorSensorCorHSVEsq.s);
  Serial.print(F(", "));
  Serial.print(valorSensorCorHSVEsq.v);
  Serial.print(F("   Cor Direito:  "));
  Serial.print(valorSensorCorHSVDir.h);
  Serial.print(F(", "));
  Serial.print(valorSensorCorHSVDir.s);
  Serial.print(F(", "));
  Serial.print(valorSensorCorHSVDir.v);
  Serial.println();  
}


void SensoresCor::pegarDadosEEPROM(){
  robo.lerCalibracao(val);

  mediaPretoCorEsq.h = val.pretoEsq.h;
  mediaPretoCorEsq.s = val.pretoEsq.s;
  mediaPretoCorEsq.v = val.pretoEsq.v;
  
  mediaPretoCorDir.h = val.pretoDir.h;
  mediaPretoCorDir.s = val.pretoDir.s;
  mediaPretoCorDir.v = val.pretoDir.v;
  
  mediaBrancoCorEsq.h = val.brancoEsq.h;
  mediaBrancoCorEsq.s = val.brancoEsq.s;
  mediaBrancoCorEsq.v = val.brancoEsq.v;
  
  mediaBrancoCorDir.h = val.brancoDir.h;
  mediaBrancoCorDir.s = val.brancoDir.s;
  mediaBrancoCorDir.v = val.brancoDir.v;
  
  mediaVerdeCorEsq.h = val.verdeEsq.h;
  mediaVerdeCorEsq.s = val.verdeEsq.s;
  mediaVerdeCorEsq.v = val.verdeEsq.v;
  
  mediaVerdeCorDir.h = val.verdeDir.h;
  mediaVerdeCorDir.s = val.verdeDir.s;
  mediaVerdeCorDir.v = val.verdeDir.v;
}

void SensoresCor::calcularDivisores(){
  divisorPretoVerdeEsq.h = (mediaPretoCorEsq.h + mediaVerdeCorEsq.h) / 2;
  divisorPretoVerdeEsq.s = (mediaPretoCorEsq.s + mediaVerdeCorEsq.s) / 2;
  divisorPretoVerdeEsq.v = (mediaPretoCorEsq.v + mediaVerdeCorEsq.v) / 2;
  
  divisorPretoVerdeDir.h = (mediaPretoCorDir.h + mediaVerdeCorDir.h) / 2;
  divisorPretoVerdeDir.s = (mediaPretoCorDir.s + mediaVerdeCorDir.s) / 2;
  divisorPretoVerdeDir.v = (mediaPretoCorDir.v + mediaVerdeCorDir.v) / 2;
  
  divisorBrancoVerdeEsq.h = (mediaBrancoCorEsq.h + mediaVerdeCorEsq.h) / 2;
  divisorBrancoVerdeEsq.s = (mediaBrancoCorEsq.s + mediaVerdeCorEsq.s) / 2;
  divisorBrancoVerdeEsq.v = (mediaBrancoCorEsq.v + mediaVerdeCorEsq.v) / 2;

  divisorBrancoVerdeDir.h = (mediaBrancoCorDir.h + mediaVerdeCorDir.h) / 2;
  divisorBrancoVerdeDir.s = (mediaBrancoCorDir.s + mediaVerdeCorDir.s) / 2;
  divisorBrancoVerdeDir.v = (mediaBrancoCorDir.v + mediaVerdeCorDir.v) / 2;
   
}

