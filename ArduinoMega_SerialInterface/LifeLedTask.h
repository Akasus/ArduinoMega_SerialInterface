// LifeLedTask.h

#ifndef _LIFELEDTASK_h
#define _LIFELEDTASK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Arduino_FreeRTOS.h"
#include "stdint.h"


void StartLifeLedTask();



#endif

