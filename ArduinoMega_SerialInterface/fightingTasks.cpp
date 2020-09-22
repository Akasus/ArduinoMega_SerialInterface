// 
// 
// 

#include "fightingTasks.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"

void prvTask1(void* pvParameters);
void prvTask2(void* pvParameters);

static TaskHandle_t Task1handle;
static TaskHandle_t Task2handle;


void StartFightingTasks()
{
	xTaskCreate(prvTask1, "Task1", 160, NULL, 2, &Task1handle);
}

void prvTask1(void* pvParameters)
{
	if (Task2handle != NULL)
		vTaskDelete(Task2handle);
	
	(void)pvParameters;
	vTaskDelay(500 / portTICK_PERIOD_MS);
	xTaskCreate(prvTask2, "Task2", 160, NULL, 1, &Task2handle);
	int i = 0;

	while (i < 20000) i++;

	vTaskDelay(100 / portTICK_PERIOD_MS);
	vTaskDelete(Task1handle);
	
}

void prvTask2(void* pvParameters)
{
	(void)pvParameters;
	if (Task1handle != NULL)
		vTaskDelete(Task1handle);

	vTaskDelay(500 / portTICK_PERIOD_MS);
	xTaskCreate(prvTask1, "Task1", 160, NULL, 1, &Task1handle);

	int i = 0;

	while (i < 20000) i++;

	vTaskDelay(100 / portTICK_PERIOD_MS);
}



