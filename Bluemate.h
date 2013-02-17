#ifndef BLUEMATE_H
#define BLUEMATE_H
#include <Arduino.h>
#include <Stream.h>

#define TIMEOUT 1000;

class Bluemate{

	public:

	Bluemate(Stream* stream);
	boolean connectToDevice(char* hexAddress);
	boolean setMode();
	boolean setBaudRate();
	void begin();
	boolean enterCommandMode();
	boolean exitCommandMode();
	void sendCommand(char* command, boolean includeEndline);


	private:
	char _buffer[30];
	boolean isInCommandMode(boolean useCache);
	boolean _inCommandMode;
	boolean waitAndEvaluateResponse(char* response);
	Stream* _stream;

	/*
	Output from "D"
	***Settings***
BTA=000666430475
BTName=RN42-0475
Baudrt=9600
Parity=None
Mode  =Mstr
Authen=0
Encryp=0
PinCod=1234
Bonded=0
Rem=000D18A00001
Output from "E"
***ADVANCED Settings***
SrvName= SPP
SrvClass=0000
DevClass=1F00
InqWindw=0100
PagWindw=0100
CfgTimer=60
StatuStr=NULL
*/



};

#endif
