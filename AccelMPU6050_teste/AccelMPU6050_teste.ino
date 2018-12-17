#include <AccelMPU6050.h>

AccelMPU6050 mpu(20,21); //D20 e D21;

AxisMPU accel;  

float zAngle = 0.0, yAngle = 0.0, xAngle = 0.0;



void setup() {
  Serial.begin(9600);
  mpu.initI2C();
  mpu.initMPU(0,0);
  mpu.checkMPU(mpu.MPU_ADDR);
    
}

bool cramTest(){
  delay(1500);
  accel = mpu.readRawACCEL();
  xAngle = mpu.getAngleAccelX(accel.X, accel.Y, accel.Z);
 
  if(!(xAngle < 20.0)){
    delay(1500);
    accel = mpu.readRawACCEL();
    xAngle = mpu.getAngleAccelX(accel.X, accel.Y, accel.Z);
    if(!(xAngle < 20.0)){
      return true;
    }
  }else{
    return false;
  }
}

bool fallTest(){
  delay(3000);
  accel = mpu.readRawACCEL();
  zAngle = mpu.getAngleAccelZ(accel.X, accel.Y, accel.Z);
  
  if(!(zAngle >= 75.0 and zAngle <= 90.0 and xAngle < 20.0)){
    delay(2000);
    accel = mpu.readRawACCEL();
    zAngle = mpu.getAngleAccelZ(accel.X, accel.Y, accel.Z);
    if(!(zAngle >= 75.0 and zAngle <= 90.0 and xAngle < 20.0)){
      return true;
    }
  }else{
    return false;
  }
  
  
}

void loop() {
  accel = mpu.readRawACCEL();
  xAngle = mpu.getAngleAccelX(accel.X, accel.Y, accel.Z);
  yAngle = mpu.getAngleAccelY(accel.X, accel.Y, accel.Z);
  zAngle = mpu.getAngleAccelZ(accel.X, accel.Y, accel.Z);
  
  if((zAngle <= 15.0 and (yAngle <= -65.0 or yAngle >= 65))){
    if(fallTest() == true){
      Serial.println("Queda detectada");
    }
  }

  if((zAngle < 20.0 and xAngle >= 65.0 and xAngle <= 85)){
    if(cramTest() == true){
      Serial.println("Empinada detectada");
    }
  }
     Serial.print(" X: ");
     Serial.println(xAngle);
     Serial.print(" Y: ");
     Serial.println(yAngle);
     Serial.print(" Z: ");
     Serial.println(zAngle);
     delay(5000);
     Serial.println("*************************");
  yield();
}
