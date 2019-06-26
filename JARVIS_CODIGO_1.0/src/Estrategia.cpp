#include "Estrategia.h"

#define FASE_DE_TESTE false

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

//Delay usado para o robo voltar ao bbbb no bpbb e bbpb, o mais centralizado possivel.
#define DELAY_VOLTAR_PARA_A_LINHA 35
//Velocidade nos motores 35 - Delay 35


void Estrategia::seguirLinha(){
  if(refletancia.bbbb()){
    motores.frente();
  } else if(refletancia.bpbb()){
    acaoBPBB();
  } else if(refletancia.bbpb()){
    acaoBBPB();
  }else{
    frearUltimoMovimento();
    refletancia.comoEstaoMeusSensores();
    motores.pararAteBotao1();
  }
}


//PB
void Estrategia::acaoBPBB(){
  setEsquerda();
  while(refletancia.bpbb()){
    robo.acionarMotores(-35, 35);
    if(refletancia.sensorMaisDir('P')){
      robo.ligarLed(1);
      motores.pararAteBotao1();
    }
  }
  if(refletancia.bbbb()){
    delay(DELAY_VOLTAR_PARA_A_LINHA);
    motores.frearGiroEsq();
  }
    //motores.girarEsq();
}

//BP
void Estrategia::acaoBBPB(){
  setDireita();
    while(refletancia.bbpb()){
      robo.acionarMotores(35, -35);
    }
    if(refletancia.bbbb()){
      delay(DELAY_VOLTAR_PARA_A_LINHA);
      motores.frearGiroDir();
    }
    //motores.girarDir();
}

//PPBB
void Estrategia::acaoPPBB(){
  motores.frearPor(500); 
  //Se não estiver no PPBB
  if(refletancia.ppbb() == false){
    alinharComPPBB();
  } 

  //Olhar os Sensores de Cor
  if(acaoVerde() == false){ //Se não tiver verde
    //Realizar manobra do metodo
    enrolarEsquinaParaEsq(false);
  } 
}

//PPPP
void Estrategia::acaoPPPP(){
  frearUltimoMovimento();
  
  alinharComPPPP();
  
  //Olhar os Sensores de Cor
  if(acaoVerde() == false){ //Se não tiver verde
    //Realizar manobra do metodo
    while(refletancia.sensorMaisEsq('P')){
      motores.frente();
    }
  } 
}

void Estrategia::alinharComPPBB(){
  if(!refletancia.bbbb()){ //Ir até todos bancos para começar o alinhamento
    boolean maisEsquerdoComecouNoPreto = false;
    boolean maisEsquerdoSaiuDoPreto = false;
    boolean estaEmUmaEncrisilhada = false;

    if(refletancia.sensorMaisEsq('P')){
      maisEsquerdoComecouNoPreto = true;
    }

    while(!refletancia.bbbb()){ 
      motores.frenteDevagar();
      if(maisEsquerdoComecouNoPreto){ //Se ele começou no preto
        if(refletancia.sensorMaisEsq('B') && maisEsquerdoSaiuDoPreto == false){ //Se ele saiu do preto
          maisEsquerdoSaiuDoPreto = true;
        }
        if(maisEsquerdoSaiuDoPreto){ //Se ele saiu do preto
          if(refletancia.sensorMaisEsq('P')){ //E voltou para o preto
            estaEmUmaEncrisilhada = true;
            toy.ligarApenasLed(1);
            motores.pararAteBotao1();

          }
        }
      }
    }
    motores.frearDevagar();
  }
  
  if(refletancia.bbbp()){ //Robô chegou torto com o sensor mais esquerdo no preto
    while(refletancia.sensorEsq('B')){ //Ajusta o sensor Esquerdo
      motores.voltarDevagarDir();
      delay(50);
    }
  }

  boolean sensorMaisEsqChegouCedo = false;

  while(refletancia.sensorEsq('B')){ //Ajuste padrão - Parte 1
    robo.acionarMotores(-25, -20);
    if(refletancia.sensorMaisEsq('P')){
      sensorMaisEsqChegouCedo = true;
      break;
    }
    if(refletancia.sensorMaisDir('P') || refletancia.sensorDir('P')){ //Se enquanto ele estiver voltando perceber algo a mais, ele pode estar em uma encrusilhada ou desalinhado 
      alinharComPPPP();
    }
  } 

  if(sensorMaisEsqChegouCedo){
    
    while(refletancia.sensorEsq('B')){
      robo.ligarLed(2);
      robo.acionarMotores(-25, 0);
    }
    robo.desligarLed(2);
    while(refletancia.sensorMaisEsq('P')){
      robo.acionarMotores(25,0);
    }

    while(refletancia.sensorEsq('B')){
      robo.acionarMotores(0, -30);
    }
    
  } else {
    while(refletancia.sensorMaisEsq('B')){
      robo.acionarMotores(-25, 0);
    }
  }

  if(refletancia.pbbb()){
    while(refletancia.sensorEsq('B')){
      robo.acionarMotores(0, -30);
    }   
  }

  if(refletancia.bpbb()){
    while(refletancia.sensorEsq('B')){
      robo.acionarMotores(0, -30);
    }   
  }

  motores.pararPor(500);
  
  if(FASE_DE_TESTE){
    refletancia.comoEstaoMeusSensores();

    motores.pararAteBotao1();
  }
}


void Estrategia::alinharComPPPP(){
  toy.ligarLeds();
  if(refletancia.bbpb()){
    while(refletancia.sensorDir('P')){
      robo.acionarMotores(0, 25);
    }
  }

  if(refletancia.bbpp()){
    while(refletancia.sensorDir('P') || refletancia.sensorMaisDir('P')){
      robo.acionarMotores(0, 25);
    }
  }
  
  motores.pararPor(1000);

  if(refletancia.bbbb()){
    toy.ledAlerta(2, 10, 50);
  }

  while(refletancia.sensorMaisEsq('B')){
    robo.acionarMotores(-25,0);
  }
  motores.parar();
  if(refletancia.pppp()){
    toy.ledAlerta(1, 10, 50);  
  }
  if(FASE_DE_TESTE){
    motores.pararAteBotao1();
  }
}

#define DELAY_ENTRE_SENSORES_DE_COR 150

boolean Estrategia::acaoVerde(){
  motores.parar();
  boolean viuVerde = true;
  boolean verdeEsq = false;
  boolean verdeDir = false;

  if(cor.verificarVerdeEsq()){
    verdeEsq = true;
  } 
  
  delay(DELAY_ENTRE_SENSORES_DE_COR);
  
  if(cor.verificarVerdeDir()){
    verdeDir = true;
  }

  if(FASE_DE_TESTE){
    cor.comoEstaoMeusSensores();
    motores.pararAteBotao1();
  }

  if((verdeEsq == false) && (verdeDir == false)){        //Não Verde - Não Verde
    //Não achou verde
    viuVerde = false;
  
  } else if((verdeEsq  == true) && (verdeDir == false)){ //Verde - Não Verde
    //Virar para a Esquerda
    toy.ligarApenasLed(3);
    enrolarEsquinaParaEsq(true);

  } else if((verdeEsq == false) && (verdeDir == true)){  //Não Verde - Verde
    //Virar para a Direita
    toy.ligarApenasLed(3);
    enrolarEsquinaParaDir(true);

  } else if((verdeEsq == true) && (verdeDir == true)){   //Verde - Verde
    //Dar meia volta
    toy.ligarApenasLed(3);
  } 

  return viuVerde;
}

#define DELAY_AVANCO_DOS_MOTORES 275 //Distancia percorrida pelos motores
#define DELAY_ENTRE_AVANCO_DOS_MOTORES 590
#define DELAY_ENTRE_GIROS 50

void Estrategia::enrolarEsquinaParaEsq(boolean veioDeUmVerde){
  for(int contador = 1; contador <= 2; contador++){
    robo.acionarMotores(25, 28);
    delay(DELAY_AVANCO_DOS_MOTORES);
    motores.frearDevagar();
    delay(DELAY_ENTRE_AVANCO_DOS_MOTORES);
    if(contador == 1 && veioDeUmVerde == false){
      if(acaoVerde()){
        return;
      }
    }
  }

  delay(200);
  
  if(veioDeUmVerde == true){
    if(refletancia.sensorMaisEsq('B')){ //Tudo show
      while(refletancia.sensorMaisEsq('B')){
        robo.acionarMotores(-30,30);
      }
      motores.frearGiroEsq();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorMaisEsq('P')){
        robo.acionarMotores(-30,30);
      }
      motores.frearGiroEsq();

      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorEsq('P')){
        robo.acionarMotores(-30,30);
      }
      delay(50);
      motores.frearGiroEsq();
      
      delay(DELAY_ENTRE_GIROS);

    } else { //Se o maisEsq estiver em cima do preto
      while(refletancia.sensorMaisEsq('P')){
        robo.acionarMotores(-30,30);
      }
      
      while(refletancia.sensorMaisEsq('B')){
        robo.acionarMotores(-30,30);
      }
      motores.frearGiroEsq();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorMaisEsq('P')){
        robo.acionarMotores(-30,30);
      }
      motores.frearGiroEsq();

      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorEsq('P')){
        robo.acionarMotores(-30,30);
      }
      delay(50);
      motores.frearGiroEsq();  
    }
    //motores.pararAteBotao1();
  } else { //Se não vinher de um verde
    if(refletancia.sensorDir('B')){ //Tudo show
      while(refletancia.sensorDir('B')){
        robo.acionarMotores(-30,30);
      }
      motores.frearGiroEsq();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorDir('P')){
        robo.acionarMotores(30,-30);
      }
      delay(50);
      motores.frearGiroDir();
      
      delay(DELAY_ENTRE_GIROS);
    }
  }
}

void Estrategia::enrolarEsquinaParaDir(boolean veioDeUmVerde){
  for(int contador = 1; contador <= 2; contador++){
    robo.acionarMotores(28, 25);
    delay(DELAY_AVANCO_DOS_MOTORES);
    motores.frearDevagar();
    delay(DELAY_ENTRE_AVANCO_DOS_MOTORES);
    if(contador == 1 && veioDeUmVerde == false){
      if(acaoVerde()){
        return;
      }
    }
  }

  delay(200);
  
  if(veioDeUmVerde == true){
    if(refletancia.sensorMaisDir('B')){ //Tudo show
      while(refletancia.sensorMaisDir('B')){
        robo.acionarMotores(30,-30);
      }
      motores.frearGiroDir();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorMaisDir('P')){
        robo.acionarMotores(30,-30);
      }
      motores.frearGiroDir();

      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorDir('P')){
        robo.acionarMotores(30,-30);
      }
      delay(50);
      motores.frearGiroDir();
      
      delay(DELAY_ENTRE_GIROS);

    } else { //Se o maisEsq estiver em cima do preto
      while(refletancia.sensorMaisDir('P')){
        robo.acionarMotores(30,-30);
      }
      
      while(refletancia.sensorMaisDir('B')){
        robo.acionarMotores(30,-30);
      }
      motores.frearGiroDir();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorMaisDir('P')){
        robo.acionarMotores(30,-30);
      }
      motores.frearGiroDir();

      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorDir('P')){
        robo.acionarMotores(30,-30);
      }
      delay(50);
      motores.frearGiroDir();  
    }
    //motores.pararAteBotao1();

  } else { //Se não vinher de um verde
    if(refletancia.sensorEsq('B')){ //Tudo show
      while(refletancia.sensorEsq('B')){
        robo.acionarMotores(30,-30);
      }
      motores.frearGiroEsq();
      
      delay(DELAY_ENTRE_GIROS);

      while(refletancia.sensorEsq('P')){
        robo.acionarMotores(-30,30);
      }
      delay(50);
      motores.frearGiroDir();
      
      delay(DELAY_ENTRE_GIROS);
    }
  }
}

void Estrategia::desviarObstaculo(){
  if(distancia.verificarObstaculo()){
    delay(DELAY_PAUSA_MOVIMENTO);
      motores.girar90Dir();
      motores.parar();
      delay(DELAY_PAUSA_MOVIMENTO);

      motores.frenteDevagar();
      delay(DELAY_FRENTE1);
      motores.parar();
      delay(DELAY_PAUSA_MOVIMENTO);
      
      motores.girar90Esq();
      motores.parar();
      delay(DELAY_PAUSA_MOVIMENTO);
      
      motores.frenteDevagar();
      delay(DELAY_FRENTE2);
      motores.parar();
      delay(DELAY_PAUSA_MOVIMENTO);
      
      motores.girar90Esq();
      motores.parar();
      delay(DELAY_PAUSA_MOVIMENTO);
      
      while(refletancia.bbbb()){
        motores.frenteDevagar();
      }
      
      while(!refletancia.bbbb()){
        motores.frenteDevagar();
      }

      while(!refletancia.sensorDir('P')){
        motores.girarDevagarDir();
      }
  }
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

