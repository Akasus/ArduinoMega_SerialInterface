// 
// 
// 
#include "TaskCollection.h"
#include "SerialTask.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "ANSICodes.h"
#include "stdint.h"
#include "SerialPinManager.h"

//Macros

#define RX_BUFFER_SIZE 1024
#define BAUDRATE 115200

void(*resetFunc)(void) = 0;

//Declarations
static void prv_rx_read(void* pvParameters);
void printPrompt(const char * str);
void printPrompt();
void handleCommand();
void parseCommand(const String command,const String param);
void debug_Out(const char* str, bool success);
void printHelp();
void ShowTasks();
void TogglePin(unsigned int pin);


//Globals
static String rx_Buffer;
static int_fast16_t rx_BufferCtr = 0;
static String param_buffer;
static char taskBuffer[512];


//Init Serial Task

void StartSerialTask()
{
	Serial.begin(BAUDRATE);
    xTaskCreate(prv_rx_read, "RX_Task", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
}



static void prv_rx_read(void* pvParameters) // Serial Task
{
    (void)pvParameters;

    while (!Serial)
    {
        vTaskDelay(1);
    }
	
    Serial.println(COLOR_BOLDGREEN "Serial Interface ready !" COLOR_RESET);
    printPrompt();
    Serial.flush();

    for (;;)
    {
        if (Serial.available())
        {
            if (rx_BufferCtr < RX_BUFFER_SIZE)
            {
               
                rx_Buffer += (char)Serial.read();
                rx_BufferCtr++;
                Serial.print(rx_Buffer.charAt(rx_BufferCtr -1));
            }
            else
            {
                rx_BufferCtr = 0;
                Serial.flush();
                Serial.println();
                printPrompt();
            	
            }

            if (rx_Buffer[rx_BufferCtr - 1] == '\n' || rx_Buffer[rx_BufferCtr - 1] == '\r')
            {
                Serial.println();
                handleCommand();
                rx_BufferCtr = 0;
            }
        	
            else if(rx_Buffer[rx_BufferCtr -1] == '\177')
            {
	            if(rx_BufferCtr <= 1)
	            {
                    Serial.flush();
                    Serial.write('\r');
                    printPrompt();
	            	continue;
	            }
                Serial.write('\r');
                printPrompt();
                int i = 0;
            	
	            while (i < rx_BufferCtr)
	            {
	            	
                    Serial.write(' ');
                    i++;
	            }
                Serial.write('\r');
                rx_Buffer.remove(rx_Buffer.length()-1);
                if (rx_BufferCtr >= 2)
                {
                    rx_Buffer.remove(rx_Buffer.length() -1);
                    rx_BufferCtr -= 2;
                }
                else
                    rx_BufferCtr -= 1;

            	
                printPrompt();
                Serial.print(rx_Buffer);
            }
        }
        else
            vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void handleCommand(void)
{
    if(rx_Buffer == "\n\r" || rx_Buffer == "\n" || rx_Buffer == "\r")
    {
        rx_Buffer = "";
        printPrompt();
    	return;
    }
	
    int commandLength = 0;
    int paramLength = 0;
    int count;
    bool commandOnlyOnce = true;
    bool IsParameter = false;

    commandLength = rx_Buffer.indexOf(' ', 0);
    paramLength = rx_Buffer.indexOf('\r');
	if(paramLength < 0)
	{
        paramLength = rx_Buffer.indexOf('\n');
	}
	
    String command = "";
    String param = "";

	if(commandLength >= 0)
	{
		command = rx_Buffer.substring(0, commandLength);
		param = rx_Buffer.substring(commandLength + 1, paramLength);
	}
    else
    {
        command = rx_Buffer.substring(0, paramLength);
    }
	
    rx_Buffer = "";
    rx_BufferCtr = 0;
	
    parseCommand(command, param);
}

void parseCommand(const String command,const String param)
{
	
    if (command == "start")
    {
        printPrompt(COLOR_BOLDRED "NOT IMPLEMENTED JET!" COLOR_RESET);
    }
    else if (command == "stop")
    {
        printPrompt(COLOR_BOLDRED "NOT IMPLEMENTED JET!" COLOR_RESET);
    }
    else if (command == "help")
    {
        printHelp();
    }
    else if (command == "tasks")
    {
        ShowTasks();
    }
    else if (command == "reset")
    {
        resetFunc();
    }
	else if(command == "pin")
	{
        Pin_Command(param);
        printPrompt();
	}
    else
    {
        printPrompt(COLOR_BOLDRED"Invalid command! type in 'help' for more info!" COLOR_RESET endl);
    }
}

void printHelp()
{
    Serial.write('\r');
    Serial.println("        Help" endl);
    Serial.println("    Available Commands:");
    Serial.println("        reset   ->  reset the Arduino");
    Serial.println("        tasks   ->  List the tasks and those states");
    Serial.println("        start   ->  starts a task");
    Serial.println("        stop    ->  stops a task");
    Serial.println("        pin     ->  Serial Pin functions");
    Serial.println(endl endl);
    Serial.println("Syntax Structure: <command> <parameter>" endl);
    printPrompt();
}



void debug_Out(const char* str, bool success)
{
    Serial.write('\r');
    if (success)     Serial.print(COLOR_BOLDGREEN "OK   " COLOR_RESET);
    else            Serial.print(COLOR_BOLDRED    "NOK  " COLOR_RESET);
    Serial.println(str);
    printPrompt();
}


void printPrompt()
{
    Serial.print(COLOR_GREEN"atmega@AK-ATM00" COLOR_RESET":" COLOR_BLUE "~" COLOR_RESET "$ ");
}




void printPrompt(const char * str)
{
    Serial.write('\r');
    Serial.println(str);
    printPrompt();
}

void ShowTasks()
{
    Serial.write('\r');
    bool over1 = false;
    int linecount = 0;
    int oldlinecount = 0;
    int i = 0;

    Serial.println(endl "       Task List" endl);
	
    Serial.println("    Press 'ESC' to Exit!" endl);
    Serial.println("  Name     | State | Priority | Stack | Num |");
    Serial.println("---------------------------------------------");
    Serial.print("\033[s");
    do
    {
        oldlinecount = linecount;
        linecount = 0;
        vTaskList(taskBuffer);
        i = 0;
        while (taskBuffer[i] != '\0')
        {
            if (taskBuffer[i] == '\r')
                linecount++;
            i++;
        }
        if (over1)
        {
            Serial.printf("\033[%dA", oldlinecount);
            for (int f = 0; f < oldlinecount; f++)
            {
                Serial.println("\033[K");
            }
            Serial.printf("\033[%dA", oldlinecount);
        }
        Serial.print(taskBuffer);
        over1 = true;
    	
        /*for (int f = 0; f < oldlinecount - linecount; f++)
        {
            Serial.println("\033[K");
        }*/
        
        vTaskDelay(250 / portTICK_PERIOD_MS);
    } while ((Serial.read() != '\033'));

    Serial.println();
    printPrompt();
}


