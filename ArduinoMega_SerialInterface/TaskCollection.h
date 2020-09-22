#ifndef TASKCOLLECTION_H_
#define TASKCOLLECTION_H_

#include "LifeLedTask.h"
#include "SerialTask.h"
#include "fightingTasks.h"


#define TaskCount 2		//Should match the User created Task Count


#define SystemTasks 2		// Dont change!
#define TaskEntrySize = 40	// Dont Change!

#define tskList_TOTALSize = (int)((TaskCount + SystemTasks) * TaskEntrySize)


#endif

