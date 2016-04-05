/*
  Screwie_stepper.h - Controls one stepper motor.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Screwie_stepper.h"
#include "Screwie_motorCommand.h"

const byte fullStep[] = {
	B1000, // First step
	B0010, // Second step
	B0100, // Third step
	B0001, // Fourth step
};
	
const byte doubleStep[] = {
	B1010, // First step
	B0110, // Second step
	B0101, // Third step
	B1001, // Fourth step
};

Screwie_stepper::Screwie_stepper(uint8_t coils[4]) {
  actualStep = 0;
  initCoilsPins(coils);
}

void Screwie_stepper::initCoilsPins(uint8_t coils[4]) {
  for (int coil = 0 ; coil < 4 ; coil++) {
	motorCoils[coil] = coils[coil];
    pinMode(motorCoils[coil], OUTPUT);
  }
}

void Screwie_stepper::executeCommand(Screwie_motorCommand command) {
  switch (command.getStepType()) {
        case HALF_STEP:
            executeHalfStep(command);
            break;
        case DOUBLE_STEP:
            executeDoubleStep(command);
            break;
        default : //Full step
            executeFullStep(command);
    }
}

void Screwie_stepper::executeHalfStep(Screwie_motorCommand command) {
  switch (command.getDirection()) {
        case BACKWARDS:
            executeHalfStepBackward(command);
            break;
        default : //Half step forward 
            executeHalfStepForward(command);
    }
}

void Screwie_stepper::executeFullStep(Screwie_motorCommand command) {
  switch (command.getDirection()) {
        case BACKWARDS:
            executeFullStepBackward(command);
            break;
        default : //Full step forward 
            executeFullStepForward(command);
    }
}

void Screwie_stepper::executeDoubleStep(Screwie_motorCommand command) {
  switch (command.getDirection()) {
        case BACKWARDS:
            executeDoubleStepBackward(command);
            break;
        default : //Double step forward 
            executeDoubleStepForward(command);
    }
}

void Screwie_stepper::executeFullStepForward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum++) {
    executeStepForward(fullStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeFullStepBackward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum++) {
    executeStepBackward(fullStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeDoubleStepForward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum++) {
    executeStepForward(doubleStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeDoubleStepBackward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum++) {
    executeStepBackward(doubleStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeHalfStepForward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum = stepNum + 2) {
    executeStepForward(fullStep);
    delay(command.getSpeed());
    decrementStep();
    executeStepForward(doubleStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeHalfStepBackward(Screwie_motorCommand command) {
  for ( int stepNum = 0; stepNum < command.getNumberOfSteps(); stepNum = stepNum + 2) {
    executeStepBackward(fullStep);
    delay(command.getSpeed());
    incrementStep();
    executeStepBackward(doubleStep);
    delay(command.getSpeed());
  }
}

void Screwie_stepper::executeStepForward(const byte stepConfiguration[]) {
  byte configuration = stepConfiguration[actualStep];
  executeMovementForward(configuration);
  incrementStep();
}

void Screwie_stepper::executeStepBackward(const byte stepConfiguration[]) {
  byte configuration = stepConfiguration[actualStep];
  executeMovementBackward(configuration);
  decrementStep();
}

void Screwie_stepper::executeMovementForward(byte configuration) {
  for (byte coil = 0 ; coil < 4 ; coil++) {
    if (configuration & (1 << coil)) {
      digitalWrite(motorCoils[coil], HIGH);
    } else {
      digitalWrite(motorCoils[coil], LOW);
    }
  }
}

void Screwie_stepper::executeMovementBackward(byte configuration) {
  for (byte coil = 0 ; coil < 4 ; coil++) {
    if (configuration & (1 << coil)) {
      digitalWrite(motorCoils[coil], LOW);
    } else {
      digitalWrite(motorCoils[coil], HIGH);
    }
  }
}

void Screwie_stepper::incrementStep() {
  if (actualStep == 3) {
    actualStep = 0;
  } else {
    actualStep++;
  }
}

void Screwie_stepper::decrementStep() {
  if (actualStep == 0) {
    actualStep = 3;
  } else {
    actualStep--;
  }
}

