void auton() {
  // fourWheelDrive(200,100);
  // fourWheelDrive(-100, 50);
  // vex::task::sleep(200);
  // intake(-600, 75);
  // armMotor.rotateTo(0,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  // vex::task::sleep(500);
  // armMotor.rotateFor(-100,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  rightintake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  leftintake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  fourWheelDrive(1200, 30); 
  // vex::task::sleep(500);
  //Perfect Here
  
  vex::task::sleep(200);
   turnRight(450, 50);
  //Pefect Here
   
   fourWheelDrive(1150, 60);
   rightintake.stop();
  leftintake.stop();
   turnLeft(50,75);
    fourWheelDrive(-25, 50);
     rightintake.startRotateFor(-200,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
   leftintake.rotateFor(-200,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
   traymotor.startRotateTo(3900,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
   vex::task::sleep(2000);
   score();
}