// 
// 
// 

#include "shiftPort.h"
#include "Arduino.h"


shiftPort::shiftPort(int count, int latchPin, int clockPin, int dataPin) {
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	MYchipCount = count;
	MYlatchPin = latchPin;
	MYclockPin = clockPin;
	MYdataPin = dataPin;
	MYlastPin = count * 8 - 1;
	reset();
}

void shiftPort::lsbFirst() {
	MYway = LSBF;
}


void shiftPort::msbFirst() {
	MYway = MSBF;
}


void shiftPort::reset() {
	for (int i = 0; i < 8; i++) MYarray[i] = 0;
	send();
}

void shiftPort::sendToChips() {
	digitalWrite(MYlatchPin, LOW);
	digitalWrite(MYdataPin, LOW);
	for (int i = MYchipCount - 1; i >= 0; i--) {
		for (int j = 7; j >= 0; j--) {
			digitalWrite(MYclockPin, LOW);
			if ((MYarray[i] & MYmask[j]) > 0) {
				digitalWrite(MYdataPin, HIGH);
			}
			digitalWrite(MYclockPin, HIGH);
			digitalWrite(MYdataPin, LOW);
		}
	}
	digitalWrite(MYlatchPin, HIGH);
}


void shiftPort::reverseSendToChips() {
	digitalWrite(MYlatchPin, LOW);
	digitalWrite(MYdataPin, LOW);
	for (int i = 0; i < MYchipCount; i++) {
		for (int j = 0; j < 8; j++) {
			digitalWrite(MYclockPin, LOW);
			if ((MYarray[i] & MYmask[j]) > 0) {
				digitalWrite(MYdataPin, HIGH);
			}
			digitalWrite(MYclockPin, HIGH);
			digitalWrite(MYdataPin, LOW);
		}
	}
	digitalWrite(MYlatchPin, HIGH);
}

void shiftPort::send() {
	if (MYway == MSBF) sendToChips();
	else               reverseSendToChips();
}


// 00000001  11111110
// 00000010  11111101
// 00000100  11111011
// 00001000  11110111
// 00010000  11101111
// 00100000  11011111
// 01000000  10111111
// 10000000  01111111

// ON:   10101010 | 00000001 = 10101011
// OFF:  10101010 & 11111101 = 10101000
// Lire: 10101010 & 00000010 = 00000010

void shiftPort::setPin(int pin, int action) {
	int chip = int(pin / 8);
	int pos = pin - (chip * 8);
	switch (action) {
	case OFF: {
		MYarray[chip] = MYarray[chip] & (255 - MYmask[pos]);
		break;
	}
	case ON: {
		MYarray[chip] = MYarray[chip] | MYmask[pos];
		break;
	}
	case TOGGLE: {
		if ((MYarray[chip] & MYmask[pos]) == 0)
			MYarray[chip] = MYarray[chip] | MYmask[pos];
		else
			MYarray[chip] = MYarray[chip] & (255 - MYmask[pos]);
		break;
	}
	}
	send();
}


void shiftPort::setPins(int from, int to, int action) {
	for (int i = from; i <= to; i++) setPin(i, action);
}


int shiftPort::getState(int pin) {
	int chip = int(pin / 8);
	int pos = chip - (pin * 8);
	int actualValue = MYarray[chip] & MYmask[pos];
	if (actualValue == 0)	return 0;
	else					return 1;
}


String shiftPort::toString() {
	String s = "";
	for (int i = (MYchipCount - 1); i >= 0; i--) {
		s += byteToString(MYarray[i]);
		s += "|";
	}
	return s;
}


String shiftPort::byteToString(int data) {
	String s = "";
	for (int i = 7; i >= 0; i--) {
		s += bitRead(data, i);
	}
	return s;
}

int shiftPort::lastPin() {
	return MYlastPin;
}