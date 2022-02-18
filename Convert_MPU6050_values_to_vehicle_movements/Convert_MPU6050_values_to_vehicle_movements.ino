/*
 *  Mandatory includes
 */
#include <Arduino.h>
#include <TinyMPU6050.h>
#define enableleft 6
#define leftin1 7
#define leftin2 5
#define rightin1 4
#define rightin2 2
#define enableright 3
int speed1, speed2;
float AngY;
/*
 *  Constructing MPU-6050
 */
MPU6050 mpu (Wire);

/*
 *  Setup
 */
void setup() {

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
}

/*
 *  Loop
 */
void loop() {

  mpu.Execute();
  Serial.print("AngX = ");
  Serial.print(mpu.GetAngX());
  Serial.print("  /  AngY = ");
  AngY = mpu.GetAngY();
  Serial.print(AngY);
  Serial.print("  /  AngZ = ");
  Serial.println(mpu.GetAngZ());
  if (AngY<10 && AngY>-10 && AngX<10 && AngX>-10){
    //nomovement
    stopit();
  }
  else if(AngY<-10 && AngY>-60 && AngX<10 && AngX>-10){
    //forward
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = 2*(abs(AngY) - 10);
    forward(speed1,speed2);
  }
   else if(AngY<-10 && AngY>-60 && AngX<-10 && AngX>-60){
   //forwardright
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = speed1 - (2*(abs(AngX) - 10));
    forward(speed1,speed2);
  }
  else if(AngY<-10 && AngY>-60 && AngX>10 && AngX<60){
   //forwardleft
    speed2 - 100 = 2*(abs(AngY) - 10);
    speed1 - 100 = speed1 - (2*(abs(AngX) - 10));
    forward(speed1,speed2);
  }
  else if(AngY>10 && AngY<60 && AngX<10 && AngX>-10){
    //backward
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = 2*(abs(AngY) - 10);
    backward(speed1,speed2);
  }
   else if(AngY>10 && AngY<60 && AngX<-10 && AngX>-60){
   //backwardright
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = speed1 - (2*(abs(AngX) - 10));
    backward(speed1,speed2);
  }
  else if(AngY>10 && AngY<60 &&AngX>10 && AngX<60){
   //backwardleft
    speed2 - 100 = 2*(abs(AngY) - 10);
    speed1 - 100 = speed1 - (2*(abs(AngX) - 10));
    backward(speed1,speed2);
  }
  else if(AngY<10 && AngY>-10 && AngX>10 && AngX<60){
    //rollleft
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = 2*(abs(AngY) - 10);
    rollleft(speed1,speed2);
    }
  else if(AngY<10 && AngY>-10 && AngX<-10 && AngX>-60){
  //rollright
    speed1 - 100 = 2*(abs(AngY) - 10);
    speed2 - 100 = 2*(abs(AngY) - 10);
    rollright(speed1,speed2);
    }
  }


  void forward(uint8_t speed1,uint8_t speed2)
{
  analogWrite(enableleft , speed1);
 analogWrite(enableright , speed2);
   digitalWrite (leftin1, LOW);
   digitalWrite (leftin2, HIGH);
   digitalWrite (rightin1, HIGH);
   digitalWrite (rightin2, LOW); 
 }

 void backward(uint8_t speed1,uint8_t speed2)
 {
   analogWrite(enableleft , speed1/2);
   analogWrite(enableright , speed2/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

void rightback(uint8_t speed1,uint8_t speed2)
 {
  analogWrite(enableright , speed1/2);
   analogWrite(enableleft , speed2/2);
    digitalWrite (leftin2,LOW);
    digitalWrite (leftin1,LOW);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

 void leftback(uint8_t speed1,uint8_t speed2)
 {
  analogWrite(enableright , speed1/2);
   analogWrite(enableleft , speed2/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2,LOW);
    digitalWrite (rightin1,LOW);  
 }

 void rightfront(uint8_t speed1,uint8_t speed2)
 {
  analogWrite(enableright , speed1/2);
   analogWrite(enableleft , speed2/2);
    digitalWrite (leftin1,LOW);
    digitalWrite (leftin2,LOW);
    digitalWrite (rightin1, HIGH);
    digitalWrite (rightin2,LOW);  
  }
  
 void leftfront(uint8_t speed1,uint8_t speed2)
 {
  analogWrite(enableright , speed1/2);
   analogWrite(enableleft , speed2/2);
    digitalWrite (leftin1, LOW);
    digitalWrite (leftin2,HIGH);
    digitalWrite (rightin1,LOW);
    digitalWrite (rightin2,LOW);  
 }
 
 void stopit()
 {
 analogWrite(enableright , 0);
   analogWrite(enableleft , 0);
  }
  void rollright()
  {
   analogWrite(enableleft , speed1);
   analogWrite(enableright , speed2);
   digitalWrite (leftin1, LOW);
   digitalWrite (leftin2, HIGH);
   digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
    }
   void rollleft(){
    analogWrite(enableleft , speed1);
   analogWrite(enableright , speed2);
   digitalWrite (leftin2, LOW);
   digitalWrite (leftin1, HIGH);
   digitalWrite (rightin1, HIGH);
    digitalWrite (rightin2,LOW); 
   }
   
    
