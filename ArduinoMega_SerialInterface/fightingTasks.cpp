// 
// 
// 

#include "fightingTasks.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "shiftPort.h"

void prvTask1(void* pvParameters);

shiftPort port(4,);
#define data_pin 22
#define clock_pin 24
#define latch_pin 23


void Init()
{
	pinMode(data_pin, OUTPUT);
	pinMode(clock_pin, OUTPUT);
	pinMode(latch_pin, OUTPUT);
}



void StartFightingTasks()
{
	xTaskCreate(prvTask1, "Task1", 160, NULL, 1, NULL);
}

void prvTask1(void* pvParameters)
{
	(void)pvParameters;
	Init();
	int i = 0;
	
	while (1)
	{
		for (int i = 0; i < 24; i++)
		{
			port.SetBit(i, HIGH);
			if (i > 0)
				port.SetBit(i - 1, LOW);
			vTaskDelay(50 / portTICK_PERIOD_MS);
			
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
