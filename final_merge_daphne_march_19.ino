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

const int button3 = 27;   // top compartment button -- this is the button with red and black wires
const int button2 = 15;   // middle compartment button -- this is is the button with purple wires
const int button1 = 4;   // bottom compartment button -- this is is the button with two white wires 

const int relaypin1 = 18; // bottom compartment
const int relaypin2 = 17; // middle compartment
const int relaypin3 = 21; // top compartment

int buttonstate3;
int buttonstate2;
int buttonstate1;

long duration3;
long duration2;
long duration1;
float distance3;
float distance2;
float distance1;


String incomingmessage = "";
String mastercode = "master"; // e.g. "master stmstr arg3"
// newly added - March 19th
String otp = "";
boolean otpActive = false;

float distanceSensor(const int trigpin, const int echopin){

  digitalWrite(trigpin,LOW);
  delay(0.005);
  
  digitalWrite(trigpin,HIGH);
  delay(0.010);
  digitalWrite(trigpin,LOW);

  long duration = pulseIn(echopin,HIGH);
  float distance = (duration/2)*0.03402778l;
  Serial.println(distance);

  // newly added - March 19th
  // notification implementation
  if(distance < 36){
  // checks to see if a package is detected inside
     SerialBT.print("package_detected"); // send text to MIT app via bluetooth
     delay(400);
  }
  else{
     SerialBT.print("empty"); 
     delay(400);
  }

  return distance;
  
}

void intepretmessage(String incoming){
//Convention for setting one-time generated password: "master setotp *enter otp password*"
//Convention for using one-time generated password: "*otp*  *any instruction*"
//Convention for setting masterkey: "master setmtr *enter new masterkey*"
//Convention for using masterkey: "*masterkey* *any instruction*"

  // newly added - March 19th
  if(incoming.length() >= 13){ //code(6char) ins(6char) arg3(6cha) => "master setotp 123456" set the opt to "123456" && set otpAvtive to true "master setmtr 29384d"
      String key = incoming.substring(0,6);
      String instruction = incoming.substring(7,13);//"master relay_1","master relay_2", "master relay_3", "master unlock"
      Serial.println(key);
      Serial.println(instruction);
  
     
     if(key == mastercode || (key == otp && otpActive)){
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
  
  pinMode(trigpin3,OUTPUT);
  pinMode(echopin3,INPUT);
  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button1,INPUT_PULLUP);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
  
}

void loop(){
  buttonstate3 = digitalRead(button3); //button is active low
  buttonstate2 = digitalRead(button2);
  buttonstate1 = digitalRead(button1);

  distance3 = distanceSensor(trigpin3, echopin3);
  distance2 = distanceSensor(trigpin2, echopin2);
  distance1 = distanceSensor(trigpin1, echopin1);
    

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

  else{
    if(buttonstate3 == 0){ // this button controls the top compartment lock
      if(distance3 >= 36){ //if compartment is greater than or equal than default distance, it means the box is empty
        digitalWrite(relaypin3,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin3,LOW);//relay is on
      }       
    }

    else if(buttonstate2 == 0){ // this button controls the top compartment lock
      if(distance2 >= 36){ // if compartment is greater than or equal than default distance, it means the box is empty
        // may need to change the distance above based on how the compartment was put together
        digitalWrite(relaypin2,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin2,LOW);//relay is on
      }       
    }

    else if(buttonstate1 == 0){ // this button controls the top compartment lock
      if(distance1 >= 36){ //if compartment is greater than or equal than default distance, it means the box is empty
        // may need to change the distance above based on how the compartment was put together
        digitalWrite(relaypin1,HIGH); //relay is off
        delay(2000); //2 second delay for testing purposes, supposed to be 10 seconds
        digitalWrite(relaypin1,LOW);//relay is on
      }       
    }
  }

  
}