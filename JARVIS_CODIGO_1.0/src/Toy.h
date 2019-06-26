/*
 * Classe para a Utilização de sequenias dos Leds para o shield_mega_seed4_mpu_lobo5
 * By: DuduCMT
 * -------------------------------------------
 * ligarLed(int) 
 *    Função: Liga o Led
 *    Parametros: Número do Led no Shild (1, 2 ou 3)
 *    
 * desligarLed(int)
 *    Função:  - Desliga o Led
 *    Parametros: Número do Led no Shild (1, 2 ou 3)
 *    
 * desligaLigaLed(int)
 *    Função: Desliga o Led e liga depois de 300ms
 *    Parametros: Número do Led no Shild (1, 2 ou 3)
 *    
 * ligarApenasLed(int);
 *    Função:
 *    Parametros:
 * 
 * nome(int);
 *    Função:
 *    Parametros:
 * 
 * nome(int);
 *    Função:
 *    Parametros:
 * 
 * nome(int);
 *    Função:
 *    Parametros:
 */


#ifndef TOY_H
#define TOY_H

#include <Arduino.h>
#include <robo_hardware2.h>
#include <Servo.h>

class Toy{
  public:
    Toy();
    void ligarLed(int); //Número do Led
    //Liga o Led
    
    void desligarLed(int); //Número do Led
    //Desliga o Led

    void desligaLigaLed(int); //Número do Led
    //Desliga o Led por 300ms, após isso o led é Ligado
    
    void ligarApenasLed(int);
    
    void ligarLeds();
    //Liga todos os Leds
    
    void desligarLeds();
    //Desliga todos os Leds
    
    void ledsEscada(int, int); //Quantidade de Repetições, Tempo de ligação entre cada Led 
    //Liga todos os Leds em sequência
    
    void ledsAlerta(int); //Quantidade de Repedições
    //Liga e Desliga todos os Leds

    
    void ledAlerta(int, int, int); //Número do Led, Quantidade de Repetições, Tempo entre cada Liga-Desliga
    //Liga e Desliga um Leds em expecifico
};

#endif
