// 
// 
//


#include <ANSICodes.h>
#include "SerialPinManager.h"

#define UNKNOWN_PIN 0xFF

unsigned int getPinMode(unsigned int pin);
void InitPin(unsigned int pin, String mode);
void SetPin(unsigned int pin, String mode);
void PinInfo(unsigned int pin);
void CommandInterpreter();
void PinHelp();

String command;
String pin;
String argument;


void Pin_Command(String raw_input)
{
	raw_input = raw_input.substring(0, raw_input.indexOf('\r'));
	int commandend, pinend;

	commandend = raw_input.indexOf(' ', 0);
	pinend = raw_input.indexOf(' ', commandend + 1);



	command = raw_input.substring(0, commandend);
	pin = raw_input.substring(commandend + 1, pinend);
	argument = raw_input.substring(pinend +1);

	CommandInterpreter();
}

void CommandInterpreter()
{
	if(command.equalsIgnoreCase("set"))
	{
		SetPin(pin.toInt(), argument);
	}
	else if(command.equalsIgnoreCase("reset"))
	{
		Serial.println(COLOR_BOLDRED "NOT IMPLEMENTED JET!" COLOR_RESET);
	}
	else if(command.equalsIgnoreCase("init"))
	{
		InitPin(pin.toInt(), argument);
	}
	else if (command.equalsIgnoreCase("help"))
	{
		PinHelp();
	}
	else if (command.equalsIgnoreCase("info"))
	{
		PinInfo(pin.toInt());
	}
	else
	{
		Serial.println(COLOR_BOLDRED "Invalid PIN command! type in 'pin help' for more info!" COLOR_RESET);
	}
}

void PinHelp()
{
	Serial.println(endl COLOR_BOLDGREEN"\tPin Help" COLOR_RESET endl);

	Serial.println("\tAvailable Commands:");
	Serial.println("\t\t init \t->\t initializes a pin");
	Serial.println("\t\t set \t->\t set a pin to defined state");
	Serial.println("\t\t help \t->\t shows this help");
	Serial.println("\t\t info \t->\t shows info about the pin");
	Serial.println(endl endl);
	Serial.println("Syntax Structure: pin <command> <pinNumber> <arg>" endl);
}



void InitPin(unsigned pin,String mode)
{
	unsigned int Mode;

	
	Serial.println(endl COLOR_BOLDGREEN"\tPin Initializer" COLOR_RESET endl);


	if		(mode.equalsIgnoreCase("i")) Mode = INPUT;
	else if (mode.equalsIgnoreCase("in")) Mode = INPUT;
	else if (mode.equalsIgnoreCase("input")) Mode = INPUT;
	else if (mode.equalsIgnoreCase("o")) Mode = OUTPUT;
	else if (mode.equalsIgnoreCase("out")) Mode = OUTPUT;
	else if (mode.equalsIgnoreCase("output")) Mode = OUTPUT;
	else if (mode.equalsIgnoreCase("ip")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("i p")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("in p")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("in pull")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("in pullup")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("input p")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("input pull")) Mode = INPUT_PULLUP;
	else if (mode.equalsIgnoreCase("input pullup")) Mode = INPUT_PULLUP;
	else
	{
		Serial.print( COLOR_BOLDRED "Unknown Mode: ");
		Serial.print(mode);
		Serial.println(COLOR_RESET);
		Serial.println("Available Modes are:");
		Serial.println("\tINPUT:       \t'i', 'in', 'input'");
		Serial.println("\tOUTPUT:      \t'o', 'out', 'output'");
		Serial.println("\tINPUT_PULLUP:\t'ip', 'i p', 'in p', 'in pull', 'in pullup', 'input p', 'input pull', 'input pullup'");
		return;
	}

	
	Serial.printf("\tPin: \t" COLOR_BOLDGREEN "%d" COLOR_RESET endl,pin);

	switch (Mode)
	{
	case INPUT:
		Serial.printf("\tMode: \t" COLOR_BOLDYELLOW "INPUT" COLOR_RESET endl);
		break;
	case INPUT_PULLUP:
		Serial.printf("\tMode: \t" COLOR_BOLDCYAN "INPUT_PULLUP" COLOR_RESET endl);
		break;
	case OUTPUT:
		Serial.printf("\tMode: \t" COLOR_BOLDMAGENTA "OUTPUT" COLOR_RESET endl);
		break;
	}

	pinMode(pin, Mode);

	int i = digitalRead(pin);

	switch (i)
	{
	case HIGH:
		Serial.printf("\tState: \t" COLOR_BOLDRED "HIGH" COLOR_RESET endl);
		break;
	case LOW:
		Serial.printf("\tState: \t" COLOR_BOLDGREEN "LOW" COLOR_RESET endl);
		break;
	}

	Serial.println(endl "Pin successfully Initialized!");
}

void SetPin(unsigned pin, String mode)
{
	unsigned int Mode;
	
	Serial.println(endl COLOR_BOLDGREEN"\tGPIO Pin Set" COLOR_RESET endl);

	if		(mode.equalsIgnoreCase("high")) Mode = HIGH;
	else if (mode.equalsIgnoreCase("1")) Mode = HIGH;
	else if (mode.equalsIgnoreCase("low")) Mode = LOW;
	else if (mode.equalsIgnoreCase("0")) Mode = LOW;
	else
	{
		Serial.print(COLOR_BOLDRED "Unknown State: ");
		Serial.print(mode);
		Serial.println(COLOR_RESET endl);
		Serial.println("Available Modes are:\t '1', 'high', '0', 'low'");
		return;
	}

	Serial.printf("\tPin: \t" COLOR_BOLDGREEN "%d" COLOR_RESET endl, pin);
	
	switch (Mode)
	{
	case HIGH:
		Serial.println("\tMode: \t" COLOR_BOLDRED "HIGH" COLOR_RESET);
		break;
	case LOW:
		Serial.println("\tMode: \t" COLOR_BOLDGREEN "LOW" COLOR_RESET);
		break;
	}

	digitalWrite(pin, Mode);

	Serial.println(endl "Pin successfully set!");
	

}

void PinInfo(unsigned pin)
{
	Serial.println(endl COLOR_BOLDGREEN"\tGPIO Pin Info" COLOR_RESET endl);
	Serial.printf("\tPin: \t" COLOR_BOLDGREEN "%d" COLOR_RESET endl, pin);
	switch (getPinMode(pin))
	{
	case INPUT:
		Serial.printf("\tMode: \t" COLOR_BOLDYELLOW "INPUT" COLOR_RESET endl);
		break;
	case INPUT_PULLUP:
		Serial.printf("\tMode: \t" COLOR_BOLDCYAN "INPUT_PULLUP" COLOR_RESET endl);
		break;
	case OUTPUT:
		Serial.printf("\tMode: \t" COLOR_BOLDMAGENTA "OUTPUT" COLOR_RESET endl);
		break;
	default:
		Serial.println(COLOR_BOLDRED "Unknown Pin!" COLOR_RESET);
		return;
	}

	switch (digitalRead(pin))
	{
	case HIGH:
		Serial.println("\tState: \t" COLOR_BOLDRED "HIGH" COLOR_RESET);
		break;
	case LOW:
		Serial.println("\tState: \t" COLOR_BOLDGREEN "LOW" COLOR_RESET);
		break;
	}
	Serial.println();
	
}



unsigned int getPinMode(unsigned int pin)
{
	unsigned int bit = digitalPinToBitMask(pin);
	unsigned int port = digitalPinToPort(pin);

	// I don't see an option for mega to return this, but whatever...
	if (NOT_A_PIN == port) return UNKNOWN_PIN;

	// Is there a bit we can check?
	if (0 == bit) return UNKNOWN_PIN;

	// Is there only a single bit set?
	if (bit & bit - 1) return UNKNOWN_PIN;

	volatile uint8_t* reg, * out;
	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (*reg & bit)
		return OUTPUT;
	else if (*out & bit)
		return INPUT_PULLUP;
	else
		return INPUT;
}

