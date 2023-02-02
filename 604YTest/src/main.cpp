#include "main.h"

using namespace pros;

Motor FrontrightDrive(20);
Motor FrontleftDrive(8);
Motor BackrightDrive(17);
Motor BackleftDrive(4);
Motor RightmiddleDrive(19);
Motor catapult2(21);
Motor LeftmiddleDrive(7);
Motor intake(5);
Controller master(E_CONTROLLER_MASTER);
Imu Inertial(2);
ADIGyro gyro(6);
ADIDigitalOut expansion(2);
ADIDigitalIn limit(1);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	
	pros::lcd::register_btn1_cb(on_center_button);
	gyro.reset();
	delay(50);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}






/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(){

  lcd::print(1,"IMU get rotation: %f degrees", Inertial.get_rotation());
	lcd::print(3,"Gyro: %f degrees", gyro.get_value());
	delay(50);
		
move(-100,50); //move back
roller(500,127); //do 1st roller
delay(500);
move(2000,50); //move forward
delay(1000);
rotate(13,45,0.5); //aim at basket
delay(500);
cata(500,80); 
delay(500);
cata(4700,90);
delay(500);
move(-130,50); //back up
delay(500);
rotate(119,45,0.5); //turn to intake discs
intake=127;
move(-2000,30);
rotate(-75,45,0.5);
delay(500);
cata(500,80);
delay(500);
cata(4700,90);
rotate(80,45,0.5);
move(-300,100);
delay(500);
move(-500,50);
delay(500);
rotate(-58,60,0.5);
delay(500);
move(-50,50);
delay(500);
rotate(8,45,0.5);
move(1300,50);
delay(500);
cata(500,80);
delay(500);
cata(4700,90);

/*
rotate(-90,60,0.4); //turn left to 2nd roller
delay(500);
move(-700,40);
roller(600,127); //do 2nd roller
delay(500);
move(150,50);
delay(100);
rotate(105,60,0.7);
delay(500);
intake=127;
move(-850,55);
delay(2000);
move(2300,60);
delay(500);
rotate(-5,50,0.5);
delay(500);
cata(500,80);
delay(500);
cata(5000,80);
move(-500,60);
rotate(-90,60,0.5);
move(3000,70);
*/






//red roller
/*moveback(150,30);
delay(300);
roller(250,-127);*/
//blue roller
/*moveback(150,30);
delay(500);
roller(200,127);
*/
}
// shoot (500,80) delay(500) reload(4690,80)

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol(){
	int start=0;
	int catstate= 0;
while(true){
lcd::print(1,"IMU get rotation: %f degrees", Inertial.get_rotation());
	lcd::print(3,"Gyro: %f degrees", gyro.get_value());
	
	delay(50);

	int leftY = master.get_analog(ANALOG_LEFT_Y);
	int rightX = master.get_analog(ANALOG_RIGHT_X);
	FrontrightDrive =-leftY +rightX;
	BackrightDrive =-leftY +rightX;
	FrontleftDrive =+leftY +rightX;
	BackleftDrive = +leftY +rightX;
	RightmiddleDrive=+leftY -rightX;
	LeftmiddleDrive = -leftY - rightX;

		if(limit.get_value() == 1 && (millis() - start>1)){
			catstate = 1;
		}
		if(master.get_digital(DIGITAL_R1) ==1 && catstate == 1){
			catstate = 2;
		}
		if(catstate == 0){

			catapult2 = 100;
		}
		if (catstate == 1){

			catapult2=0;
			// catapult1.move_relative(0,20);
			// catapult2.move_relative(0,20);
		}
		else if (catstate == 2){

			catapult2 = 127;
		}

		if(limit.get_value()==0 && catstate != 1){
			catstate = 0;
			start = millis();
}



//intake
		if(master.get_digital(DIGITAL_R2) ==1){

			intake=-127;
}
else if(master.get_digital(DIGITAL_L1) ==1){

	intake=127;
}
			else{

				intake=0;
			}

		if(master.get_digital(DIGITAL_X) ==1){
			expansion.set_value(1);
		}
		else{
			expansion.set_value(0);
		}



}
}



