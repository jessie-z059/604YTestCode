#include "main.h"
#include "function.hpp"
using namespace pros;

void PIDdrive(double target, double kP, double kI, double kD){
double error;
double integral; 
double derivative;
double lasterror;
double previouserror;
delay(20);
FrontrightDrive.tare_position();
FrontleftDrive.tare_position();
BackleftDrive.tare_position();
BackrightDrive.tare_position();
RightmiddleDrive.tare_position();
LeftmiddleDrive.tare_position();
while(averageposition() < target){
error = averageposition() - target;
derivative = error - lasterror;
integral += error;
int power = (kP * error) + (kI * integral) + (kD * derivative);
setDrive(-power,-power);
lasterror = error;
}
PowerDrive(-1);
}

void PIDturn(double degree, double kP, double kI, double kD){
  Inertial.reset();
   int direction = abs(degree) / (degree);
kP=0;
kI=0;
kD=0;

double error;
double integral = 0; 
double derivative = 0; 
double lasterror;
double sensor_value = Inertial.get_rotation();


while(abs(Inertial.get_rotation()) < degree){
  error = degree - sensor_value;
  derivative = error - lasterror;
  integral += error;
  int power = (kP * error) + (kI * integral) + (kD * derivative);
  setDrive(power * direction, -power * direction);
  lasterror = error;
}
setDrive(0,0);
}



void PowerDrive(int power){
    FrontleftDrive = power;
    FrontrightDrive = -power;
    RightmiddleDrive = power;
    LeftmiddleDrive = -power;
    BackrightDrive = -power;
    BackleftDrive = power;
}



void reset(){
FrontleftDrive.tare_position();
BackleftDrive.tare_position();
FrontrightDrive.tare_position();
BackrightDrive.tare_position();
RightmiddleDrive.tare_position();
LeftmiddleDrive.tare_position();
}

void rotate(int degree, int voltage, double numbers){
  int direction = abs(degree) / (degree);
  gyro.reset();
  setDrive(-voltage * direction, voltage * direction);
  while(fabs(gyro.get_value()) < abs(degree * 10)){
    pros::delay(50);
  }
if(fabs(gyro.get_value()) > abs(degree * 10)){
  while(fabs(gyro.get_value()) > abs(degree * 10)){
    setDrive(numbers * voltage * direction, numbers * -voltage * direction);
    pros::delay(50);
  }
}
  else if(fabs(gyro.get_value()) < abs(degree * 10)) {
  while(fabs(gyro.get_value()) > abs(degree * 10)){
    setDrive(numbers * -voltage * direction, numbers * voltage * direction);
    pros::delay(50);
  }
}
setDrive(0,0);
}

void setDrive(int left, int right){
 FrontleftDrive = left;
 BackleftDrive = left;
 LeftmiddleDrive = -left;
 RightmiddleDrive = right;
 FrontrightDrive = -right;
 BackrightDrive = -right;
}


double averagepostion(){
  return (fabs(FrontrightDrive.get_position()) + fabs(FrontleftDrive.get_position()) + fabs(BackleftDrive.get_position()) + fabs(BackrightDrive.get_position()) + fabs(RightmiddleDrive.get_position()) + fabs(LeftmiddleDrive.get_position()))/6;

}

void move(int distance, int power){
  reset();
    int direction = abs(distance) / distance;
gyro.reset();

delay(50);
  while(averagepostion() < abs(distance)){
setDrive(power * direction - gyro.get_value(), power * direction + gyro.get_value());
}
setDrive(direction,direction);


setDrive(-1,1);
  }

  void roller(double distance, double speed){
    intake.tare_position();
  while((fabs(intake.get_position()) <=fabs(distance))){
  intake = speed;
  }
   intake = 0;
  }
  void moveforward(double distance, double power){
  double error;
  FrontleftDrive.tare_position();
  FrontrightDrive.tare_position();
  while((fabs(FrontleftDrive.get_position())+fabs(FrontrightDrive.get_position()))/2 <= fabs(distance)){

    FrontleftDrive = power;
    FrontrightDrive = -power;
    RightmiddleDrive = power;
    LeftmiddleDrive = -power;
    BackrightDrive = -power;
    BackleftDrive = power;

  }
  FrontleftDrive = -1;
  FrontrightDrive = -1;
  BackrightDrive = -1;
  BackleftDrive = -1;
  RightmiddleDrive = -1;
  LeftmiddleDrive = -1;
  }
  void moveback(double distance, double power){
      double error;
      FrontleftDrive.tare_position();
      FrontrightDrive.tare_position();
      while((fabs(FrontleftDrive.get_position())+fabs(FrontrightDrive.get_position()))/2 <= fabs(distance)){

          FrontleftDrive = -power;
          FrontrightDrive = power;
          RightmiddleDrive = -power;
          LeftmiddleDrive = power;
          BackrightDrive = power;
          BackleftDrive = -power;
      }
      FrontleftDrive = -1;
      FrontrightDrive = -1;
      BackrightDrive = -1;
      BackleftDrive = -1;
      }

void cata(int distance, int power){
  catapult2.tare_position();
  while(catapult2.get_position() < distance){
    catapult2 = power;
  }
   catapult2 = 0;
}


 

/*
void turnRight(double degree){
  Inertial.tare_rotation();
  while(Inertial.get_rotation <= degree){
    PowerDrive(0,100);
  }
  PowerDrive(0,0);
}

void PowerDrive(double power,double turn){
          FrontleftDrive = -power + turn;
          FrontrightDrive = power + turn;
          RightmiddleDrive = -power + turn;
          LeftmiddleDrive = power +turn;
          BackrightDrive = power + turn;
          BackleftDrive = -power + turn;
}

/*void driveStraight(double distance, double speed){
  FrontleftDrive.tare_position{};
   double error;
    double kp;
    double Abjustpower ;
    error = 0;
  while(FrontleftDrive.tare_position <= distance){
   error = imu.get_rotation();
   Abjustpower = error * kp;
   BackrightDrive = speed - Abjustpower;
   BackleftDrive = speed - Abjustpower;
   LeftmiddleDrive= speed - Abjustpower;
   FrontrightDrive = speed + Abjustpower;
   FrontleftDrive = speed + Abjustpower;
   RightmiddleDrive = speed + Abjustpower;
  }
  PowerDrive(0,0);
}
*/

