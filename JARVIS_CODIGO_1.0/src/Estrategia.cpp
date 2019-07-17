#include "Estrategia.h"

#define FASE_DE_TESTE false

#define DELAY_INTERVALOS 350

//Delays para Desviar Obstaculo
#define DELAY_PAUSA_MOVIMENTO 500
#define DELAY_FRENTE1 750
#define DELAY_FRENTE2 1125
#define DELAY_FRENTE3 1000

//Delays que eu não sei para que serve pq esqueci
#define DELAY_PARADA_CURVA 150
#define DELAY_VOLTAR_CURVA 100
#define DELAY_VERIFICACAO_ONDE_ESTOU 300 
#define DELAY_VERIFICACAO_PPPP 500

Estrategia::Estrategia(){
  //
}

void Estrategia::start(){
  if(dadosCapturados == false){
    refletancia.start();
  }
  dadosCapturados = true;
}

void Estrategia::executar(){
  toy.desligarLeds();
  start();
  
  //desviarObstaculo();
  seguirLinha();
}


void Estrategia::seguirLinha(){
  if(refletancia.bbbb()){
    motores.frente();
    setFrente();
  } else if(refletancia.bpbb()){
    acaoBPBB();
  } else if(refletancia.bbpb()){
    acaoBBPB();
  } else if(refletancia.ppbb()){
    acaoPPBB();
  } else if(refletancia.bbpp()){
    acaoBBPP();
  } else if(refletancia.pppp()){
    acaoPPPP();
  }
}

//Delay usado para o robo voltar ao bbbb no bpbb e bbpb, o mais centralizado possivel.
#define DELAY_VOLTAR_PARA_A_LINHA 60
//Velocidade nos motores 35 - Delay 35

//PB (Esquerda)
void Estrategia::acaoBPBB(){
  while(refletancia.sensorEsq('P')){
    motores.girarEsq();
    setEsquerda();
    
    //Verificações no momento do Giro
    if(refletancia.ppbb()){ //PPBB desfarçado de PB
      motores.frear(); //Para não avançar para o outro lado do preto
      robo.ligarLed(3);
      acaoPPBB();

    } else if(refletancia.sensorMaisDir('P')){ //Encrusilhada desfarçada de PB
      robo.ligarLed(1);
      frearUltimoMovimento();
      alinhamentoBPBB();
    }
  }
}

//BP (Direita)
void Estrategia::acaoBBPB(){
  while(refletancia.sensorDir('P')){
    motores.girarDir();
    setDireita();
    
    //Verificações no momento do Giro
    if(refletancia.bbpp()){ //PPBB desfarçado de PB
      motores.frear(); //Para não avançar para o outro lado do preto
      robo.ligarLed(1);
      acaoBBPP();

    } else if(refletancia.sensorMaisEsq('P')){ //Encrusilhada desfarçada de PB
      robo.ligarLed(3);
      frearUltimoMovimento();
      alinhamentoBBPB();
    }
  }
}

//PPBB (Esquerda - 2 Sensores)
void Estrategia::acaoPPBB(){
  motores.criarFreio(50, -40); //Tempo, forca
  toy.selecionarLedsAlerta(true, true, false, 3);
  motores.pararAteBotao1();
}

//BBPP (Direita - 2 Sensores)
void Estrategia::acaoBBPP(){
  motores.criarFreio(50, -40); //Tempo, forca
  toy.selecionarLedsAlerta(false, true, true, 3);
  motores.pararAteBotao1();
}

//PPPP/
void Estrategia::acaoPPPP(){
  motores.frear();
  toy.ledsAlerta(3);
  motores.pararAteBotao1();
}

void Estrategia::alinhamentoBPBB(){ //Se acharmos uma encruzilhada enquanto PB entramos nesse método
  motores.pararPor(DELAY_INTERVALOS);

  //Faz o sensor mais direito voltar para o branco
  while(refletancia.sensorMaisDir('P')){
    motores.voltarDir();
  }
  motores.pararPor(DELAY_INTERVALOS);

  /* 
  ALINHAMENTO PARA DEIXAR NA BORDA (não funciona direito)
  if(refletancia.sensorMaisEsq('B')){ //Alinhando para deixar o sensor maisEsq na borda
    while(refletancia.sensorMaisEsq('B')){ //Vai até o preto
      motores.virarDir();
    }
    while(refletancia.sensorMaisDir('P')){  //Volta para o braco para ficar bem na borda
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }
  
  if(refletancia.sensorMaisDir('B')){ //Alinhando para deixar o sensor maisDir na borda
    while(refletancia.sensorMaisDir('B')){ //Vai até o preto
      motores.virarEsq();
    }
    while(refletancia.sensorMaisDir('P')){  //Volta para o braco para ficar bem na borda
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);  
  }
  */

  //Faz o sensor mais esquerdo voltar para o branco
  while(refletancia.sensorMaisEsq('P')){
    motores.voltarEsq();
  }
  motores.pararPor(DELAY_INTERVALOS);

  //Se quando voltar, o robô vê todos branco, então não tem verde e deve voltar ao seguir linha.
  //Nesse caso, ele deve encontrar PPPP ou PPBB puro (Diretamente)
  if(refletancia.bbbb()){
    return;
  }

  if(refletancia.bppb()){
    while(refletancia.sensorDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  if(refletancia.pppb() || refletancia.bppp()){
    motores.pararPor(500);
    toy.selecionarLedsAlerta(true, false, true, 3);
    motores.pararAteBotao1();
  }

  robo.desligarTodosLeds();
  refletancia.comoEstaoMeusSensores();
  motores.pararAteBotao1();
}

void Estrategia::alinhamentoBBPB(){ //Se acharmos uma encruzilhada enquanto BP entramos nesse método
  motores.pararPor(DELAY_INTERVALOS);

  //Faz o sensor mais esquerdo voltar para o branco
  while(refletancia.sensorMaisEsq('P')){
    motores.voltarEsq();
  }
  motores.pararPor(DELAY_INTERVALOS);

  //Faz o sensor mais direito voltar para o branco
  while(refletancia.sensorMaisDir('P')){
    motores.voltarDir();
  }
  motores.pararPor(DELAY_INTERVALOS);

  //Se quando voltar, o robô vê todos branco, então não tem verde e deve voltar ao seguir linha.
  //Nesse caso, ele deve encontrar PPPP ou BBPP puro (Diretamente)
  if(refletancia.bbbb()){
    return;
  }

  if(refletancia.pppb() || refletancia.bppp()){
    motores.pararPor(500);
    toy.selecionarLedsAlerta(true, false, true, 3);
    motores.pararAteBotao1();
  }

  robo.desligarTodosLeds();
  refletancia.comoEstaoMeusSensores();
  motores.pararAteBotao1();
}

void Estrategia::alinharComPPBB(){
}

//Métodos de Registro de Movimentos
void Estrategia::setFrente(){
  frente = true;
  esquerda = false;
  direita = false;
}
void Estrategia::setDireita(){
  frente = false;
  esquerda = false;
  direita = true;
}
void Estrategia::setEsquerda(){
  frente = false;
  esquerda = true;
  direita = false;
}
int Estrategia::ultimoMovimentoRegistrado(){
  int resposta = 0;
  if(frente){
    resposta = 0;
  } else if (esquerda) {
    resposta = -1;
  } else if (direita) {
    resposta = 1;
  }
  return resposta;
}
void Estrategia::frearUltimoMovimento(){
  switch(ultimoMovimentoRegistrado()){
    case 0:   //Frente
      motores.frear();
      break;
    case -1:  //Esquerda
      motores.frearGiroEsq();
      break;
    case 1:   //Direita
      motores.frearGiroDir();
      break;
  }
}

