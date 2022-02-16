/*
 *  Mandatory includes
 */
#include <Arduino.h>
#include <TinyMPU6050.h>
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
  if (AngY <10 && AngY>-10 && AngX <10 && AngX>-10){
    speed1 = 0;
    speed2 = 0;
  }
  else if(AngY < -10 && AngY > -60 && AngX <10 && AngX>-10){
    //forward
  }
   else if(AngY < -10 && AngY > -60 && AngX < -10 && AngX > -60){
   
  }
  else if(AngY < -10 && AngY > -60 && AngX > 10 && AngX < 60){
   
  }
  else if(AngY > 10 && AngY < 60 && AngX <10 && AngX>-10){
    //forward
  }
   else if(AngY > 10 && AngY < 60 && AngX < -10 && AngX > -60){
   
  }
  else if(AngY > 10 && AngY < 60 && AngX > 10 && AngX < 60){
   
  }
  else if(AngY > -10 && AngY < -60 && AngX > -10 && AngX < -60){
    speed - 100 = 2*(AngY - 10);
  }
  else if(AngY > 10 && AngY < 60 && AngY > 10 && AngY < 60){
    }
  }
    
