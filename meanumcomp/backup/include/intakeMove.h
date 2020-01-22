void intakeMove(){
    if (con.ButtonUp.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonRight.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    }  
}