//Importing the necessary library for bluetooth:
#include "BluetoothSerial.h"

//Properly enables bluetooth:
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

//Instanciates the BluetoothSerial object:
BluetoothSerial SerialBT;

const int trigpin = 12;
const int echopin = 13;

float distance;
long duration;

void setup() {
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);

  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  //Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying


}

void loop() {
    digitalWrite(trigpin,LOW);
    delay(0.005);
      
    digitalWrite(trigpin,HIGH);
    delay(0.010);
    digitalWrite(trigpin,LOW);

    duration = pulseIn(echopin,HIGH);
    distance = (duration/2)*0.03402778l;

    Serial.print("Distance is: ");
    Serial.println(distance);

    //SerialBT.print("Distance is: ");
    //SerialBT.println(distance);

    if(distance < 10){
      SerialBT.print("d");
      delay(400);
    }
    else{
      SerialBT.print("n");
      delay(400);
    }
    
    



}
