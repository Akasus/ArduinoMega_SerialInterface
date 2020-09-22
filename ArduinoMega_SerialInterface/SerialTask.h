// SerialTask.h

#ifndef _SERIALTASK_h
#define _SERIALTASK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "stdint.h"
#include "Arduino_FreeRTOS.h"

void StartSerialTask();



#endif

