#include "vex.h"
using namespace vex;

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
  TurnGyroSmart.calibrate();
  armMotor.setBrake(hold);
  trayMotor.setBrake(hold);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


void autonomous(void) {
  ////////////////// 9 Point Begin ///////////////////////
  // rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  //   //Toggles the intakes on to pick up cubes
  // driveForward(40, 100);
  //   //Goes forward picking up the preload and the 4 cubes in a row
  // turnLeft(45, 50);
  //   //We turn left after picking up the cubes so we are at the right angle to backup behind the new row of cubes for us to pick up.
  // leftIntake.stop();
  // rightIntake.stop();
  //   //we stop spinning the intakes before we begin backing up.
  // driveBackward(30, 100);
  //   //We go backwards untill the robot is behind the next row of cubes for us to pickup
  // turnRight(45, 50);
    //The robot turns right to face the cubes that we want to pick up
  ////////////////// 5 Point Begin ///////////////////////
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
    //Toggles the intakes on to pick up this row of cubes
  driveForward(40, 50); 
  vex::task::sleep(100);
    //Goes forward so the intakes actually intake cubes
  driveBackward(26, 100);
    //Goes back so we can turn right to face the goal zone at a perfect 45 degree angle
  turnRight(350, 50);
    //Turns right to look towards the goal zone at a 45 degree angle
  leftIntake.stop();
  rightIntake.stop();
    //We stop the intakes before going into the goal goal zones
  vex::task::sleep(100);
  driveForward(14.5, 100);
  trayMotor.rotateTo(1400,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  driveBackward(10, 50);
    //We go forward into the goal zone then stack the 9 cubes and back up after bringing the tray perpindicular to the ground.
  }


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
  //   leftIntake.spin(directionType::fwd);
  //   // double yawValue = TurnGyroSmart.heading();
  //   if(TurnGyroSmart.rotation() >= 90){
  //     // Brain.Screen.printAt(1,30,"yaw",TurnGyroSmart.heading());
  //     leftIntake.stop();
  //   }
  //   else{
  //     leftIntake.spin(directionType::fwd);
  //   }
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    float motor_max = 50;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max;
       
    leftMotorA.spin(fwd,left_power,vex::velocityUnits::pct);
    leftMotorB.spin(fwd,left_power,vex::velocityUnits::pct);
    rightMotorA.spin(fwd,right_power,vex::velocityUnits::pct);
    rightMotorB.spin(fwd,right_power,vex::velocityUnits::pct);
  
    trayTilt();
    intakeSpin();
    armMove();
    wait(20, msec); // Sleep the task for a short amount of time to
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
    wait(100, msec);
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
      armMotor.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonRight.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
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
  leftMotorA.resetRotation();
  rightMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorB.resetRotation();

  leftMotorA.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorA.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  leftMotorB.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorB.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
}

void turnRight(double ecount, double speed) {
    leftMotorA.resetRotation();
  rightMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorB.resetRotation();
  
  leftMotorA.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorA.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  leftMotorB.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorB.rotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
}