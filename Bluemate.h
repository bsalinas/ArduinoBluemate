#ifndef BLUEMATE_H
#define BLUEMATE_H
#include <Arduino.h>
#include <Stream.h>

#define TIMEOUT 500;
// #define DEBUG_BLUETOOTH 0;
typedef struct{
	char address[12]; //this should really be 2 ints or something
	// char name[12], //only store the first 12 chars,
	char cod[12];
} BluetoothDevice;
class Bluemate{

	public:

	Bluemate(Stream* stream);
	boolean connectToDevice(char* hexAddress);
	boolean setMode();
	boolean setBaudRate(int rate);
	void begin();
	boolean enterCommandMode();
	boolean exitCommandMode();
	void sendCommand(char* command, boolean includeEndline);
	int scanForDevices(BluetoothDevice* devices[3]);


	private:
	char _buffer[45];
	boolean isInCommandMode(boolean useCache);
	boolean _inCommandMode;
	boolean waitAndEvaluateResponse(char* response);
	boolean waitAndEvaluateResponse(char* response, int timeout);
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
