void intakeSpin(){
    if (con.ButtonL1.pressing() == 1) {
      leftintake.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
      rightintake.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      leftintake.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
      rightintake.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    } else {
      leftintake.stop();
      rightintake.stop();
    }
    }