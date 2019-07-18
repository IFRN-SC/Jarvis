#include "Estrategia.h"

#define FASE_DE_TESTE false

#define DELAY_INTERVALOS 350

#define DELAY_VAI_VERIFICA_VERDE_VOLTA 200
#define DELAY_MINI_VAI_VERIFICA_VERDE_VOLTA 100
#define DELAY_AVANCA_VERIFICA_VERDE 150

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

boolean ppppDeveSerPuro = true;
int numeroMaximoDeViradinhas = 10;

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
  if(numeroDeViradinhas > numeroMaximoDeViradinhas){
    corrigirViradinha();
  } else {
    if(refletancia.bbbb()){
      numeroDeViradinhas = 0;
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
      acaoPPPP(ppppDeveSerPuro);
    }
  }
}

//Delay usado para o robo voltar ao bbbb no bpbb e bbpb, o mais centralizado possivel.
#define DELAY_VOLTAR_PARA_A_LINHA 60
//Velocidade nos motores 35 - Delay 35

//PB (Esquerda)
void Estrategia::acaoBPBB(){
  robo.ligarLed(1);
  numeroDeViradinhas++;
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
  robo.ligarLed(2);
  numeroDeViradinhas++;
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
void Estrategia::acaoPPPP(boolean veioPuro){
  if(veioPuro){
    ppppDeveSerPuro = true;
    motores.frear();
  }
  toy.ledsAlerta(3);
  motores.pararAteBotao1();
}

//Métodos de Transição PB - PPBB
void Estrategia::alinhamentoBPBB(){ //Se acharmos uma encruzilhada enquanto PB entramos nesse método
  motores.pararPor(DELAY_INTERVALOS);
  if(verificarVerdeParado()){ //Se já encontrou um verde parado
    return; //Já fez o que devia fazer
  }
  if(miniVaiVerificaVerdeVolta() == true){ //Se já encontrou um verde indo e voltando
    return; //Já fez o que tinha que fazer
  }
  if(vaiVerificaVerdeVolta() == true){ //Se já encontrou um verde indo e voltando
    return; //Já fez o que tinha que fazer
  }
  //Faz o sensor mais direito voltar para o branco
  if(refletancia.sensorMaisDir('P')){
    while(refletancia.sensorMaisDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  //Faz o sensor mais esquerdo voltar para o branco
  if(refletancia.sensorMaisEsq('P')){
    while(refletancia.sensorMaisEsq('P')){
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  } else {
    while(refletancia.sensorMaisEsq('B')){
      motores.virarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
    while(refletancia.sensorMaisEsq('P')){
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  //Se quando voltar, o robô vê todos branco, então não tem verde e deve voltar ao seguir linha.
  //Nesse caso, ele deve encontrar PPPP ou PPBB puro (Diretamente)
  if(refletancia.bbbb()){
    ppppDeveSerPuro = false;
    return;
  }

  //Tratando caso caia no pppb ou bppp
  if(refletancia.pppb()){
    toy.selecionarLedsAlerta(true, false, true, 3);
    while(refletancia.sensorMaisEsq('P')){
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  } else if(refletancia.bppp()){
    toy.selecionarLedsAlerta(true, false, true, 3);
    while(refletancia.sensorMaisDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  if(refletancia.bppb()){
    while(refletancia.sensorDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  robo.desligarTodosLeds();
  refletancia.comoEstaoMeusSensores();
  motores.pararAteBotao1();
}
void Estrategia::alinhamentoBBPB(){ //Se acharmos uma encruzilhada enquanto BP entramos nesse método
  motores.pararPor(DELAY_INTERVALOS);
  if(verificarVerdeParado()){ //Se já encontrou um verde parado
    return; //Já fez o que devia fazer
  }
  if(miniVaiVerificaVerdeVolta() == true){ //Se já encontrou um verde indo e voltando
    return; //Já fez o que tinha que fazer
  }
  if(vaiVerificaVerdeVolta() == true){ //Se já encontrou um verde indo e voltando
    return; //Já fez o que tinha que fazer
  }

  //Faz o sensor mais esquerdo voltar para o branco
  while(refletancia.sensorMaisEsq('P')){
    motores.voltarEsq();
  }
  motores.pararPor(DELAY_INTERVALOS);

  //Faz o sensor mais direito voltar para o branco
  if(refletancia.sensorMaisDir('P')){
    while(refletancia.sensorMaisDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  } else {
    while(refletancia.sensorMaisDir('B')){
      motores.virarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
    while(refletancia.sensorMaisDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  motores.pararPor(DELAY_INTERVALOS);

  //Se quando voltar, o robô vê todos branco, então não tem verde e deve voltar ao seguir linha.
  //Nesse caso, ele deve encontrar PPPP ou BBPP puro (Diretamente)
  if(refletancia.bbbb()){
    ppppDeveSerPuro = false;
    return;
  }

  //Tratando caso caia no pppb ou bppp
  if(refletancia.pppb()){
    toy.selecionarLedsAlerta(true, false, true, 3);
    while(refletancia.sensorMaisEsq('P')){
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  } else if(refletancia.bppp()){
    toy.selecionarLedsAlerta(true, false, true, 3);
    while(refletancia.sensorMaisDir('P')){
      motores.voltarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }

  if(refletancia.bppb()){
    while(refletancia.sensorEsq('P')){
      motores.voltarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }


  robo.desligarTodosLeds();
  refletancia.comoEstaoMeusSensores();
  motores.pararAteBotao1();
}

//Métodos de Verificação do verde
boolean Estrategia::verificarVerdeParado(){
  boolean resposta = false;

  motores.parar();

  boolean verdeEsqEncontrado = false;
  boolean verdeDirEncontrado = false;

  if(cor.verificarVerdeEsq()){
    toy.ligarApenasLed(3);
    verdeEsqEncontrado = true;
  }

  if(cor.verificarVerdeDir()){
    toy.ligarApenasLed(3);
    verdeDirEncontrado = true;
  }

  if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Verde - Não Verde (Esquerda)
    //Virar para Esq
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Não Verde - Não Verde (Direita) {
    //Virar para Dir
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == true){ //Verde- Verde (Retorar)
    //Retornar
    resposta = true;
  } else {
    resposta = false;
  }

  motores.pararAteBotao1();
  return resposta;
}
boolean Estrategia::vaiVerificaVerdeVolta(){
  boolean resposta = false;

  motores.mandarParaFrente(DELAY_VAI_VERIFICA_VERDE_VOLTA);
  motores.frearPor(DELAY_VAI_VERIFICA_VERDE_VOLTA);

  boolean verdeEsqEncontrado = false;
  boolean verdeDirEncontrado = false;

  if(cor.verificarVerdeEsq()){
    toy.ligarApenasLed(3);
    verdeEsqEncontrado = true;
  }

  if(cor.verificarVerdeDir()){
    toy.ligarApenasLed(3);
    verdeDirEncontrado = true;
  }

  if(verdeEsqEncontrado == false && verdeDirEncontrado == false){ //Não Verde - Não Verde (Voltar)
    //Não tem verde
    motores.voltar();
    delay(DELAY_VAI_VERIFICA_VERDE_VOLTA);
    motores.frearVoltar();
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Verde - Não Verde (Esquerda)
    //Virar para Esq
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Não Verde - Não Verde (Direita) {
    //Virar para Dir
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == true){ //Verde- Verde (Retorar)
    resposta = true;
  }
  motores.pararAteBotao1();
  return resposta;
}
boolean Estrategia::miniVaiVerificaVerdeVolta(){
  boolean resposta = false;

  motores.mandarParaFrente(DELAY_MINI_VAI_VERIFICA_VERDE_VOLTA);
  motores.frearPor(DELAY_MINI_VAI_VERIFICA_VERDE_VOLTA);

  boolean verdeEsqEncontrado = false;
  boolean verdeDirEncontrado = false;

  if(cor.verificarVerdeEsq()){
    toy.ligarApenasLed(3);
    verdeEsqEncontrado = true;
  }

  if(cor.verificarVerdeDir()){
    toy.ligarApenasLed(3);
    verdeDirEncontrado = true;
  }

  if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Verde - Não Verde (Esquerda)
    //Virar para Esq
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Não Verde - Não Verde (Direita) {
    //Virar para Dir
    resposta = true;
  } else if (verdeEsqEncontrado == true && verdeDirEncontrado == true){ //Verde- Verde (Retorar)
    resposta = true;
  }

  motores.pararAteBotao1();
  return resposta;
}
boolean Estrategia::avancarVerificarVerde(int numeroDeAvancos){
  boolean resposta = false;

  for(int avanco = 0; avanco <= numeroDeAvancos; avanco++){
    motores.mandarParaFrente(DELAY_AVANCA_VERIFICA_VERDE);
    motores.frearPor(DELAY_AVANCA_VERIFICA_VERDE);

    boolean verdeEsqEncontrado = false;
    boolean verdeDirEncontrado = false;

    if(cor.verificarVerdeEsq()){
      toy.ligarApenasLed(3);
      verdeEsqEncontrado = true;
    }

    if(cor.verificarVerdeDir()){
      toy.ligarApenasLed(3);
      verdeDirEncontrado = true;
    }

    if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Verde - Não Verde (Esquerda)
      //Virar para Esq
      resposta = true;
      break;
    } else if (verdeEsqEncontrado == true && verdeDirEncontrado == false){ //Não Verde - Não Verde (Direita)
      //Virar para Dir
      resposta = true;
      break;
    } else if (verdeEsqEncontrado == true && verdeDirEncontrado == true){ //Verde- Verde (Retorar)
      resposta = true;
      break;
    } else {
      resposta = false;
    }
  }
  return resposta;
}

//Métodos de Tratamento de erro
void Estrategia::corrigirViradinha(){
  motores.pararPor(DELAY_INTERVALOS);
  
  robo.desligarTodosLeds();
  for(int i = 0; i <= 3; i++){
    toy.ligarApenasLed(1);
    delay(100);
    toy.ligarApenasLed(2);
    delay(100);
  }
  robo.ligarLed(1);
  robo.ligarLed(2);

  delay(DELAY_INTERVALOS);
  robo.desligarTodosLeds();

  if(refletancia.sensorDir('P')){
    while(refletancia.sensorDir('P')){
      motores.virarDir();
    }
    motores.pararPor(DELAY_INTERVALOS);
    if(verificarVerdeParado()){
      robo.ligarLed(3);
      delay(DELAY_INTERVALOS);
      return;
    }
    if(miniVaiVerificaVerdeVolta()){
      return;
    }
  } else if(refletancia.sensorEsq('P')){
    while(refletancia.sensorEsq('P')){
      motores.virarEsq();
    }
    motores.pararPor(DELAY_INTERVALOS);
    if(verificarVerdeParado()){
      robo.ligarLed(3);
      delay(DELAY_INTERVALOS);
      return;
    }
    if(miniVaiVerificaVerdeVolta()){
      return;
    }  
  }

  if(refletancia.bbbb()){
    while(refletancia.sensorMaisDir('B') || refletancia.sensorMaisEsq('B')){
      motores.voltar();
    }
    motores.pararPor(DELAY_INTERVALOS);
  }



  refletancia.comoEstaoMeusSensores();

  motores.pararAteBotao1();
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

