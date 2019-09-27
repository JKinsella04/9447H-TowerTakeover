void fourWheelDrive(
    double ecount, double speed) { // With this function we can use it to move
                                   // the robot either forwards with a positive ecount or backwards with a negative ecount
  frontleft.resetRotation(); // These next four lines reset the encoders in the drive base motors to 0
  frontright.resetRotation();
  backleft.resetRotation();
  backright.resetRotation();
  frontleft.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct); // These next four lines actually rotate the drive base motors exactly to the encoder postition
                                // that is defined by ecount which is the first number you give the function when you call it
  frontright.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backleft.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backright.rotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct); // This line rotates the motor but it will also make the robot wait and not go to the next
                                // line of code until this motor gets to the encoder count
}