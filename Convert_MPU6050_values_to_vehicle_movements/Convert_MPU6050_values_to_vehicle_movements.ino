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
int leftspeed, rightspeed;
float AngY, AngX;
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
  AngX = mpu.GetAngX(); //retrieve X angle values from mpu6050
  Serial.print(AngX);
  Serial.print(", ");
  AngY = mpu.GetAngY(); ///retrieve Y angle values from mpu6050
  Serial.println(AngY);

  
  if (AngY<10 && AngY>-10 && AngX<10 && AngX>-10){
    //nomovement
    stopit();
  }
  else if(AngY<-10 && AngY>-60 && AngX<10 && AngX>-10){
    //forward
    leftspeed  = 4*abs(AngY) - 40;
    rightspeed  = 4*abs(AngY) - 40;
    forward(leftspeed,rightspeed);
  }
   else if(AngY<-10 && AngY>-60 && AngX<-10 && AngX>-60){
   //forwardright
    leftspeed = 4*abs(AngY) - 40;
    rightspeed = leftspeed - 4*abs(AngX);
    forward(leftspeed,rightspeed);
  }
  else if(AngY<-10 && AngY>-60 && AngX>10 && AngX<60){
   //forwardleft
    rightspeed = 4*abs(AngY) - 40;
    leftspeed = leftspeed - 4*abs(AngX);
    forward(leftspeed,rightspeed);
  }
  else if(AngY>10 && AngY<60 && AngX<10 && AngX>-10){
    //backward
    leftspeed  = 4*abs(AngY) - 40;
    rightspeed  = 4*abs(AngY) - 40;
    backward(leftspeed,rightspeed);
  }
   else if(AngY>10 && AngY<60 && AngX<-10 && AngX>-60){
   //backwardright
    leftspeed = 4*abs(AngY) - 40;
    rightspeed = leftspeed - 4*abs(AngX);
    backward(leftspeed,rightspeed);
  }
  else if(AngY>10 && AngY<60 &&AngX>10 && AngX<60){
   //backwardleft
    rightspeed = 4*abs(AngY) - 40;
    leftspeed = leftspeed - 4*abs(AngX);
    backward(leftspeed,rightspeed);
  }
//  else if(AngY<10 && AngY>-10 && AngX>10 && AngX<60){
//    //rollleft
//    leftspeed - 100 = 2*(abs(AngY) - 10);
//    rightspeed - 100 = 2*(abs(AngY) - 10);
//    rollleft(leftspeed,rightspeed);
//    }
//  else if(AngY<10 && AngY>-10 && AngX<-10 && AngX>-60){
//  //rollright
//    leftspeed - 100 = 2*(abs(AngY) - 10);
//    rightspeed - 100 = 2*(abs(AngY) - 10);
//    rollright(leftspeed,rightspeed);
//    }
  }


  void forward(uint8_t leftspeed,uint8_t rightspeed)
{
  analogWrite(enableleft , leftspeed);
 analogWrite(enableright , rightspeed);
   digitalWrite (leftin1, LOW);
   digitalWrite (leftin2, HIGH);
   digitalWrite (rightin1, HIGH);
   digitalWrite (rightin2, LOW); 
 }

 void backward(uint8_t leftspeed,uint8_t rightspeed)
 {
   analogWrite(enableleft , leftspeed/2);
   analogWrite(enableright , rightspeed/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

void rightback(uint8_t leftspeed,uint8_t rightspeed)
 {
  analogWrite(enableright , leftspeed/2);
   analogWrite(enableleft , rightspeed/2);
    digitalWrite (leftin2,LOW);
    digitalWrite (leftin1,LOW);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

 void leftback(uint8_t leftspeed,uint8_t rightspeed)
 {
  analogWrite(enableright , leftspeed/2);
   analogWrite(enableleft , rightspeed/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2,LOW);
    digitalWrite (rightin1,LOW);  
 }

 void rightfront(uint8_t leftspeed,uint8_t rightspeed)
 {
  analogWrite(enableright , leftspeed/2);
   analogWrite(enableleft , rightspeed/2);
    digitalWrite (leftin1,LOW);
    digitalWrite (leftin2,LOW);
    digitalWrite (rightin1, HIGH);
    digitalWrite (rightin2,LOW);  
  }
  
 void leftfront(uint8_t leftspeed,uint8_t rightspeed)
 {
  analogWrite(enableright , leftspeed/2);
   analogWrite(enableleft , rightspeed/2);
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
   analogWrite(enableleft , leftspeed);
   analogWrite(enableright , rightspeed);
   digitalWrite (leftin1, LOW);
   digitalWrite (leftin2, HIGH);
   digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
    }
   void rollleft(){
    analogWrite(enableleft , leftspeed);
   analogWrite(enableright , rightspeed);
   digitalWrite (leftin2, LOW);
   digitalWrite (leftin1, HIGH);
   digitalWrite (rightin1, HIGH);
    digitalWrite (rightin2,LOW); 
   }
   
    
