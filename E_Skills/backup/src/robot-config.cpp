#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT11, ratio18_1, false);
motor leftMotorB = motor(PORT17, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

motor rightMotorA = motor(PORT13, ratio18_1, true); 
motor rightMotorB = motor(PORT9, ratio18_1, true); 
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 292.09999999999997, 190.5, mm, 1);
controller con = controller();
motor trayMotor = motor(PORT16, ratio36_1, false);
motor leftIntake = motor(PORT12, ratio18_1, false);
motor rightIntake = motor(PORT4, ratio18_1, true);
motor armMotor = motor(PORT10, ratio36_1, true);

// VEXcode generated functions
// define variables used for controllinfg motors based on controller inputs
bool conLeftShoulderControlMotorsStopped = true;
bool conRightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_con = true;
bool DrivetrainRNeedsToBeStopped_con = true;

// define a task that will handle monitoring inputs from con
int rc_auto_loop_callback_con() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3
    // right = Axis2
    int drivetrainLeftSideSpeed = con.Axis3.position();
    int drivetrainRightSideSpeed = con.Axis2.position();
    // check if the value is inside of the deadband range
    if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
      // check if the left motor has already been stopped
      if (DrivetrainLNeedsToBeStopped_con) {
        // stop the left drive motor
        LeftDriveSmart.stop();
        // tell the code that the left motor has been stopped
        DrivetrainLNeedsToBeStopped_con = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
      DrivetrainLNeedsToBeStopped_con = true;
    }
    // check if the value is inside of the deadband range
    if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
      // check if the right motor has already been stopped
      if (DrivetrainRNeedsToBeStopped_con) {
        // stop the right drive motor
        RightDriveSmart.stop();
        // tell the code that the right motor has been stopped
        DrivetrainRNeedsToBeStopped_con = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
      DrivetrainRNeedsToBeStopped_con = true;
    }
    // only tell the left drive motor to spin if the values are not in the deadband range
    if (DrivetrainLNeedsToBeStopped_con) {
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    }
    // only tell the right drive motor to spin if the values are not in the deadband range
    if (DrivetrainRNeedsToBeStopped_con) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }
    // check the ButtonL1/ButtonL2 status to control trayMotor

    // check the ButtonR1/ButtonR2 status to control leftIntake
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_con(rc_auto_loop_callback_con);
}