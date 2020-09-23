// 
// 
// 

#include "shiftPort.h"
#include "Arduino.h"


shiftPort::shiftPort()
{
	data_pin = 0;
	clock_pin = 0;
	latch_pin = 0;
}


shiftPort::shiftPort(unsigned int dataPin, unsigned int clockPin, unsigned int latchPin)
{
	data_pin = dataPin;
	clock_pin = clockPin;
	latch_pin = latchPin;
	bitbuffer = 0;

	pinMode(data_pin, OUTPUT);
	pinMode(clock_pin, OUTPUT);
	pinMode(latch_pin, OUTPUT);

}

void shiftPort::SetBit(uint8_t pin, uint8_t value)
{
	digitalWrite(latch_pin, LOW);
	bitWrite(bitbuffer, pin, value);
	shiftOut(data_pin, clock_pin, MSBFIRST, bitbuffer);
	digitalWrite(latch_pin, HIGH);
}

void shiftPort::Write(uint8_t value)
{
	digitalWrite(latch_pin, LOW);
	bitbuffer = value;
	shiftOut(data_pin, clock_pin, MSBFIRST, bitbuffer);
	digitalWrite(latch_pin, HIGH);
}

shiftPort Port;

