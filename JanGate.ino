#include <Servo.h>
#include <SoftwareSerial.h>
const int SERVO_0 = 1500;
const int SERVO_90 = 300;
const int SERVO_PIN = 9;
const int FOTO = 2;
const int RX = 10;
const int TX = 11;

int servoState = SERVO_0;
int fotoCount = 0;

Servo myservo;
SoftwareSerial BTSerial(10, 11);

String cmd;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
  myservo.attach(SERVO_PIN); 
  pinMode(FOTO, INPUT);

}

void loop() {
  
    if(BTSerial.available() > 0) {
      cmd = BTSerial.readString();
      cmd.trim();
      Serial.println("napisalem");
      Serial.println(cmd);
      if(cmd == "OPEN"){
        if(servoState == SERVO_0){
          myservo.writeMicroseconds(SERVO_90);
          servoState = SERVO_90;
          delay(500);
        }
      }
    }

    if(digitalRead(FOTO) == 0 && servoState == SERVO_90){
      while(digitalRead(FOTO) == 0){
        delay(500);
      }
      fotoCount++;
      if(fotoCount == 2){
          delay(3000);
          myservo.writeMicroseconds(SERVO_0);
          servoState = SERVO_0;
          delay(500);
          fotoCount = 0;
      }
    }

}
