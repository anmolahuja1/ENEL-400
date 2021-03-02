//Importing the necessary library for bluetooth:
#include "BluetoothSerial.h"

//Properly enables bluetooth:
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

//Instanciates the BluetoothSerial object:
BluetoothSerial SerialBT;

const int trigpin = 2;
const int echopin = 4;
const int relaypin1 = 18;
const int relaypin2 = 17;
const int relaypin3 = 21;
long duration;
int distance;

String incomingmessage = "";
char incomingchar;


void setup() 
{
//  pinMode(trigpin,OUTPUT);
//  pinMode(echopin,INPUT);
//  pinMode(relaypin,OUTPUT);

  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);

  Serial.begin(115200);                                                       //Making the communication rate correct
  SerialBT.begin("Smartbox"); //Bluetooth device name                         //Naming the device
  Serial.println("The device started, now you can pair it with bluetooth!");  //Message saying the bluetooth is ready
}

void loop() 
{
//  digitalWrite(trigpin,LOW);
//  delay(0.005);
//
//  digitalWrite(trigpin,HIGH);
//  delay(0.010);
//  digitalWrite(trigpin,LOW);
//
//  duration = pulseIn(echopin,HIGH);
//  distance = duration*0.034/2;
//
//  Serial.print("Distance is:");
//  Serial.println(distance);

  if (SerialBT.available())                                       //If there is information waiting to be read from the serial port:
  {
    incomingchar = SerialBT.read();                               //  Take note of the incoming informtaion.
    if(incomingchar != '\n')                                      //  If that information is not '\n':
    {
      incomingmessage = incomingmessage + (String)incomingchar;   //    Add the caracter to the message string.
    }
    else                                                          //  Otherwise:
    {
      incomingmessage = "";                                       //    Clear the incoming message
    }
    Serial.write(incomingchar);                                   //  Write the character to the terminal.
  }

  if(incomingmessage == "relay_1"){
    digitalWrite(relaypin1, HIGH);
    delay(1000);
    digitalWrite(relaypin1, LOW);
  }else if(incomingmessage == "relay_2"){
    digitalWrite(relaypin2, HIGH);
    delay(1000);
    digitalWrite(relaypin2, LOW);
  }else if(incomingmessage == "relay_3"){
    digitalWrite(relaypin3, HIGH);
    delay(1000);
    digitalWrite(relaypin3, LOW);
  }

//  if(incomingmessage == "relay_OFF")                              //If the message was: "relay_ OFF":
//  {
//    digitalWrite(relaypin,HIGH);                                  //  Output HIGH to the relay.
//
//  }
//  else if(incomingmessage == "relay_ON")                          //Otherwise if the message was "relay_ON":
//  {
//    digitalWrite(relaypin,LOW);                                   //  Output LOW  to the relay.
//  }
//
  delay(20);                                                      //Wait a hot minute.
}
