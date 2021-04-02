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



int buttonstate3;
int buttonstate2;
int buttonstate1;


String incomingmessage = "";


void setup(){
;
  pinMode(button3,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button1,INPUT_PULLUP);

  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying
  
}

void loop(){

  // MAKE SURE BUTTONS 1 AND 2 ARE CONNECTED BEFORE RUNNING CODE
  
  buttonstate3 = digitalRead(button3); //button is active low
  buttonstate2 = digitalRead(button2);
  buttonstate1 = digitalRead(button1);



     

    if(buttonstate3 == 0){ // this button controls the top compartment lock
      SerialBT.println("Button3 is working");
      }       
    

    else if(buttonstate2 == 0){ // this button controls the top compartment lock
      SerialBT.println("Button2 is working");
      }       
    

    else if(buttonstate1 == 0){
          SerialBT.println("Button1 is working");
      }       
   
  
}
