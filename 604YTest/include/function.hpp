#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_
void driveStraight(double distance, double speed);
void setDrive(int right, int left);
void rotate(int degree, int voltage, double numbers);
void reset();
void PIDdrive(double target, double kP,double kI, double kD);
void move(int distance, int power);
void roller(double distance, double speed);
void moveback(double distance, double power);
void moveforward(double distance, double power);
void turnRight(double degree);
void cata(int distance, int power);
void drive_forward(double target, double speed);
void move2(double distance_drive, double power_drive, int distance_roller, int power_roller);
double averagepostion();
void PIDturn(double target, double kP, double kI, double kD);
void PowerDrive(double power,double turn);
void turnLeft(double degree, double kP,double kd);
void drive(double distance, double kp, double Ki, double Kd);
void turnRight(double degree, double kP,double kd);



#endif
