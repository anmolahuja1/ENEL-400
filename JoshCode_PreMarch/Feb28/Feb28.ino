const int trigpin = 13;
const int echopin = 12;
const int relaypin1 = 14;
const int relaypin2 = 27;
const int relaypin3 = 26;
long duration;
int distance;

void setup() {
 pinMode(trigpin,OUTPUT);
 pinMode(echopin,INPUT);
// pinMode(relaypin1,OUTPUT);
// pinMode(relaypin2,OUTPUT);
// pinMode(relaypin3,OUTPUT);
 Serial.begin(9600);



}

void loop() {
  digitalWrite(trigpin,LOW);
  delay(0.005);

  digitalWrite(trigpin,HIGH);
  delay(0.010);
  digitalWrite(trigpin,LOW);

  duration = pulseIn(echopin,HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);

// if(distance < enter default distance){
//   digitalWrite(relaypin1,HIGH); //relay1 turns off
//  }
//  else{
//   digitalWrite(relaypin1,LOW); //relay2 turns on
//   }
}
