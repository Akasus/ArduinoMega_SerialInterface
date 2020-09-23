// SerialPinManager.h

#ifndef _SERIALPINMANAGER_h
#define _SERIALPINMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void Pin_Command(String raw_input);



#endif

