// GPIOPort.h

#ifndef _SHIFTPORT_h
#define _SHIFTPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct PinPack8Bit_t
{
	PinPack8Bit_t(int pin0,int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7)
	{
		Pin0 = pin0;
		Pin1 = pin1;
		Pin2 = pin2;
		Pin3 = pin3;
		Pin4 = pin4;
		Pin5 = pin5;
		Pin6 = pin6;
		Pin7 = pin7;
	}

	PinPack8Bit_t()
	{
		Pin0 = -1;
		Pin1 = -1;
		Pin2 = -1;
		Pin3 = -1;
		Pin4 = -1;
		Pin5 = -1;
		Pin6 = -1;
		Pin7 = -1;
	}

	
	int Pin0;
	int Pin1;
	int Pin2;
	int Pin3;
	int Pin4;
	int Pin5;
	int Pin6;
	int Pin7;

	int GetPin(int_fast8_t input)
	{
		if (input < 0 || input > 7) return -1;
		switch (input)
		{
		case 0: return Pin0;
		case 1: return Pin1;
		case 2: return Pin2;
		case 3: return Pin3;
		case 4: return Pin4;
		case 5: return Pin5;
		case 6: return Pin6;
		case 7: return Pin7;
		default: return -1;
		}
	}

	void InitPins(uint_fast8_t Mode)
	{
		for(int i = 0; i < 8;i++)
		{
			if		(Mode == INPUT)		pinMode(GetPin(i), INPUT);
			else if (Mode == OUTPUT)	pinMode(GetPin(i), OUTPUT);
		}
	}
	
};

class shiftPort
{
 protected:

private:
	unsigned int latch_pin;
	unsigned int data_pin;
	unsigned int clock_pin;

	byte bitbuffer;

 public:
	shiftPort(unsigned int dataPin,unsigned int clockPin, unsigned int latchPin);
	shiftPort();
	void Write(uint8_t value);
	void SetBit(uint8_t pin, uint8_t value);
};

extern shiftPort Port;

#endif

