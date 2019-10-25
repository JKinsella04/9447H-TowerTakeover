void auton() {
  fourWheelDrive(200,100);
  fourWheelDrive(-100, 50);
  vex::task::sleep(200);
  intake(-600, 75);
  armMotor.rotateTo(0,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  vex::task::sleep(100);
  armMotor.rotateFor(-50,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  rightintake.spin(vex::directionType::fwd, 200,vex::velocityUnits::rpm);
  leftintake.spin(vex::directionType::fwd, 200,vex::velocityUnits::rpm);
  fourWheelDrive(1150, 30); 
  vex::task::sleep(100);
  rightintake.stop();
  leftintake.stop();
  vex::task::sleep(200);
  //Perfect Here
  turnLeft(515, 50);
  //Pefect Here
  fourWheelDrive(1000, 75);
  score(); // Make this work
}