/*
  Screwie_stepper.h - Biblioteca para controle de passos do Screwie.
  Released into the public domain.
*/
#ifndef Screwie_stepper_h
#define Screwie_stepper_h

#include "Arduino.h"

enum Direcao {
  FRENTE,
  TRAS
};

enum TipoPasso {
  MEIO_PASSO,
  PASSO_INTEIRO,
  PASSO_DUPLO
}

class Screwie_stepper
{
  public:
    Screwie_stepper(byte bobinas[]);
    void passo(int numeroDePassos, int velocidade, Direcao direcao);
    void passo(int numeroDePassos, int velocidade, TipoPasso tipoPasso, Direcao direcao);    

  private:
    byte bobinasMotor[];
    int passoMotor;

    static byte fullStep[];
    static byte doubleStep[];

    void inicializaSaidaParaBobina(byte bobinasMotor[]);
    void meioPasso(int numeroDePassos, int velocidade, Direcao direcao);
    void passoInteiro(int numeroDePassos, int velocidade, Direcao direcao);
    void passoDuplo(int numeroDePassos, int velocidade, Direcao direcao);
    void fullStepParaFrente(int numeroDePassos, int velocidade);
    void fullStepParaTras(int numeroDePassos, int velocidade);
    void doubleStepParaFrente(int numeroDePassos, int velocidade);
    void doubleStepParaTras(int numeroDePassos, int velocidade);
    void halfStepParaFrente(int numeroDePassos,int velocidade);
    void halfStepParaTras(int numeroDePassos, int velocidade);
    void executaPassoMotorFrente(byte configuracoesPassos[]);
    void executaPassoMotorTras(byte configuracoesPassos[]);
    void executaMovimentoParaFrente(byte configuracao);
    void executaMovimentoParaTras(byte configuracao);
    void avancaPasso();
    void recuaPasso();
};

#endif
