const int trigpin = 13; 
const int echopin = 12;         
const int relaypin1 = 14;

long duration;
float distance;

void setup() {
 pinMode(trigpin,OUTPUT);
 pinMode(echopin,INPUT);
 pinMode(relaypin1,OUTPUT);
 Serial.begin(9600);



}

void loop() {
  digitalWrite(trigpin,LOW); //clearing the trigpin signal
  delay(0.005);

  digitalWrite(trigpin,HIGH); //setting trigpin high
  delay(0.010);
  digitalWrite(trigpin,LOW);// setting trigpin high

  duration = pulseIn(echopin,HIGH); //returns how long echopin was active for in microseconds
  distance = (duration/2)*0.03402778; //calculates the distance using the speed of sound in centimeters
  Serial.println(distance);
  
 if(distance < 10){   // enter  default distance of the compartment 
   digitalWrite(relaypin1,HIGH); //relay1 turns off
  }
  else{
   digitalWrite(relaypin1,LOW); //relay1 turns on
   }
}
