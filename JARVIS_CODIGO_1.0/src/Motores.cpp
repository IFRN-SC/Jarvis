#include "Motores.h"

#define DIFERENCA 3

#define DIR_POSITIVO 28
#define DIR_NEGATIVO -28
#define ESQ_POSITIVO (DIR_POSITIVO + DIFERENCA)
#define ESQ_NEGATIVO (DIR_NEGATIVO - DIFERENCA)


#define DIR_POSITIVO_DEVAGAR 27
#define DIR_NEGATIVO_DEVAGAR -27
#define ESQ_POSITIVO_DEVAGAR (DIR_POSITIVO_DEVAGAR + DIFERENCA)
#define ESQ_NEGATIVO_DEVAGAR (DIR_POSITIVO_DEVAGAR - DIFERENCA)

#define DIR_POSITIVO_90_GRAUS 40
#define DIR_NEGATIVO_90_GRAUS -40
#define ESQ_POSITIVO_90_GRAUS (DIR_POSITIVO_90_GRAUS + DIFERENCA)
#define ESQ_NEGATIVO_90_GRAUS (DIR_POSITIVO_90_GRAUS - DIFERENCA)

#define DIR_POSITIVO_DIFERENTE 45
#define DIR_NEGATIVO_DIFERENTE -40
#define ESQ_POSITIVO_DIFERENTE (DIR_POSITIVO_DIFERENTE + DIFERENCA)
#define ESQ_NEGATIVO_DIFERENTE (DIR_POSITIVO_DIFERENTE - DIFERENCA)

#define DIR_POSITIVO_FREIO 40
#define DIR_NEGATIVO_FREIO -40
#define ESQ_POSITIVO_FREIO (DIR_POSITIVO_FREIO + DIFERENCA)
#define ESQ_NEGATIVO_FREIO (DIR_NEGATIVO_FREIO - DIFERENCA)

#define DELAY_90_GRAUS 260
#define DELAY_FREIO 43

#define POSITIVO_FRENTE_CURVA 25
#define DELAY_FRENTE_CURVA 100

Motores::Motores(){
  //
}

//Movimentos com Valores Padrões
void Motores::frente(){robo.acionarMotores(ESQ_POSITIVO, DIR_POSITIVO);}
void Motores::voltar(){robo.acionarMotores(ESQ_NEGATIVO, DIR_NEGATIVO);}
void Motores::parar(){robo.acionarMotores(0, 0);}
void Motores::frear(){
  robo.acionarMotores(ESQ_NEGATIVO_FREIO, DIR_NEGATIVO_FREIO);
  delay(DELAY_FREIO);
  parar();
}
void Motores::girarEsq(){robo.acionarMotores(ESQ_NEGATIVO, DIR_POSITIVO);}
void Motores::girarDir(){robo.acionarMotores(ESQ_POSITIVO, DIR_NEGATIVO);}
void Motores::virarEsq(){robo.acionarMotores(0, DIR_POSITIVO);}
void Motores::virarDir(){robo.acionarMotores(ESQ_POSITIVO, 0);}
void Motores::voltarEsq(){robo.acionarMotores(ESQ_NEGATIVO, 0);}
void Motores::voltarDir(){robo.acionarMotores(0, DIR_NEGATIVO);}

//Movimentos Devagar
void Motores::frenteDevagar(){robo.acionarMotores(ESQ_POSITIVO_DEVAGAR, DIR_POSITIVO_DEVAGAR);}
void Motores::voltarDevagar(){robo.acionarMotores(ESQ_NEGATIVO_DEVAGAR, DIR_NEGATIVO_DEVAGAR);}
void Motores::frearDevagar(){
  robo.acionarMotores(ESQ_NEGATIVO_DEVAGAR, DIR_NEGATIVO_DEVAGAR);
  delay(DELAY_FREIO);
  parar();
}
void Motores::girarDevagarEsq(){robo.acionarMotores(ESQ_NEGATIVO_DEVAGAR, DIR_POSITIVO_DEVAGAR);}
void Motores::girarDevagarDir(){robo.acionarMotores(ESQ_POSITIVO_DEVAGAR, DIR_NEGATIVO_DEVAGAR);}
void Motores::virarDevagarEsq(){robo.acionarMotores(0, DIR_POSITIVO_DEVAGAR);}
void Motores::virarDevagarDir(){robo.acionarMotores(ESQ_POSITIVO_DEVAGAR, 0);}
void Motores::voltarDevagarEsq(){robo.acionarMotores(ESQ_NEGATIVO_DEVAGAR, 0);}
void Motores::voltarDevagarDir(){robo.acionarMotores(0, DIR_NEGATIVO_DEVAGAR);}

//Movimentos Diferentes
void Motores::giroDiferenteDir(){robo.acionarMotores(ESQ_POSITIVO_DIFERENTE, DIR_NEGATIVO_DIFERENTE);}
void Motores::giroDiferenteEsq(){robo.acionarMotores(ESQ_NEGATIVO_DIFERENTE, DIR_POSITIVO_DIFERENTE);}


//Movimentos de 90 Graus
void Motores::girar90Esq(){
  robo.acionarMotores(ESQ_NEGATIVO_90_GRAUS, DIR_POSITIVO_90_GRAUS);
  delay(DELAY_90_GRAUS);
}
void Motores::girar90Dir(){
  robo.acionarMotores(ESQ_POSITIVO_90_GRAUS, DIR_NEGATIVO_90_GRAUS);
  delay(DELAY_90_GRAUS);
}

void Motores::acaoRedutor(){
  parar();
  delay(500);
  voltarDevagar();
  delay(500);
  parar();
  delay(500);
  frente();
  delay(1000);
}

//Movimento de Freios
void Motores::frearGiroEsq(){
  robo.acionarMotores(ESQ_POSITIVO_FREIO, DIR_NEGATIVO_FREIO);
  delay(DELAY_FREIO);
  parar();
}
void Motores::frearGiroDir(){
  robo.acionarMotores(ESQ_NEGATIVO_FREIO, DIR_POSITIVO_FREIO);
  delay(DELAY_FREIO);
  parar();
}
void Motores::frearVirarEsq(){
  robo.acionarMotores(0, DIR_POSITIVO_FREIO);
  delay(DELAY_FREIO);
  parar();  
}
void Motores::frearVirarDir(){
  robo.acionarMotores(ESQ_POSITIVO_FREIO, 0);
  delay(DELAY_FREIO);
  parar();
}
void Motores::frearVoltarEsq(){
  robo.acionarMotores(ESQ_POSITIVO_FREIO, 0);
  delay(DELAY_FREIO);
  parar();
}
void Motores::frearVoltarDir(){
  robo.acionarMotores(0, DIR_POSITIVO_FREIO);
  delay(DELAY_FREIO);
  parar();
}
void Motores::frarVoltar(){
  robo.acionarMotores(ESQ_POSITIVO_FREIO, DIR_POSITIVO_FREIO);
  delay(DELAY_FREIO);
  parar();
}

//Movimentos Especificos
void Motores::frenteCurva(){
  robo.acionarMotores(POSITIVO_FRENTE_CURVA, POSITIVO_FRENTE_CURVA);
  delay(DELAY_FRENTE_CURVA);
}

void Motores::pararPor(int segundos){
  parar();
  delay(segundos);
}

void Motores::frearPor(int segundos){
  frear();
  delay(segundos);
}

void Motores::pararAteBotao1(){
  parar();
  while(!robo.botao1Pressionado()){}
  toy.ledsAlerta(3);
}

