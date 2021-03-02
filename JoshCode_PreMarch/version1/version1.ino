int lock_pin = 0;
int button1_pin = 5; // button pressed feeds a 0
int button2_pin = 4;
int button3_pin = 16;
int button4_pin = 17;
int val1 = 1;
int val2 = 1;
int val3 = 1;
int val4 = 1;
int passcode[] = {1, 3, 4, 2};
int pressed[5];
int currentPosition = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(button1_pin, INPUT);
  pinMode(button2_pin, INPUT);
  pinMode(button3_pin, INPUT);
  pinMode(button4_pin, INPUT);
  pinMode(lock_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = digitalRead(button1_pin);
  val2 = digitalRead(button2_pin);
  val3 = digitalRead(button3_pin);
  val4 = digitalRead(button4_pin);
  
  if(val1+val2+val3+val4 == 3){
    
  }else if(val1+val2+val3+val4 < 3){
    currentPosition = 0;
  }
  
}
