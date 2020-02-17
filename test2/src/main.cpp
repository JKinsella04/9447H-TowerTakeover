#include "vex.h"
using namespace vex;

float motor_max = 100;
bool arm = 0;
double speed[5] = {10,15,20,35,50};

void intakeSpin();
void armMove();
void smartTrayTilt();
void arrayTilt();
void brakes();
void resetBrakes();

void driveForward(double ecount, double speed);
void driveBackward(double ecount, double speed);
void intake(double ecount, double speed);
void turnLeft(double count, double speed);
void turnRight(double count, double speed);
void ddtrain(double ecount, double speed);

int controlType();

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  TurnGyroSmart.calibrate();
  armMotor.setBrake(hold);
  trayMotor.setBrake(hold);
  leftIntake.setBrake(hold);
  rightIntake.setBrake(hold);
}


void autonomous(void) {
  ////////////////// 9 Point Begin ///////////////////////
  // rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // vex::task::sleep(2000);
  //   //Toggles the intakes on to pick up cubes
  // driveForward(40, 50);
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
  //  /*
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // vex::task::sleep(2000);
    //Toggles the intakes on to pick up this row of cubes
  driveForward(45, 50); 
  vex::task::sleep(100);
    //Goes forward so the intakes actually intake cubes
  driveBackward(30, 100);
    //Goes back so we can turn right to face the goal zone at a perfect 45 degree angle
  turnRight(345, 75); //Red 450 Blue 360
    //Turns right to look towards the goal zone at a 45 degree angle
  leftIntake.stop();
  rightIntake.stop();
    //We stop the intakes before going into the goal goal zones
  vex::task::sleep(100);
  intake(-400, 100);
  trayMotor.startRotateTo(1100,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  driveForward(11, 100);
  vex::task::sleep(1500);
  // */
  
  // vex::task::sleep(100);
  // ddtrain(100, 100);
  // vex::task::sleep(500);
  driveBackward(10, 50);
  // driveForward(2, 75);
  
  /**/
    //We go forward into the goal zone then stack the 9 cubes and back up after bringing the tray perpindicular to the ground.
  }


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    // float motor_max = 100;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max;
       
    leftMotorA.spin(fwd,left_power,vex::velocityUnits::pct);
    leftMotorB.spin(fwd,left_power,vex::velocityUnits::pct);
    rightMotorA.spin(fwd,right_power,vex::velocityUnits::pct);
    rightMotorB.spin(fwd,right_power,vex::velocityUnits::pct);
  
    controlType();
    // smartTrayTilt();
    arrayTilt();
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

/*
int cubes() {
  if (LineSensor1.value(analogUnits::mV) == 25){
      motor_max = 75;
  }
  return 0;
}
*/

int controlType() {
  if(con.ButtonA.pressing() == 1){
    arm = 1;
    con.Screen.clearScreen();
    con.Screen.print("Set Adjustment");
  }
  else if (con.ButtonX.pressing() == 1) {
    arm = 0;
    con.Screen.clearScreen();
    con.Screen.print("Smooth Adjustment");
  }
  return 0;
}

void brakes(){
  leftIntake.setBrake(coast);
  rightIntake.setBrake(coast);
  leftMotorA.setBrake(hold);
  leftMotorB.setBrake(hold);
  rightMotorA.setBrake(hold);
  rightMotorB.setBrake(hold);
}
void resetBrakes(){
  leftIntake.setBrake(hold);
  rightIntake.setBrake(hold);
  leftMotorA.setBrake(coast);
  leftMotorB.setBrake(coast);
  rightMotorA.setBrake(coast);
  rightMotorB.setBrake(coast);
}

void smartTrayTilt(){
    if (con.ButtonLeft.pressing() == 1) {
      brakes();
      trayMotor.spin(vex::directionType::fwd, 10, vex::velocityUnits::rpm);
      if(trayMotor.rotation(rotationUnits::deg) >= 300) {
        trayMotor.spin(vex::directionType::fwd, 10, vex::velocityUnits::rpm);
      }
    } else if (con.ButtonRight.pressing() == 1) {
      trayMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::rpm);
    } else {
      trayMotor.stop();
      resetBrakes();
    }
}

void arrayTilt(){
  if(con.ButtonLeft.pressing() == 1) {
    for (int i = 0; i < 5; i++) {
      trayMotor.spin(vex::directionType::fwd, speed[i],vex::velocityUnits::rpm);
      speed[ i ] = i + 1;
      vex::task::sleep(100);
    }
  } else if (con.ButtonRight.pressing() == 1) {
      trayMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::rpm);
    } else {
      trayMotor.stop();
      resetBrakes();
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
  if(arm == 0) {
    if (con.ButtonL1.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
      if (armMotor.position(rotationUnits::deg) <= 200) {
        armMotor.stop();
      }
    } else {
      armMotor.stop();
    } 
  }
  else if (arm == 1) {
    if (con.ButtonL1.pressing() == 1) {
      armMotor.rotateFor(500, vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      armMotor.rotateFor(350, vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    } 
  } 
}

void driveForward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::fwd, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void driveBackward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::rev, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void intake(double ecount,double speed) { //spins both intakes for the specified encoder count. continues to next line of code after the right intake finishes spinning.
  leftIntake.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightIntake.rotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
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

void ddtrain(double ecount, double speed){ //go forward with and go to next line of code
  leftMotorA.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  leftMotorB.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightMotorA.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightMotorB.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}