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
 


const int button3 = 27;   // top compartment button -- this is the button with red and black wires
const int button2 = 15;   // middle compartment button -- this is is the button with purple wires           CHANGE PIN NUMBERS ACCORDING TO WHAT YOU HAVE!
const int button1 = 4;   // bottom compartment button -- this is is the button with two white wires 



const int relaypin1 = 18; // bottom compartment
const int relaypin2 = 19; // middle compartment   CHANGE PIN NUMBERS ACCORDING TO WHAT YOU HAVE!!
const int relaypin3 = 21; // top compartment



int buttonstate3;
int buttonstate2;
int buttonstate1;

String incomingmessage = "";

void setup(){
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  
  pinMode(relaypin1,OUTPUT);
  pinMode(relaypin2,OUTPUT);
  pinMode(relaypin3,OUTPUT);

  
  
  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
}

void loop(){
  buttonstate1 = digitalRead(button1); //button is active low
  buttonstate2 = digitalRead(button2);
  buttonstate3 = digitalRead(button3);

  Serial.println(/*whatever button you want to test*/); //prints the buttonstate
 
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
    if(buttonstate3 == 0){ // this button controls the top compartment lock
        digitalWrite(relaypin3,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin3,LOW);//relay is on
      }       
    

    else if(buttonstate2 == 0){ // this button controls the top compartment lock
        digitalWrite(relaypin2,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin2,LOW);//relay is on
      }       
    

    else if(buttonstate1 == 0){ // this button controls the top compartment lock
        digitalWrite(relaypin1,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin1,LOW);//relay is on
      }
  }       
    
}
