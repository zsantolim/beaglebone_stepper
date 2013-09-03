#include "StepperMotor.h"

void StepperMotor_setup(StepperMotor* motor) {
	int port, pin;	
	// Initializes the ports and pins needed
	// Pin gpioA1
	port	= motor->gpioA1 / 32;
	pin		= motor->gpioA1 % 32;
	gpio_setup(port,pin,OUTPUT);
	// Pin gpioA2
	port	= motor->gpioA2 / 32;
	pin		= motor->gpioA2 % 32;
	gpio_setup(port,pin,OUTPUT);
	// Pin gpioB1
	port	= motor->gpioB1 / 32;
	pin		= motor->gpioB1 % 32;
	gpio_setup(port,pin,OUTPUT);
	// Pin gpioB2
	port	= motor->gpioB2 / 32;
	pin		= motor->gpioB2 % 32;
	gpio_setup(port,pin,OUTPUT);
	
	// Initializes the state
	motor->state = 0;
}

void StepperMotor_step(StepperMotor* motor, int steps) {
	float stepsPerRev, periodPerStep;
	long int uPeriodPerStep;
	int direction, stepsCount;
	// Calculates the number of steps for one revolution
	stepsPerRev = (360.0 / (motor->stepSize));				// Steps per revolution
	periodPerStep = (60.0 / (stepsPerRev * motor->speed));	// Period per step, based on the Steps Per Revolution and the Motor Speed
	uPeriodPerStep = (long int) (periodPerStep * 1000000);	// Period per step in microseconds
	
	if (steps > 0) {
		direction = 1;
		stepsCount = steps;
	} else if (steps < 0) {
		direction = 0;
		stepsCount = -steps;
	} else return;
	
	while (stepsCount) {
		switch (motor->state) {
			case STEPPER_STATE_A:
				gpio_write((motor->gpioA1)/32,(motor->gpioA1)%32,1);
				gpio_write((motor->gpioA2)/32,(motor->gpioA2)%32,0);
				gpio_write((motor->gpioB1)/32,(motor->gpioB1)%32,0);
				gpio_write((motor->gpioB2)/32,(motor->gpioB2)%32,1);
				break;
			case STEPPER_STATE_B:
				gpio_write((motor->gpioA1)/32,(motor->gpioA1)%32,0);
				gpio_write((motor->gpioA2)/32,(motor->gpioA2)%32,1);
				gpio_write((motor->gpioB1)/32,(motor->gpioB1)%32,0);
				gpio_write((motor->gpioB2)/32,(motor->gpioB2)%32,1);
				break;
			case STEPPER_STATE_C:
				gpio_write((motor->gpioA1)/32,(motor->gpioA1)%32,0);
				gpio_write((motor->gpioA2)/32,(motor->gpioA2)%32,1);
				gpio_write((motor->gpioB1)/32,(motor->gpioB1)%32,1);
				gpio_write((motor->gpioB2)/32,(motor->gpioB2)%32,0);			
				break;
			case STEPPER_STATE_D:
				gpio_write((motor->gpioA1)/32,(motor->gpioA1)%32,1);
				gpio_write((motor->gpioA2)/32,(motor->gpioA2)%32,0);
				gpio_write((motor->gpioB1)/32,(motor->gpioB1)%32,1);
				gpio_write((motor->gpioB2)/32,(motor->gpioB2)%32,0);
				break;
			default:
				return;
				break;
		}
		if (direction) {
			motor->state++;
			motor->state %= 4;
		} else {
			if (motor->state) motor->state--;
			else motor->state = STEPPER_STATE_D;
		}
		stepsCount--;
		usleep(uPeriodPerStep);
	}
	
}