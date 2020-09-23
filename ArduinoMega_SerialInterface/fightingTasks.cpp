// 
// 
// 

#include "fightingTasks.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "shiftPort.h"

void prvTask1(void* pvParameters);


shiftPort port(22,24,23);

void Init()
{
	
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
		i = 0;
		for(;i< 256;i++)
		{
			port.Write(i);
			vTaskDelay(50 / portTICK_PERIOD_MS );
		}
		for(;i>= 0;i--)
		{
			port.Write(i);
			vTaskDelay(50 / portTICK_PERIOD_MS);
		}
	}
}




