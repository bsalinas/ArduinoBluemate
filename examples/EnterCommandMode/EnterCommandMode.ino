#include <Bluemate.h>
#include <SoftwareSerial.h>



SoftwareSerial bluetoothSerial(2,3);
Bluemate bluetooth(&bluetoothSerial);

void setup(){
  Serial.begin(9600);
  //Out of the box, the Bluemate defaults to 115200
  //But remember that SoftwareSerial doesn't work well at high baud rates.
  bluetoothSerial.begin(9600);
  bluetooth.begin();
  boolean connected = bluetooth.enterCommandMode();
  if(connected){
    Serial.println("In command mode");
//    bluetooth.sendCommand("D",true);  
  }
  else{
    Serial.println("Error entering command mode");
  }
//  bluetooth.sendCommand("D",true);
  BluetoothDevice* devices[3];
  int num = bluetooth.scanForDevices(devices);
  Serial.println(num);
//  for(int i=0; i<num; i++){
//    Serial.print((char*)(&devices[i]->address));
//    Serial.print(",");
//    Serial.println((char*)(&devices[i]->cod));
//  }
  
}

void loop(){
   if(bluetoothSerial.available()){
      Serial.write(bluetoothSerial.read()); 
   }
   if(Serial.available()){
     bluetoothSerial.write(Serial.read());
   }
  
}
