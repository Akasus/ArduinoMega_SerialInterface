// 
// 
// 

#include "LifeLedTask.h"

void prvLifeLedTask(void* pvParameters);


void StartLifeLedTask()
{
	xTaskCreate(prvLifeLedTask, "LedTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
}


void prvLifeLedTask(void* pvParameters)
{
	(void)pvParameters;
	pinMode(LED_BUILTIN, OUTPUT);
	TickType_t shortDelay = 250u /portTICK_PERIOD_MS ;
	TickType_t longDelay = 500u /portTICK_PERIOD_MS;

	for(;;)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		vTaskDelay(shortDelay);
		digitalWrite(LED_BUILTIN, LOW);
		vTaskDelay(shortDelay);
		digitalWrite(LED_BUILTIN, HIGH);
		vTaskDelay(shortDelay);
		digitalWrite(LED_BUILTIN, LOW);
		vTaskDelay(longDelay);
	}

	
}






