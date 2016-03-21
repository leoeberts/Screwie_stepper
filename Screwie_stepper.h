/*
  Screwie_stepper.h - Biblioteca para controle de passos do Screwie.
  Released into the public domain.
*/
#ifndef Screwie_stepper_h
#define Screwie_stepper_h

#include "Arduino.h"

extern const byte fullStep[];
extern const byte doubleStep[];

enum Direcao {
  FRENTE,
  TRAS
};

enum TipoPasso {
  MEIO_PASSO,
  PASSO_INTEIRO,
  PASSO_DUPLO
};

class Screwie_stepper
{
  public:
    Screwie_stepper(uint8_t bobinas[4]);
    void passo(int numeroDePassos, int velocidade, Direcao direcao);
    void passo(int numeroDePassos, int velocidade, TipoPasso tipoPasso, Direcao direcao);    

  private:
    uint8_t bobinasMotor[4];
    int passoMotor;

    void inicializaSaidaParaBobina(uint8_t bobinas[4]);
    void meioPasso(int numeroDePassos, int velocidade, Direcao direcao);
    void passoInteiro(int numeroDePassos, int velocidade, Direcao direcao);
    void passoDuplo(int numeroDePassos, int velocidade, Direcao direcao);
    void fullStepParaFrente(int numeroDePassos, int velocidade);
    void fullStepParaTras(int numeroDePassos, int velocidade);
    void doubleStepParaFrente(int numeroDePassos, int velocidade);
    void doubleStepParaTras(int numeroDePassos, int velocidade);
    void halfStepParaFrente(int numeroDePassos,int velocidade);
    void halfStepParaTras(int numeroDePassos, int velocidade);
    void executaPassoMotorFrente(const byte configuracoesPassos[]);
    void executaPassoMotorTras(const byte configuracoesPassos[]);
    void executaMovimentoParaFrente(byte configuracao);
    void executaMovimentoParaTras(byte configuracao);
    void avancaPasso();
    void recuaPasso();
};

#endif
