void intakeMove(){
    if (con.ButtonL1.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    }  
}