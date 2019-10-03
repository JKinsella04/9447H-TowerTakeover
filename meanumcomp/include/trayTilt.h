void trayTilt(){
    if (con.ButtonR1.pressing() == 1) {
      traymotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    } else if (con.ButtonR2.pressing() == 1) {
      traymotor.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    } else {
      traymotor.stop();
    }
}