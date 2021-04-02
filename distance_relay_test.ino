//Importing the necessary library for bluetooth:
#include "BluetoothSerial.h"

//Properly enables bluetooth:
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

//Instanciates the BluetoothSerial object:
BluetoothSerial SerialBT;

// 3 --> top compartment
// 2 --> middle compartment
// 1 --> bottom compartment


const int trigpin3 = 13; 
const int echopin3 = 12;

const int trigpin2 = 33; 
const int echopin2 = 32; 

const int trigpin1 = 14; 
const int echopin1 = 2; 


const int relaypin1 = 18; // bottom compartment
const int relaypin2 = 19; // middle compartment
const int relaypin3 = 21; // top compartment



long duration3;
long duration2;
long duration1;
float distance3;
float distance2;
float distance1;

String incomingmessage = "";


void setup(){
  pinMode(trigpin3,OUTPUT);
  pinMode(echopin3,INPUT);
  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
  
}

void loop(){

  // MAKE SURE BUTTONS 1 AND 2 ARE CONNECTED BEFORE RUNNING CODE
  

//    top distance sensor
      digitalWrite(trigpin3,LOW);
      delay(0.005);
      
      digitalWrite(trigpin3,HIGH);
      delay(0.010);
      digitalWrite(trigpin3,LOW);

      duration3 = pulseIn(echopin3,HIGH);
      distance3 = (duration3/2)*0.03402778l;
      Serial.println(distance3);

//    middle distance sensor
      digitalWrite(trigpin2,LOW);
      delay(0.005);
      
      digitalWrite(trigpin2,HIGH);
      delay(0.010);
      digitalWrite(trigpin2,LOW);

      duration2 = pulseIn(echopin2,HIGH);
      distance2 = (duration2/2)*0.03402778l;
     // Serial.println(distance2);
      
//    bottom distance sensor
      digitalWrite(trigpin1,LOW);
      delay(0.005);
      
      digitalWrite(trigpin1,HIGH);
      delay(0.010);
      digitalWrite(trigpin1,LOW);

      duration1 = pulseIn(echopin1,HIGH);
      distance1 = (duration1/2)*0.03402778l;
     // Serial.println(distance1);
     
  if(SerialBT.available()){
    incomingmessage = SerialBT.readString();
    
    if(incomingmessage == "relay_1"){
        digitalWrite(relaypin1,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin1,LOW);
      }
    

    else if(incomingmessage == "relay_2"){
        digitalWrite(relaypin2,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin2,LOW);
      }
    

    else if(incomingmessage == "relay_3"){
        digitalWrite(relaypin3,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin3,LOW);
    }
  
  }
  
  else{
      if(distance3 >= 10){ //if compartment is greater than or equal than default distance, it means the box is empty 
        digitalWrite(relaypin3,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin3,LOW);//relay is on
      }       
    

      if(distance2 >= 10){ // if compartment is greater than or equal than default distance, it means the box is empty                                               CHANGE DISTANCE BASED ON HOW IT IS SET UP!!!!
        // may need to change the distance above based on how the compartment was put together
        digitalWrite(relaypin2,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin2,LOW);//relay is on
      }       
    

      if(distance1 >= 10){ //if compartment is greater than or equal than default distance, it means the box is empty
        // may need to change the distance above based on how the compartment was put together
        digitalWrite(relaypin1,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin1,LOW);//relay is on
      }       
    }
}
