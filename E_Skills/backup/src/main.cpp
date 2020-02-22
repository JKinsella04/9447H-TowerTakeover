#include "vex.h"

void trayTilt();
void intakeSpin();
void armMove();


void driveForward(double ecount, double speed);
void driveBackward(double ecount, double speed);
void intake(double ecount, double speed);
void turnLeft(double count, double speed);
void turnRight(double count, double speed);

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


void autonomous(void) {
 // fourWheelDrive(200,100);
  // fourWheelDrive(-100, 50);
  // vex::task::sleep(200);
  // intake(-600, 75);
  // armMotor.rotateTo(0,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  // vex::task::sleep(500);
  // armMotor.rotateFor(-100,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  driveForward(1200, 30); 
  vex::task::sleep(200);
  turnRight(450, 50);   
  driveForward(1150, 60);
  rightIntake.stop();
  leftIntake.stop();
  turnLeft(50,75);
  driveBackward(-25, 50);
  rightIntake.startRotateFor(-200,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  leftIntake.rotateFor(-200,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  trayMotor.startRotateTo(3900,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  vex::task::sleep(2000);
  vex::task::sleep(4000);
  // fourWheelDrive(100, 50);
  driveBackward(-300, 30);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    trayTilt();
    intakeSpin();
    armMove();
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::task::sleep(100);
  }
}

void trayTilt(){
    if (con.ButtonL1.pressing() == 1) {
      trayMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      trayMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
    } else {
      trayMotor.stop();
    }
}

void intakeSpin(){
    if (con.ButtonR1.pressing() == 1) {
      leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (con.ButtonR2.pressing() == 1) {
      leftIntake.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    } else {
      leftIntake.stop();
      rightIntake.stop();
    }
}

void armMove(){
    if (con.ButtonUp.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonRight.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    }  
}

void driveForward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::fwd, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void driveBackward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::rev, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void intake(double ecount,double speed) { // Very basic function where it will reset the encoders on
                    // the intake motors and then it will rotate the intake motors until it gets to the wanted position. This
                    // function will require the second lift motor to come to a stop before it will continue to the next line of code
  leftIntake.resetRotation();
  rightIntake.resetRotation();
  leftIntake.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightIntake.rotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void turnLeft(double ecount, double speed) {
  Drivetrain.turnFor(turnType::left, ecount , rotationUnits::deg, speed, velocityUnits::rpm);
}

void turnRight(double ecount, double speed) {
  Drivetrain.turnFor(turnType::right, ecount, rotationUnits::deg, speed, velocityUnits::rpm);
}
