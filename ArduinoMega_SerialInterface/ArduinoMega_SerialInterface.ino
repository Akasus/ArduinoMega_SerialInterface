/*
 Name:		ArduinoMega_SerialInterface.ino
 Created:	19.09.2020 15:23:42
 Author:	Akasu
*/

//includes
#include "TaskCollection.h"

// the setup function runs once when you press reset or power the board
void setup() {

	StartSerialTask();
	StartLifeLedTask();
	StartFightingTasks();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
