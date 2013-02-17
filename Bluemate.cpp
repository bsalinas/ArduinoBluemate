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
	return false;
}
boolean Bluemate::setMode(){
	return false;
}
boolean Bluemate::setBaudRate(){
	return false;
}

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
	long endTime = millis() + TIMEOUT;
	_buffer[0] = '\0';
	while(1){
    	if(_stream->available()){
       		char c = _stream->read();
       		int len = strlen(_buffer);
       		_buffer[len] = c;
       		_buffer[len+1] = '\0';
       		char* pch = strstr (_buffer,response);
			if(pch != NULL){
				return true;
			}
    	}
    	else{
    		if(millis() > endTime){
    			return false;
    		}
    	}
  	}
}
