#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_
void setDrive(int right, int left);
void rotate(int degree, int voltage, double numbers);
void reset();
void move(int distance, int power);
void roller(double distance, double speed);
void cata(int distance, int power);
double averagepostion();
void PowerDrive(double power,double turn);
void turnLeft(double degree, double kP,double kd,double time);
void drive(char direction, double distance, double kp, double Kd, int maxpower);
void turnRight(double degree, double kP,double kd, double time);



#endif
