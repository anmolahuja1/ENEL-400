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
      //SerialBT.println(distance3);

//    middle distance sensor
      digitalWrite(trigpin2,LOW);
      delay(0.005);
      
      digitalWrite(trigpin2,HIGH);
      delay(0.010);
      digitalWrite(trigpin2,LOW);

      duration2 = pulseIn(echopin2,HIGH);
      distance2 = (duration2/2)*0.03402778l;
      //SerialBT.println(distance2);
      
//    bottom distance sensor
      digitalWrite(trigpin1,LOW);
      delay(0.005);
      
      digitalWrite(trigpin1,HIGH);
      delay(0.010);
      digitalWrite(trigpin1,LOW);

      duration1 = pulseIn(echopin1,HIGH);
      distance1 = (duration1/2)*0.03402778l;
     SerialBT.println(distance1);
     
  
  
}
