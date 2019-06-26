#include <robo_hardware2.h>
#include <Servo.h>
#include "MenuIniciar.h"
#include "Estrategia.h"
#include "Calibragem.h"

MenuIniciar menuIniciar;
Estrategia estrategia;
Calibragem calibragem;

void setup() {
  Serial.begin(9600);
  robo.configurar(false);
  robo.habilitaTCS34();

  calibragem.printDadosEEPROM();
  menuIniciar.menuBotoes();
}

void loop() {
  if(menuIniciar.calibragem.voltarMenu){
    Serial.println(F("Voltando para Menu Botões..."));
    menuIniciar.calibragem.voltarMenu = false;
    menuIniciar.menuBotoes();
  }
  estrategia.executar();
}
