#include <PS2X_lib.h>
PS2X ps2x;
//pulley motor
int motor1pin1 = 2;
int motor1pin2 = 3;

//steering motor
int motor2pin1 = 4;
int motor2pin2 = 5;

//driving motor
int motor3pin1 = 6;
int motor3pin2 = 7;

int error = 0; 
byte type = 0;
byte vibrate = 0;
void setup(){
  //set motor pins to receive output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
Serial.begin(9600);

//making sure controller has full functionality
error = ps2x.config_gamepad(13,11,10,12, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
if(error == 0){
  Serial.println("Found Controller, configured successful");
  Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
}
//error handling
 else if(error == 1)
  Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
 else if(error == 2)
  Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
    switch(type) {
      case 0:
       Serial.println("Unknown Controller type");
      break;
      case 1:
       Serial.println("DualShock Controller Found");
      break;
      case 2:
        Serial.println("GuitarHero Controller Found");
      break;
    }
}

void loop(){   
if(error == 1) 
 return; 
else { //DualShock Controller
   vibrate = ps2x.Analog(PSAB_BLUE);        
   
   //checking when buttons are pressed or released                                           
   if (ps2x.NewButtonState())              
   {   
    //driving motor forward/backward
       if(ps2x.Button(PSB_R2)) {
        Serial.println("R2 pressed");
        digitalWrite(motor3pin1, HIGH);
        digitalWrite(motor3pin2, LOW);
       }
       if(ps2x.ButtonReleased(PSB_R2)) {
         digitalWrite(motor3pin1, LOW);
         digitalWrite(motor3pin2, LOW);
       }
        if(ps2x.Button(PSB_L2)) {
        Serial.println("L2 pressed");
        digitalWrite(motor3pin1, LOW);
        digitalWrite(motor3pin2, HIGH);
        }
        if(ps2x.ButtonReleased(PSB_L2)) {
        Serial.println("L2 released");
        digitalWrite(motor3pin1, LOW);
        digitalWrite(motor3pin2, LOW);
        }

        //pulley motor forward/backward
        if(ps2x.Button(PSB_RED)) {
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
      
       }
       if(ps2x.ButtonReleased(PSB_RED)) {
         digitalWrite(motor2pin1, LOW);
         digitalWrite(motor2pin2, LOW);
       }

         if(ps2x.Button(PSB_PINK)) {
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
       }
       if(ps2x.ButtonReleased(PSB_PINK)) {
        
         digitalWrite(motor2pin1, LOW);
         digitalWrite(motor2pin2, LOW);
       }

    //steering motor forward/backward    
    if(ps2x.Button(PSB_GREEN)) {
        Serial.println("R2 pressed");
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
       }
       if(ps2x.ButtonReleased(PSB_GREEN)) {
         digitalWrite(motor1pin1, LOW);
         digitalWrite(motor1pin2, LOW);
       }
        if(ps2x.Button(PSB_BLUE)) {
        Serial.println("L2 pressed");
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
        }
        if(ps2x.ButtonReleased(PSB_BLUE)) {
        Serial.println("L2 released");
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, LOW);
        }
 
   }
delay(50);
}} 
