/*
  Screwie_stepper.h - Biblioteca para controle de passos do Screwie.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Screwie_stepper.h"

void Screwie_stepper::Screwie_stepper(byte bobinas[]) {
  passoMotor = 0;
  bobinasMotor = bobinas;
  inicializaSaidaParaBobina(bobinasMotor);

  fullStep[] = {
    B1000, // primeiro passo
    B0010, // segundo passo
    B0100, // terceiro passo
    B0001, // quarto passo
  };

  doubleStep[] = {
    B1010, // primeiro passo
    B0110, // segundo passo
    B0101, // terceiro passo
    B1001, // quarto passo
  };
}

void Screwie_stepper::inicializaSaidaParaBobina(byte bobinasMotor[]) {
  for (byte bobina = 0 ; bobina < 4 ; bobina++) {
    pinMode(bobinasMotor[bobina], OUTPUT);
  }
}

void Screwie_stepper::passo(int numeroDePassos, int velocidade, Direcao direcao) {
  passoInteiro(numeroDePassos, velocidade, direcao);
}

void Screwie_stepper::passo(int numeroDePassos, int velocidade, TipoPasso tipoPasso, Direcao direcao) {
  switch (tipoPasso) {
        case MEIO_PASSO:
            meioPasso(numeroDePassos, velocidade, direcao);
            break;
        case PASSO_DUPLO:
            passoDuplo(numeroDePassos, velocidade, direcao);
            break;
        default : //passo inteiro e demais
            passoInteiro(numeroDePassos, velocidade, direcao);
    }
}

void Screwie_stepper::meioPasso(int numeroDePassos, int velocidade, Direcao direcao) {
  switch (direcao) {
        case TRAS:
            halfStepParaTras(numeroDePassos, velocidade);
            break;
        default : //passo inteiro e demais
            halfStepParaDrente(numeroDePassos, velocidade);
    }
}

void Screwie_stepper::passoInteiro(int numeroDePassos, int velocidade, Direcao direcao) {
  switch (direcao) {
        case TRAS:
            fullStepParaTras(numeroDePassos, velocidade);
            break;
        default : //passo inteiro e demais
            fullStepParaFrente(numeroDePassos, velocidade);
    }
}

void Screwie_stepper::passoDuplo(int numeroDePassos, int velocidade, Direcao direcao) {
  switch (direcao) {
        case TRAS:
            doubleStepParaTras(numeroDePassos, velocidade);
            break;
        default : //passo inteiro e demais
            doubleStepParaFrente(numeroDePassos, velocidade);
    }
}

void Screwie_stepper::fullStepParaFrente(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum++) {
    executaPassoMotorFrente(fullStep);
    delay(velocidade);
  }
}

void Screwie_stepper::fullStepParaTras(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum++) {
    executaPassoMotorTras(fullStep);
    delay(velocidade);
  }
}

void Screwie_stepper::doubleStepParaFrente(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum++) {
    executaPassoMotorFrente(doubleStep);
    delay(velocidade);
  }
}

void Screwie_stepper::doubleStepParaTras(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum++) {
    executaPassoMotorTras(doubleStep);
    delay(velocidade);
  }
}

void Screwie_stepper::halfStepParaFrente(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum = stepNum + 2) {
    executaPassoMotorFrente(fullStep);
    delay(velocidade);
    recuaPasso();
    executaPassoMotorFrente(doubleStep);
    delay(velocidade);
  }
}

void Screwie_stepper::halfStepParaTras(int numeroDePassos, int velocidade) {
  for ( int stepNum = 0; stepNum < numeroDePassos; stepNum = stepNum + 2) {
    executaPassoMotorTras(fullStep);
    delay(velocidade);
    avancaPasso();
    executaPassoMotorTras(doubleStep);
    delay(velocidade);
  }
}

void Screwie_stepper::executaPassoMotorFrente(byte configuracoesPassos[]) {
  byte configuracao = configuracoesPassos[passoMotor];
  executaMovimentoParaFrente(configuracao);
  avancaPasso();
}

void Screwie_stepper::executaPassoMotorTras(byte configuracoesPassos[]) {
  byte configuracao = configuracoesPassosDoubleStep[passoMotor];
  executaMovimentoParaTras(configuracao);
  recuaPasso();
}

void Screwie_stepper::executaMovimentoParaFrente(byte configuracao) {
  for (byte bobina = 0 ; bobina < 4 ; bobina++) {
    if (configuracao & (1 << bobina)) {
      digitalWrite(bobinasMotor[bobina], HIGH);
    } else {
      digitalWrite(bobinasMotor[bobina], LOW);
    }
  }
}

void Screwie_stepper::executaMovimentoParaTras(byte configuracao) {
  for (byte bobina = 0 ; bobina < 4 ; bobina++) {
    if (configuracao & (1 << bobina)) {
      digitalWrite(bobinasMotor[bobina], LOW);
    } else {
      digitalWrite(bobinasMotor[bobina], HIGH);
    }
  }
}

void Screwie_stepper::avancaPasso() {
  if (passoMotor == 3) {
    passoMotor = 0;
  } else {
    passoMotor++;
  }
}

void Screwie_stepper::recuaPasso() {
  if (passoMotor == 0) {
    passoMotor = 3;
  } else {
    passoMotor--;
  }
}

