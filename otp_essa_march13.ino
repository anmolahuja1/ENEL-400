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
const int relaypin1 = 13; // bottom compartment
const int relaypin2 = 12; // middle compartment
const int relaypin3 = 14; // top compartment
int buttonstate;

long duration;
float distance;

String incomingmessage = "";
String mastercode = "master";//"master stmstr arg3"
String otp = "";
boolean otpActive = false;

void intepretmessage(String incoming){
  
  if(incoming.length() >= 13){ //code(6char) ins(6char) arg3(6cha) => "master setotp 123456" set the opt to "123456" && set otpAvtive to true "master setmtr 29384d"
      String key = incoming.substring(0,6);
      String instruction = incoming.substring(7,13);//"master relay_1","master relay_2", "master relay_3", "master unlock"
      //keyIsValid()
     Serial.println(key);
     Serial.println(instruction);
   
     
     if(key == mastercode || (key == otp && otpActive)){//
       if(instruction == "relay1"){
        digitalWrite(relaypin1,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin1,LOW);
       }
        else if(instruction == "relay2"){
        digitalWrite(relaypin2,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin2,LOW);
      }
        else if(instruction == "relay3"){
        digitalWrite(relaypin3,HIGH);
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds 
        digitalWrite(relaypin3,LOW);
        }

        else if(instruction == "unlock"){
          
          digitalWrite(relaypin1, HIGH);
          digitalWrite(relaypin2, HIGH);
          digitalWrite(relaypin3, HIGH);
          delay(2000);                                                                                                                                
          digitalWrite(relaypin1, LOW);
          digitalWrite(relaypin2, LOW);
          digitalWrite(relaypin3, LOW);
     
        }else if(instruction == "setotp"){
          otp = incoming.substring(14,20);//last 6 char
          Serial.println(otp);
          otpActive = true;
        }else if (instruction == "setmtr"){
          mastercode = incoming.substring(14,20);
          Serial.println(mastercode);
        }
        if(key == otp && otpActive){
           otp = "";
           otpActive = false;
        }
    }
  }
 }
void setup(){
  //pinMode(trigpin,OUTPUT);
  //pinMode(echopin,INPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
  
}

void loop(){
  buttonstate = digitalRead(button); //button is active low

      /*digitalWrite(trigpin,LOW);
      delay(0.005);
      
      digitalWrite(trigpin,HIGH);
      delay(0.010);
      digitalWrite(trigpin,LOW);
      duration = pulseIn(echopin,HIGH);
      distance = (duration/2)*0.03402778l;
      Serial.println(distance);*/


  if(SerialBT.available()){
    incomingmessage = SerialBT.readString();
    intepretmessage(incomingmessage);
    }
}
