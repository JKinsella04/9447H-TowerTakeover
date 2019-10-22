void turnRight(double count, double speed) {
  backleft.resetRotation(); // Resets the encoder of the back left motor. This is the motor we are basing our turn off of since it travels the farthest
  if (frontleft.rotation(vex::rotationUnits::deg) < count) { // A Basic if loop where it checks to see if the back left motor
               // encoder is less then the number we introduce into the function (count)
    frontleft.spin(vex::directionType::fwd, 50,vex::velocityUnits::rpm); // If it passes the if loop it will begin
                                  // spinning all the drive base motors the needed way to turn right
    backleft.spin(vex::directionType::fwd, 50,vex::velocityUnits::rpm); // It spins the left motors forward
                                            // and the right motors backwards
    frontright.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    backright.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    vex::task::sleep(1000);
    while (backleft.rotation(vex::rotationUnits::deg) <
           count) { // This while loop checks the speed of the back left motor
                    // while the back left motor is not at the wanted position. When it reaches that position it will stop the motors.
      if (backleft.velocity(vex::velocityUnits::dps) < 1) {
        break;
      }
    }
    frontleft.stop();
    backleft.stop();
    frontright.stop();
    backright.stop();
  }
}