void moveIntake() {
  if(con.ButtonUp.pressing() ==1) {
    intakearm.startRotateTo(500,vex::rotationUnits::deg, 50,vex::velocityUnits::rpm);
    traymotor.rotateTo(400,vex::rotationUnits::deg,50,vex::velocityUnits::rpm);
  }
  else if(con.ButtonUp.pressing() ==1 && intakearm.rotation(vex::rotationUnits::deg) >= 150) {
    intakearm.startRotateTo(0,vex::rotationUnits::deg, 50,vex::velocityUnits::rpm);
    traymotor.rotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::rpm);
  }
}