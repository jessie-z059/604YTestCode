#include "main.h"
#include "function.hpp"

using namespace pros;

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
setDrive(-1,-1);
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
Inertial.tare_rotation();

delay(50);
  while(averagepostion() < abs(distance)){
setDrive(power * direction - Inertial.get_rotation(), power * direction + Inertial.get_rotation());
}
setDrive(direction,direction);


setDrive(-3,3);
  }

  void roller(double distance, double speed){
    intake.tare_position();
  while((fabs(intake.get_position()) <=fabs(distance))){
  intake = speed;
  }
   intake = 0;
  }
  

void cata(int distance, int power){
  catapult2.tare_position();
  while(catapult2.get_position() < distance){
    catapult2 = power;
  }
   catapult2 = 0;
}




void PowerDrive(double power,double turn){
	FrontrightDrive =-power + turn;
	BackrightDrive =-power + turn;
	FrontleftDrive =+power + turn;
	BackleftDrive = +power + turn;
	RightmiddleDrive=+power - turn;
	LeftmiddleDrive = -power - turn;
}
void turnRight(double degree, double kP,double kd,double time){
   startTimer(1);
  Inertial.tare_rotation();
  double error; 
  double power;
  double der;
  double last_error;
  
  
  while(Inertial.get_rotation() <= degree || getTime(1) <= time){
    error = degree - Inertial.get_rotation();
   
    der = error -last_error;
    last_error = error;
     power = error*kP + der * kd ;

  PowerDrive(0,power);
}
PowerDrive(0,0);
}
void turnLeft(double degree, double kP,double kd,double time){
   startTimer(1);
  Inertial.tare_rotation();
  double error; 
  double power;
  double der;
  double last_error;
  
  
  while(fabs(Inertial.get_rotation()) <= degree || getTime(1) <= time){
    error = degree - fabs(Inertial.get_rotation());
   
    der = error -last_error;
    last_error = error;
     power = error*kP + der * kd ;

    PowerDrive(0,-power);
  }
  PowerDrive(0,0);
}

  void drive(char direction, double distance, double kp, double Kd, int maxpower){
    if(direction == 'f'){
      startTimer(1);
    Inertial.tare_rotation();
    reset();
    double error;
    double power;
    double der;
    double last_error;
    double integral;

    double turn_error;
    double turn_der;
    double turn_integral;
    double turn_lasterror;
    double turn_power;
    double turn_Kp = 4;
    double turn_Ki = 0;
    double turn_Kd = 1;
  

    while(averagepostion() <= distance ) {
      error = distance - averagepostion();
      der = error - last_error;
      last_error = error;
      power = error * kp + der * Kd;
      if(power >= maxpower){
        power = maxpower;
      }
      else{
        power = power;
      }
      turn_error = Inertial.get_rotation();
      turn_integral += turn_error;
      turn_der = turn_error - turn_lasterror;
      turn_lasterror = turn_error;
      turn_power = turn_Kp * turn_error + turn_integral * turn_Ki + turn_der * turn_Kd;


      PowerDrive(power, -turn_power);


    }
   
    PowerDrive(0,0);
    }
    else if(direction == 'b'){
    Inertial.tare_rotation();
    reset();
    double error;
    double power;
    double der;
    double last_error;
    double integral;

    double turn_error;
    double turn_der;
    double turn_integral;
    double turn_lasterror;
    double turn_power;
    double turn_Kp = 5;
    double turn_Ki = 0;
    double turn_Kd = 1;
  

    while(averagepostion() <= distance ) {
      error = distance - averagepostion();
      der = error - last_error;
      last_error = error;
      power = error * kp + der * Kd;
      if(power >= maxpower){
        power = maxpower;
      }
      else{
        power = power;
      }
      turn_error = Inertial.get_rotation();
      turn_integral += turn_error;
      turn_der = turn_error - turn_lasterror;
      turn_lasterror = turn_error;
      turn_power = turn_Kp * turn_error + turn_integral * turn_Ki + turn_der * turn_Kd;

   
      PowerDrive(-power, -turn_power);


    }
   
    PowerDrive(0,0);
    }
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

