void trayTilt(){
    if (con.ButtonL1.pressing() == 1) {
      traymotor.spin(vex::directionType::fwd, 75, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      traymotor.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    } else {
      traymotor.stop();
    }
}