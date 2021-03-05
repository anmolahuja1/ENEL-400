//Importing the necessary library for bluetooth:
#include "BluetoothSerial.h"

//Properly enables bluetooth:
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

//Instanciates the BluetoothSerial object:
BluetoothSerial SerialBT;


const int trigpin = 13; 
const int echopin = 12;  
const int button = 27;
const int relaypin = 26;
int buttonstate;

long duration;
float distance;

String incomingmessage = "";


void setup(){
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(relaypin, OUTPUT);
  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
  
}

void loop(){
  buttonstate = digitalRead(button); //button is active low

      digitalWrite(trigpin,LOW);
      delay(0.005);
      
      digitalWrite(trigpin,HIGH);
      delay(0.010);
      digitalWrite(trigpin,LOW);

      duration = pulseIn(echopin,HIGH);
      distance = (duration/2)*0.03402778l;
      Serial.println(distance);


  if(SerialBT.available()){
    incomingmessage = SerialBT.readString();
    
    if(incomingmessage == "relay_1"){
      digitalWrite(relaypin,HIGH);
      delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
      digitalWrite(relaypin,LOW);
    }
  
  }
  else{
    if(buttonstate == 0){
      if(distance >= 10){ //if compartment is greater than or equal than default distance, it means the box is empty
        digitalWrite(relaypin,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin,LOW);//relay is on
      }       
    }
  }
  
}
