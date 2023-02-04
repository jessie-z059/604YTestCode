#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_

void setDrive(int right, int left);
void rotate(int degree, int voltage, double numbers);
void reset();
void PIDdrive(double target, double kP,double kI, double kD);
void move(int distance, int power);
void roller(double distance, double speed);
void moveback(double distance, double power);
void moveforward(double distance, double power);
void driveStraight(double distance, double speed);
void turnRight(double degree);
void cata(int distance, int power);
void move2(double distance_drive, double power_drive, int distance_roller, int power_roller);
void PowerDrive(int power);
double averagepostion();
void PIDturn(double target, double kP, double kI, double kD);

#endif
