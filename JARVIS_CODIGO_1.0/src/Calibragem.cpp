#include "Calibragem.h"
#define DELAY_INTERVALO_DE_CAPTURA 200

Calibragem::Calibragem (){
  //
}

void Calibragem::iniciarCalibragem(){
  Serial.println(F("\n-------------------"));
  Serial.println(F("Calibração Iniciada"));
  Serial.println(F("-------------------\n"));
  
  Serial.println(F("Parte 1: Coletar valores do Preto para os Sensores de Refletância"));
  Serial.println(F("Precione o Botão 1 para Começar!"));
  while(!robo.botao1Pressionado()){} //Espera Resposta do Botão 1
  toy.ligarApenasLed(1);
  calibracaoPretoRefletancia();
  
  Serial.println(F("\nParte 2: Coletar valores do Preto para os Sensores de Cor"));
  Serial.println(F("Pressione o Botão 1 para Continuar!"));
  while(!robo.botao1Pressionado()){} //Espera Resposta do Botão 1
  toy.desligaLigaLed(1);
  calibracaoPretoCor();
  
  Serial.println(F("\nParte 3: Coletar valores do Branco para os Sensores de Refletância e Cor"));
  Serial.println(F("Pressione o Botão 2 para Começar!"));
  while(!robo.botao2Pressionado()){} //Espera Resposta do Botão 2
  toy.ligarLed(2);
  calibracaoBrancoRefletanciaCor();

  Serial.println(F("\nParte 4: Coletar valores do Verde para o Sensor de Cor Esquerdo"));
  Serial.println(F("Pressione o Botão 3 para Começar!"));
  while(!robo.botao3Pressionado()){} //Espera Resposta do Botão 3
  toy.ligarLed(3);
  calibracaoVerdeEsq();

  Serial.println(F("\nParte 5: Coletar valores do Verde para o Sensor de Cor Direito"));
  Serial.println(F("Pressione o Botão 3 para Continuar!"));
  while(!robo.botao3Pressionado()){} //Espera Resposta do Botão 3
  toy.desligaLigaLed(3);
  calibracaoVerdeDir();

  Serial.println(F("\nRealizando Últimas Ações..."));
  delay(1000);
  calcularCinzaRefletancia();
  guardarDadosEEPROM();

  Serial.println(F("\nCALIBRAÇÃO FINALIZADA!!"));
  
  delay(200);
  toy.ledsAlerta(4);
  delay(200);
  voltarMenu = true;
}


void Calibragem::calibracaoPretoRefletancia(){
  int i;
  Serial.println(F("\n  | Coletando Dados |"));
  Serial.print  (F("  |-------"));

  for (i = 0; i < 10; i++) {
    mediaPretoRefletanciaMaisEsq = mediaPretoRefletanciaMaisEsq + robo.lerSensorLinhaMaisEsq();
    mediaPretoRefletanciaEsq = mediaPretoRefletanciaEsq + robo.lerSensorLinhaEsq();
    mediaPretoRefletanciaDir = mediaPretoRefletanciaDir + robo.lerSensorLinhaDir();
    mediaPretoRefletanciaMaisDir = mediaPretoRefletanciaMaisDir + robo.lerSensorLinhaMaisDir();
    delay(DELAY_INTERVALO_DE_CAPTURA);
    Serial.print(F("-"));
  }
  Serial.println(F("|"));
  Serial.println(F("  |    Concluido    |"));
  
  mediaPretoRefletanciaMaisEsq = mediaPretoRefletanciaMaisEsq / 10;
  mediaPretoRefletanciaEsq = mediaPretoRefletanciaEsq / 10;
  mediaPretoRefletanciaDir = mediaPretoRefletanciaDir / 10;
  mediaPretoRefletanciaMaisDir = mediaPretoRefletanciaMaisDir / 10;
  
  toy.ledAlerta(1, 10, 50);

  Serial.println(F("\n  Valores Pretos Capturados dos Sensores de Refletância: "));
  Serial.println(F("  +esq    esq     dir     +dir"));
  Serial.print  (F("  "));
  Serial.print  (mediaPretoRefletanciaMaisEsq);
  Serial.print  (F("   "));
  Serial.print  (mediaPretoRefletanciaEsq);
  Serial.print  (F("   "));
  Serial.print  (mediaPretoRefletanciaDir);
  Serial.print  (F("   "));
  Serial.println(mediaPretoRefletanciaMaisDir);
}


void Calibragem::calibracaoPretoCor(){
  int i;
  Serial.println(F("\n  | Coletando Dados |"));
  Serial.print  (F("  |-------"));
  
  capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
  capturadorDeCorAuxDirHSV = robo.getHSVDireito();
  mediaPretoCorEsq.h = capturadorDeCorAuxEsqHSV.h;
  mediaPretoCorDir.h = capturadorDeCorAuxDirHSV.h;
  mediaPretoCorEsq.s = capturadorDeCorAuxEsqHSV.s;
  mediaPretoCorDir.s = capturadorDeCorAuxDirHSV.s;
  mediaPretoCorEsq.v = capturadorDeCorAuxEsqHSV.v;
  mediaPretoCorDir.v = capturadorDeCorAuxDirHSV.v;
  
  for (i = 0; i < 10; i++) {
    capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
    capturadorDeCorAuxDirHSV = robo.getHSVDireito();
    mediaPretoCorEsq.h = (mediaPretoCorEsq.h + capturadorDeCorAuxEsqHSV.h) / 2; 
    mediaPretoCorDir.h = (mediaPretoCorDir.h + capturadorDeCorAuxDirHSV.h) / 2;  
    mediaPretoCorEsq.s = (mediaPretoCorEsq.s + capturadorDeCorAuxEsqHSV.s) / 2;
    mediaPretoCorDir.s = (mediaPretoCorDir.s + capturadorDeCorAuxDirHSV.s) / 2;   
    mediaPretoCorEsq.v = (mediaPretoCorEsq.v + capturadorDeCorAuxEsqHSV.v) / 2; 
    mediaPretoCorDir.v = (mediaPretoCorDir.v + capturadorDeCorAuxDirHSV.v) / 2;   
    delay(DELAY_INTERVALO_DE_CAPTURA);
    Serial.print(F("-"));
  } 
  Serial.println(F("|"));
  Serial.println(F("  |    Concluido    |"));

  toy.ledAlerta(1, 10, 50);

  Serial.println(F("\n  Valores Pretos Capturados dos Sensores de Cor: "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (mediaPretoCorEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(mediaPretoCorDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (mediaPretoCorEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(mediaPretoCorDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (mediaPretoCorEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(mediaPretoCorDir.v);
}


void Calibragem::calibracaoBrancoRefletanciaCor(){  
  int i;
  Serial.println(F("\n  | Coletando Dados |"));
  Serial.print  (F("  |-------"));
  
  capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
  capturadorDeCorAuxDirHSV = robo.getHSVDireito();
  mediaBrancoCorEsq.h = capturadorDeCorAuxEsqHSV.h; 
  mediaBrancoCorDir.h = capturadorDeCorAuxDirHSV.h;
  mediaBrancoCorEsq.s = capturadorDeCorAuxEsqHSV.s; 
  mediaBrancoCorDir.s = capturadorDeCorAuxDirHSV.s;
  mediaBrancoCorEsq.v = capturadorDeCorAuxEsqHSV.v; 
  mediaBrancoCorDir.v = capturadorDeCorAuxDirHSV.v;
  
  for (i = 0; i < 10; i++) {
    mediaBrancoRefletanciaMaisEsq = mediaBrancoRefletanciaMaisEsq + robo.lerSensorLinhaMaisEsq();
    mediaBrancoRefletanciaEsq = mediaBrancoRefletanciaEsq + robo.lerSensorLinhaEsq();
    mediaBrancoRefletanciaDir = mediaBrancoRefletanciaDir + robo.lerSensorLinhaDir();
    mediaBrancoRefletanciaMaisDir = mediaBrancoRefletanciaMaisDir + robo.lerSensorLinhaMaisDir();
    
    capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
    capturadorDeCorAuxDirHSV = robo.getHSVDireito();
    mediaBrancoCorEsq.h = (mediaBrancoCorEsq.h + capturadorDeCorAuxEsqHSV.h) / 2; 
    mediaBrancoCorDir.h = (mediaBrancoCorDir.h + capturadorDeCorAuxDirHSV.h) / 2;
    mediaBrancoCorEsq.s = (mediaBrancoCorEsq.s + capturadorDeCorAuxEsqHSV.s) / 2; 
    mediaBrancoCorDir.s = (mediaBrancoCorDir.s + capturadorDeCorAuxDirHSV.s) / 2;
    mediaBrancoCorEsq.v = (mediaBrancoCorEsq.v + capturadorDeCorAuxEsqHSV.v) / 2; 
    mediaBrancoCorDir.v = (mediaBrancoCorDir.v + capturadorDeCorAuxDirHSV.v) / 2;
    
    delay(DELAY_INTERVALO_DE_CAPTURA);
    Serial.print(F("-"));
  }
  Serial.println(F("|"));
  Serial.println(F("  |    Concluido    |"));
  
  mediaBrancoRefletanciaMaisEsq = mediaBrancoRefletanciaMaisEsq / 10;
  mediaBrancoRefletanciaEsq = mediaBrancoRefletanciaEsq / 10;
  mediaBrancoRefletanciaDir = mediaBrancoRefletanciaDir / 10;
  mediaBrancoRefletanciaMaisDir = mediaBrancoRefletanciaMaisDir / 10;

  toy.ledAlerta(2, 10, 50);

  Serial.println(F("\n  Valores Brancos Capturados dos Sensores de Refletância: "));
  Serial.println(F("  +esq    esq     dir     +dir"));
  Serial.print  (F("  "));
  Serial.print  (mediaBrancoRefletanciaMaisEsq);
  Serial.print  (F("   "));
  Serial.print  (mediaBrancoRefletanciaEsq);
  Serial.print  (F("   "));
  Serial.print  (mediaBrancoRefletanciaDir);
  Serial.print  (F("   "));
  Serial.println(mediaBrancoRefletanciaMaisDir);

  Serial.println(F("\n  Valores Brancos Capturados dos Sensores de Cor: "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (mediaBrancoCorEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(mediaBrancoCorDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (mediaBrancoCorEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(mediaBrancoCorDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (mediaBrancoCorEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(mediaBrancoCorDir.v);
}


void Calibragem::calibracaoVerdeEsq(){
  int i;
  Serial.println(F("\n  | Coletando Dados |"));
  Serial.print  (F("  |-------"));
  
  capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
  mediaVerdeCorEsqHSV.h = capturadorDeCorAuxEsqHSV.h;
  mediaVerdeCorEsqHSV.s = capturadorDeCorAuxEsqHSV.s;
  mediaVerdeCorEsqHSV.v = capturadorDeCorAuxEsqHSV.v;
  
  mediaVerdeCorEsqRGBmaior = robo.getRGBEsquerdo();
  mediaVerdeCorEsqRGBmenor = robo.getRGBEsquerdo();

  for (i = 0; i < 10; i++) {
    capturadorDeCorAuxEsqHSV = robo.getHSVEsquerdo();
    mediaVerdeCorEsqHSV.h = (mediaVerdeCorEsqHSV.h + capturadorDeCorAuxEsqHSV.h) / 2; 
    mediaVerdeCorEsqHSV.s = (mediaVerdeCorEsqHSV.s + capturadorDeCorAuxEsqHSV.s) / 2; 
    mediaVerdeCorEsqHSV.v = (mediaVerdeCorEsqHSV.v + capturadorDeCorAuxEsqHSV.v) / 2;   

    capturadorDeCorAuxRGB = robo.getRGBEsquerdo(); 
    if(capturadorDeCorAuxRGB.vermelho > mediaVerdeCorEsqRGBmaior.vermelho){
      mediaVerdeCorEsqRGBmaior.vermelho = capturadorDeCorAuxRGB.vermelho; 
    }
    if(capturadorDeCorAuxRGB.verde > mediaVerdeCorEsqRGBmaior.verde){
      mediaVerdeCorEsqRGBmaior.verde = capturadorDeCorAuxRGB.verde;
    }
    if(capturadorDeCorAuxRGB.azul > mediaVerdeCorEsqRGBmaior.azul){
      mediaVerdeCorEsqRGBmaior.azul = capturadorDeCorAuxRGB.azul;
    }

    if(capturadorDeCorAuxRGB.vermelho < mediaVerdeCorEsqRGBmenor.vermelho){
      mediaVerdeCorEsqRGBmenor.vermelho = capturadorDeCorAuxRGB.vermelho; 
    }
    if(capturadorDeCorAuxRGB.verde < mediaVerdeCorEsqRGBmenor.verde){
      mediaVerdeCorEsqRGBmenor.verde = capturadorDeCorAuxRGB.verde;
    }
    if(capturadorDeCorAuxRGB.azul < mediaVerdeCorEsqRGBmenor.azul){
      mediaVerdeCorEsqRGBmenor.azul = capturadorDeCorAuxRGB.azul;
    }

    delay(DELAY_INTERVALO_DE_CAPTURA);
    Serial.print(F("-"));
  } 
  Serial.println(F("|"));
  Serial.println(F("  |    Concluido    |"));

  toy.ledAlerta(3, 10, 50);

  Serial.println(F("\n  Valores do Verde Capturados do Sensor de Cor Esquerdo: "));
  Serial.print  (F("  H: "));
  Serial.println(mediaVerdeCorEsqHSV.h);     
  Serial.print  (F("  S: "));
  Serial.println(mediaVerdeCorEsqHSV.s);
  Serial.print  (F("  V: "));
  Serial.println(mediaVerdeCorEsqHSV.v);  
}


void Calibragem::calibracaoVerdeDir(){
  int i;
  Serial.println(F("\n  | Coletando Dados |"));
  Serial.print  (F("  |-------"));
  
  capturadorDeCorAuxDirHSV = robo.getHSVDireito();
  mediaVerdeCorDirHSV.h = capturadorDeCorAuxDirHSV.h;
  mediaVerdeCorDirHSV.s = capturadorDeCorAuxDirHSV.s;
  mediaVerdeCorDirHSV.v = capturadorDeCorAuxDirHSV.v;
  
  mediaVerdeCorDirRGBmaior = robo.getRGBDireito();
  mediaVerdeCorDirRGBmenor = robo.getRGBDireito();

  for (i = 0; i < 10; i++) {
    capturadorDeCorAuxDirHSV = robo.getHSVDireito();
    mediaVerdeCorDirHSV.h = (mediaVerdeCorDirHSV.h + capturadorDeCorAuxDirHSV.h) / 2;
    mediaVerdeCorDirHSV.s = (mediaVerdeCorDirHSV.s + capturadorDeCorAuxDirHSV.s) / 2;      
    mediaVerdeCorDirHSV.v = (mediaVerdeCorDirHSV.v + capturadorDeCorAuxDirHSV.v) / 2;   
    
    capturadorDeCorAuxRGB = robo.getRGBDireito(); 
    if(capturadorDeCorAuxRGB.vermelho > mediaVerdeCorDirRGBmaior.vermelho){
      mediaVerdeCorDirRGBmaior.vermelho = capturadorDeCorAuxRGB.vermelho; 
    }
    if(capturadorDeCorAuxRGB.verde > mediaVerdeCorDirRGBmaior.verde){
      mediaVerdeCorDirRGBmaior.verde = capturadorDeCorAuxRGB.verde;
    }
    if(capturadorDeCorAuxRGB.azul > mediaVerdeCorDirRGBmaior.azul){
      mediaVerdeCorDirRGBmaior.azul = capturadorDeCorAuxRGB.azul;
    }

    if(capturadorDeCorAuxRGB.vermelho < mediaVerdeCorDirRGBmenor.vermelho){
      mediaVerdeCorDirRGBmenor.vermelho = capturadorDeCorAuxRGB.vermelho; 
    }
    if(capturadorDeCorAuxRGB.verde < mediaVerdeCorDirRGBmenor.verde){
      mediaVerdeCorDirRGBmenor.verde = capturadorDeCorAuxRGB.verde;
    }
    if(capturadorDeCorAuxRGB.azul < mediaVerdeCorDirRGBmenor.azul){
      mediaVerdeCorDirRGBmenor.azul = capturadorDeCorAuxRGB.azul;
    }

    delay(DELAY_INTERVALO_DE_CAPTURA);
    Serial.print(F("-"));
  } 
  Serial.println(F("|"));
  Serial.println(F("  |    Concluido    |"));

  toy.ledAlerta(3, 10, 50);

  Serial.println(F("\n  Valores do Verde Capturados do Sensor de Cor Direito: "));
  Serial.print  (F("  H: "));
  Serial.println(mediaVerdeCorDirHSV.h);     
  Serial.print  (F("  S: "));
  Serial.println(mediaVerdeCorDirHSV.s);
  Serial.print  (F("  V: "));
  Serial.println(mediaVerdeCorDirHSV.v);
}


void Calibragem::calcularCinzaRefletancia(){
  //Calculando Cinza
  
  cinzaMaisEsq = (mediaPretoRefletanciaMaisEsq + mediaBrancoRefletanciaMaisEsq)/2; 
  cinzaEsq = (mediaPretoRefletanciaEsq + mediaBrancoRefletanciaEsq)/2;
  cinzaDir = (mediaPretoRefletanciaDir + mediaBrancoRefletanciaDir)/2;
  cinzaMaisDir = (mediaPretoRefletanciaMaisDir + mediaBrancoRefletanciaMaisDir)/2; 

  Serial.println(F("\n  Valores Calculados dos sensores de refletância: "));
  Serial.println(F("   +esq    esq     dir     +dir"));
  Serial.print  (F("   "));
  Serial.print  (cinzaMaisEsq);
  Serial.print  (F("   "));
  Serial.print  (cinzaEsq);
  Serial.print  (F("   "));
  Serial.print  (cinzaDir);
  Serial.print  (F("   "));
  Serial.println(cinzaMaisDir);

  Serial.println(F("\n  Valores Calculados dos sensores de Cor: "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (mediaPretoCorEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(mediaPretoCorDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (mediaPretoCorEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(mediaPretoCorDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (mediaPretoCorEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(mediaPretoCorDir.v);
}


void Calibragem::guardarDadosEEPROM(){
  //Dados Refletância
  val.refletanciaMaisEsq = cinzaMaisEsq;
  val.refletanciaEsq = cinzaEsq;
  val.refletanciaDir = cinzaDir;
  val.refletanciaMaisDir = cinzaMaisDir;

  //Dados Cor
  val.pretoEsq.h = mediaPretoCorEsq.h;
  val.pretoEsq.s = mediaPretoCorEsq.s;
  val.pretoEsq.v = mediaPretoCorEsq.v;
  
  val.pretoDir.h = mediaPretoCorDir.h;
  val.pretoDir.s = mediaPretoCorDir.s;
  val.pretoDir.v = mediaPretoCorDir.v;
  
  val.brancoEsq.h = mediaBrancoCorEsq.h;
  val.brancoEsq.s = mediaBrancoCorEsq.s;
  val.brancoEsq.v = mediaBrancoCorEsq.v;
  
  val.brancoDir.h = mediaBrancoCorDir.h;
  val.brancoDir.s = mediaBrancoCorDir.s;
  val.brancoDir.v = mediaBrancoCorDir.v;
  
  val.verdeEsq.h = mediaVerdeCorEsqHSV.h;
  val.verdeEsq.s = mediaVerdeCorEsqHSV.s;
  val.verdeEsq.v = mediaVerdeCorEsqHSV.v;
  
  val.verdeDir.h = mediaVerdeCorDirHSV.h;
  val.verdeDir.s = mediaVerdeCorDirHSV.s;
  val.verdeDir.v = mediaVerdeCorDirHSV.v;

  robo.salvarCalibracao(val);
  Serial.println(F("\n  Dados Guardados na EEPROM"));
  robo.lerCalibracao(val);
}

void Calibragem::printDadosEEPROM(){
  robo.lerCalibracao(val);
  Serial.println(F("-----------------------------------"));
  Serial.println(F("Dados da Última Calibração (EEPROM)"));
  Serial.println(F("-----------------------------------"));
  Serial.println(F("  Sensores de Refletância:"));
  Serial.println(F("  +esq    esq     dir     +dir"));
  Serial.print  (F("  "));
  Serial.print  (val.refletanciaMaisEsq);
  Serial.print  (F("      "));
  Serial.print  (val.refletanciaEsq);
  Serial.print  (F("      "));
  Serial.print  (val.refletanciaDir);
  Serial.print  (F("      "));
  Serial.println(val.refletanciaMaisDir);

  Serial.println(F("\n  Sensores de Cor (Preto): "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (val.pretoEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(val.pretoDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (val.pretoEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(val.pretoDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (val.pretoEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(val.pretoDir.v);

  Serial.println(F("\n  Sensores de Cor (Verde): "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (val.verdeEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(val.verdeDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (val.verdeEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(val.verdeDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (val.verdeEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(val.verdeDir.v);

  Serial.println(F("\n  Sensores de Cor (Branco): "));
  Serial.println(F("  esq            dir   "));
  Serial.print  (F("  H: "));
  Serial.print  (val.brancoEsq.h);
  Serial.print  (F("      H: "));
  Serial.println(val.brancoDir.h);
  Serial.print  (F("  S: "));
  Serial.print  (val.brancoEsq.s);
  Serial.print  (F("        S: "));
  Serial.println(val.brancoDir.s);
  Serial.print  (F("  V: "));
  Serial.print  (val.brancoEsq.v);
  Serial.print  (F("      V: "));
  Serial.println(val.brancoDir.v);
}