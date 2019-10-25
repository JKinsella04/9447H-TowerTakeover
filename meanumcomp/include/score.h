void score() {
  frontleft.spin(vex::fwd,50,vex::velocityUnits::pct);
  frontright.spin(vex::fwd,20,vex::velocityUnits::pct);
  backleft.spin(vex::fwd,50,vex::velocityUnits::pct);
  backright.spin(vex::fwd,20,vex::velocityUnits::pct);
  vex::task::sleep(500);
  frontleft.stop();
  frontright.stop();
  backleft.stop();
  backright.stop();
  traymotor.rotateFor(2700,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);  
  traymotor.startRotateTo(0,vex::rotationUnits::deg, 50,vex::velocityUnits::rpm);
  vex::task::sleep(2000);
  leftintake.spin(vex::directionType::rev, 30, vex::velocityUnits::rpm);
  rightintake.spin(vex::directionType::rev, 30, vex::velocityUnits::rpm);
  vex::task::sleep(300);
  fourWheelDrive(-500, 50);
  leftintake.stop();
  rightintake.stop();

}