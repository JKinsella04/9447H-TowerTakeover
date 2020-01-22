void intakeSpin(){
    if (con.ButtonR1.pressing() == 1) {
      leftintake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      rightintake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (con.ButtonR2.pressing() == 1) {
      leftintake.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
      rightintake.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    } else {
      leftintake.stop();
      rightintake.stop();
    }
    }