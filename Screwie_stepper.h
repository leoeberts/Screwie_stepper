/*
  Screwie_stepper.h - Controls one stepper motor.
  Released into the public domain.
*/
#ifndef Screwie_stepper_h
#define Screwie_stepper_h

#include "Arduino.h"
#include "Screwie_motorCommand.h"

extern const byte fullStep[];
extern const byte doubleStep[];

class Screwie_stepper
{
  public:
    Screwie_stepper(uint8_t coils[4]);
    void executeCommand(Screwie_motorCommand command);    

  private:
    uint8_t motorCoils[4];
    int actualStep;

    void initCoilsPins(uint8_t coils[4]);	
	void executeHalfStep(Screwie_motorCommand command);
	void executeFullStep(Screwie_motorCommand command);
	void executeDoubleStep(Screwie_motorCommand command);
	void executeFullStepForward(Screwie_motorCommand command);
	void executeFullStepBackward(Screwie_motorCommand command);
	void executeDoubleStepForward(Screwie_motorCommand command);
	void executeDoubleStepBackward(Screwie_motorCommand command);
	void executeHalfStepForward(Screwie_motorCommand command);
	void executeHalfStepBackward(Screwie_motorCommand command);
	void executeStepForward(const byte stepConfiguration[]);
	void executeStepBackward(const byte stepConfiguration[]);
	void executeMovementForward(byte configuration);
	void executeMovementBackward(byte configuration);
	void incrementStep();
	void decrementStep();
};

#endif
