#include "Bluemate.h"

Bluemate::Bluemate(Stream* stream){
	_stream = stream;
}

void Bluemate::begin(){
	//We always want to enter command mode for a second so that we can get back to it whenver we want later.
	enterCommandMode();
	exitCommandMode();
}

boolean Bluemate::exitCommandMode(){
	sendCommand("---",true);
	if(waitAndEvaluateResponse("END")){
		_inCommandMode = false;
		return true;
	}
	return false;
}

boolean Bluemate::enterCommandMode(){
	sendCommand("$$$",false);
	if(waitAndEvaluateResponse("CMD")){
		_inCommandMode = true;
		return true;
	}
	return false;
}

boolean Bluemate::connectToDevice(char* hexAddress){
	if(!_inCommandMode){
		enterCommandMode();
	}
	sprintf(_buffer, "C,%s",hexAddress);
	sendCommand(_buffer, true);
	if(waitAndEvaluateResponse("failed")){
		//If we get "CONNECT failed" then we didn't connect
		return false;
	}
	//We were successful and now we are no long in command mode.
	_inCommandMode = false;
	return true;
}
boolean Bluemate::setMode(){
	return false;
}
boolean Bluemate::setBaudRate(int rate){
	if(!_inCommandMode){
		enterCommandMode();
	}
	sprintf(_buffer, "C,%d",rate);
	sendCommand(_buffer, true);
	if(waitAndEvaluateResponse("AOK")){
		//If we get "AOK" then we are good.
		return true;
	}
	return false;
}

int Bluemate::scanForDevices(BluetoothDevice* devices[3]){
	int i=0;
	if(!_inCommandMode){
		enterCommandMode();
	}
	sendCommand("IN",true);
	waitAndEvaluateResponse("COD=0\r\n");
	while(1){
		waitAndEvaluateResponse("\n",2000);
		char* pch = strstr (_buffer,"Found");
		if(pch != NULL){
			return i;
		}
		else{
			//Got a device;
			char* pch = strtok(_buffer, ",");
			if(pch != NULL){
				//We have a comma
				
				char*  pch2 = strtok(NULL, ",");
				if(pch != NULL){
					// devices[i]=&(BluetoothDevice){(char*)pch,(char*)pch2};
					i++;
					Serial.println(pch);
					Serial.println(pch2);
				}
				// devices[0] = {}
			}
			else{
				continue;
				//No comma, so we don't got anything.
			}
		}
	}
	// waitAndEvaluateResponse("Found 2\r");
	return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
int main(){
    char buffer[30];
    int hex_a = 0xA0086C22;
    int hex_b = 0xCC6D;
    //printf("%X%X",hex_b,hex_a);
    char buffer2[30];
    long int abc = 1;
    char* hex ="CC6DA0086C22";
    char* def;
    abc = strtol(hex, &def, 16);
    printf("%ld\n",abc);
    printf("%lX\n",abc);
    
    return 0;
}
*/
boolean Bluemate::isInCommandMode(boolean useCache){
	if(useCache){
		//Check if we have saved anything to the cache ever.
		return _inCommandMode;
	}

	//Check for inCommandMode
	//Save it to the cache
	return _inCommandMode;
}

void Bluemate::sendCommand(char* command, boolean includeEndline){
	if(includeEndline){
		_stream->println(command);
	}
	else{
		_stream->print(command);	
	}
	
}
boolean Bluemate::waitAndEvaluateResponse(char* response){
	return waitAndEvaluateResponse(response, 500);
}
boolean Bluemate::waitAndEvaluateResponse(char* response, int timeout){
	#ifdef DEBUG_BLUETOOTH
    	Serial.print("Waiting for: ");
    	Serial.println(response);
    #endif
	long endTime = millis() + timeout;
	_buffer[0] = '\0';
	while(1){
    	if(_stream->available()){
       		char c = _stream->read();
       		int len = strlen(_buffer);
       		_buffer[len] = c;
       		_buffer[len+1] = '\0';
       		#ifdef DEBUG_BLUETOOTH
       			Serial.write(c);
       		#endif
       		char* pch = strstr (_buffer,response);
			if(pch != NULL){
				return true;
			}
    	}
    	else{
    		if(millis() > endTime){
    			#ifdef DEBUG_BLUETOOTH
    				Serial.print(F("Timeout while waiting for "));
    				Serial.println(response);
    			#endif
    			return false;
    		}
    	}
  	}
}
