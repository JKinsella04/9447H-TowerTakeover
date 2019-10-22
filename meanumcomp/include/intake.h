void intake(double ecount,double speed) { // Very basic function where it will reset the encoders on
                    // the intake motors and then it will rotate the intake motors until it gets to the wanted position. This
                    // function will require the second lift motor to come to a stop before it will continue to the next line of code
  leftintake.resetRotation();
  rightintake.resetRotation();
  leftintake.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightintake.rotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}