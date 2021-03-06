#include <Servo.h>
#include <SoftwareSerial.h>
const int SERVO_DOWN = 2400;
const int SERVO_UP = 1000;
const int SERVO_PIN = 9;
const int FOTO = 2;
const int RX = 10;
const int TX = 11;

int servoState = SERVO_DOWN;
bool vacuumCleaning = false;

Servo myservo;
SoftwareSerial BTSerial(10, 11);

String cmd;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
  myservo.attach(SERVO_PIN);
  myservo.writeMicroseconds(SERVO_DOWN); 
  pinMode(FOTO, INPUT);

}

void loop() {
  
    if(BTSerial.available() > 0) {
      cmd = BTSerial.readString();
      cmd.trim();
      Serial.println("received:");
      Serial.println(cmd);
      if(cmd == "OPEN"){
        if(servoState == SERVO_DOWN){
          openTheGate();
          servoState = SERVO_UP;
          vacuumCleaning = false;
          delay(500);
        }
      } else if(cmd == "CLOSE"){
          closeTheGate();
          servoState = SERVO_DOWN;
          vacuumCleaning = false;
          delay(500);
      }
    }

    if(servoState == SERVO_UP){
      if(digitalRead(FOTO) == 1 && !vacuumCleaning){
        Serial.println("vacuum is out");
        vacuumCleaning = true;  
        delay(30000);
      }
      if(digitalRead(FOTO) == 0 && vacuumCleaning){
        Serial.println("vacuum is back");
        delay(10000);
        closeTheGate();
        servoState = SERVO_DOWN;
        delay(500);
        vacuumCleaning = false;
      }
      
    }
    
}

void openTheGate(){
    int servoState = SERVO_DOWN;
    Serial.println(servoState);
    while(servoState > SERVO_UP){
      servoState = servoState - 100;
      myservo.writeMicroseconds(servoState);
      delay(300);
    }    
}

void closeTheGate(){
  int servoState = SERVO_UP;
  Serial.println(servoState);
  while(servoState < SERVO_DOWN){
    servoState = servoState + 100;
    myservo.writeMicroseconds(servoState);
    delay(500);
  }
  myservo.writeMicroseconds(SERVO_DOWN);
} 
