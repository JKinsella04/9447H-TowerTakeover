#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
void auton() {
  fourWheelDrive(200, 75);
  vex::task::sleep(200);
  intake(-500, 75);
  armMotor.rotateTo(-100,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  rightintake.spin(vex::directionType::fwd, 200,vex::velocityUnits::rpm);
  leftintake.spin(vex::directionType::fwd, 200,vex::velocityUnits::rpm);
  fourWheelDrive(1000, 30); 
  rightintake.stop();
  leftintake.stop();
  //Perfect Here
  turnLeft(120, 50);
  //Pefect Here
  fourWheelDrive(1000, 75);
  score(); // Make this work
}