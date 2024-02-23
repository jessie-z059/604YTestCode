#include "main.h"

/*void drive_forward(double target, double speed){
    double error = target;
    double integral = 0;
    double derivative = 0;
    double past_error = error;
    double output = 0;

    //tuned variables
    double integral_limit = 6;
    double kp = 0;
    double ki = 0;
    double kd = 0;

    //set our sensor to zero at the start
    drive_motor.tare_position();
    
    while(true){
        // error = target - current
        error = target - drive_motor.get_position();

        //if the error is within the integral_limit then calculate integral
        if (fabs(error) <= integral_limit){
            integral += error;
        }
        else {
            integral = 0;
        }

        //derivative = current - past
        derivative = error - past_error;
        past_error = error;

        //calculate PID output
        output = (error * kp) + (integral * ki) + (derivative * kd);

        //set the motor power to be the output
        drive_motor = set_voltage(output);

        //find exit conditions etc.
    }
}
*/