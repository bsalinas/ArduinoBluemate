#include <Bluemate.h>
#include <SoftwareSerial.h>




SoftwareSerial bluetoothSerial(2,3);
Bluemate bluetooth(&bluetoothSerial);

void setup(){
  Serial.begin(9600);
  //Out of the box, the Bluemate defaults to 115200
  bluetoothSerial.begin(9600);
  bluetooth.begin(false);
  delay(65000);
  boolean connected = bluetooth.enterCommandMode();
  if(connected){
    Serial.println("In command mode");
  }
  else{
    Serial.println("Error entering command mode");
  }
}

void loop(){
  
}
