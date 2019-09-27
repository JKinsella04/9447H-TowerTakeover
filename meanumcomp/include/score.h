void score() {
  traymotor.startRotateFor(500,vex::rotationUnits::deg, 50,vex::velocityUnits::rpm);
  leftintake.spin(vex::directionType::fwd, 30, vex::velocityUnits::rpm);
  rightintake.spin(vex::directionType::fwd, 30, vex::velocityUnits::rpm);
  vex::task::sleep(2000);
  traymotor.startRotateTo(0,vex::rotationUnits::deg, 50,vex::velocityUnits::rpm);
  fourWheelDrive(-100, 10);
  leftintake.stop();
  rightintake.stop();

}