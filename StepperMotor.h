#ifndef _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

#define STEPPER_STATE_A		0
#define STEPPER_STATE_B		1
#define STEPPER_STATE_C		2
#define STEPPER_STATE_D		3

typedef struct StepperMotor {
	int	state;		// Motor sequence state
	int gpioA1;		// GPIO number for positive side of the first winding
	int gpioA2;		// GPIO number for negative side of the first winding
	int gpioB1;		// GPIO number for positive side of the second winding
	int gpioB2;		// GPIO number for negative side of the second winding
	float stepSize;	// The step size in degrees for this Stepper Motor
	int speed;		// The desired RPM speed for the Stepper Motor
} StepperMotor_t;

void StepperMotor_setup(StepperMotor* motor);
void StepperMotor_step(StepperMotor* motor, int steps);

#endif