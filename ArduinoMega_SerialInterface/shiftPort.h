// GPIOPort.h

#ifndef _SHIFTPORT_h
#define _SHIFTPORT_h


#define OFF 0
#define ON 1
#define TOGGLE 3
#define MSBF 0
#define LSBF 1


class shiftPort
{
private:
	void sendToChips();                     
	void reverseSendToChips();              
	String byteToString(int data);          
	byte MYarray[8] = { 0,0,0,0,0,0,0,0 };
	byte MYmask[8] = { 1,2,4,8,16,32,64,128 };
	int MYchipCount;
	int MYlatchPin;
	int MYclockPin;                         
	int MYdataPin;
	int MYway = MSBF;
	int MYlastPin;

 public:
	 /// <summary>
	 /// Constructor 
	 /// </summary>
	 /// <param name="count">The Ammount of used chips on this line</param>
	 /// <param name="latchPin">The ST_CP Pin of the HC595</param>
	 /// <param name="clockPin">The SH_CP Pin of the HC595</param>
	 /// <param name="dataPin"> The DS Pin of the HC595</param>
	 shiftPort(int count, int latchPin, int clockPin, int dataPin);
	 /// <summary>
	 /// Begin with the Least Significant Bit >> 01234567
	 /// </summary>
	 void lsbFirst();
	 /// <summary>
	 /// Begin with the Most Significant Bit >> 76543210
	 /// </summary>
	 void msbFirst();								//Most Significant Bit First ...,4,2,1,0
	 void reset();		
	 /// <summary>
	 /// Set the selectet pin to choosen State
	 /// </summary>
	 /// <param name="pin"> -> The Pin you want to change</param>
	 /// <param name="action">-> The state for the Pin ON|OFF|TOGGLE</param>
	 void setPin(int pin, int action);
	 /// <summary>
	 /// Set the selected pins to choosen State
	 /// </summary>
	 /// <param name="from"> -> Index of start Bit</param>
	 /// <param name="to"> -> Index of end Bit</param>
	 /// <param name="action"> -> The state for the Pins ON|OFF|TOGGLE</param>
	 void setPins(int from, int to, int action);
	 /// <summary>
	 /// Send the Bytes to the Registers
	 /// </summary>
	 void send();   
	 /// <summary>
	 /// Returns the State of the selectet pin
	 /// </summary>
	 /// <param name="pin"></param>
	 /// <returns></returns>
	 int getState(int pin); 
	 /// <summary>
	 /// Returns the register values as a string
	 /// </summary>
	 /// <returns></returns>
	 String toString(); 
	 /// <summary>
	 /// by 1 register it is '7' by 2 it is '15'
	 /// </summary>
	 /// <returns>Returns the index of the last pin</returns>
	 int lastPin();
};

extern shiftPort Port;

#endif

