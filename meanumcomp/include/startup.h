void startup() {
  traymotor.rotateTo(300,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  //vex::task::sleep(20);
  // traymotor.startRotateTo(0,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  // armMotor.rotateTo(-200,vex::rotationUnits::deg, 75,vex::velocityUnits::rpm);
  }