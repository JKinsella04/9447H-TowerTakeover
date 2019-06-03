using namespace vex;
#include "vex.h"

double speed = 75;

/*
             ___    ___     ___    _   _    ___     ___             ___     ___     ___     ___   
    o O O   | _ \  / __|   | __|  | | | |  |   \   / _ \    ___    / __|   / _ \   |   \   | __|  
   o        |  _/  \__ \   | _|   | |_| |  | |) | | (_) |  |___|  | (__   | (_) |  | |) |  | _|   
  TS__[O]  _|_|_   |___/   |___|   \___/   |___/   \___/   _____   \___|   \___/   |___/   |___|  
 {======|_| """ |_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|     |_|"""""|_|"""""|_|"""""|_|"""""| 
./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 
*/


/* AUTONOMOUS tasks needed to be performed by robot 
  - go forward // Completed by function fourWheelDrive On 6/3/2019
  - go backward // Completed by function fourWheelDrive On 6/3/2019
  - strafe left // Completed by function strafeleft On 6/3/2019
  - strafe right // Completed by function strafeRight On 6/3/2019
  - turn left  // Completed by function turnLeft On 6/3/2019
  - turn right // Completed by function turnRight On 6/3/2019
  - raise lift // Completed by function lift On 6/3/2019
  - spin the motor(s) on whatever cube grabbing mechanism we use // Completed by function intake On 6/3/2019
  - 
*/

void fourWheelDrive (double ecount, double speed) { // With this function we can use it to move the robot either forwards with a positive ecount or backwards with a negative ecount
    frontleft.resetRotation();    //These four lines reset the encoders in the drive base motors to 0
    frontright.resetRotation();
    backleft.resetRotation();
    backright.resetRotation();
    frontleft.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); //These four lines actually rotate the drive base motors exactly to the encoder postition that is defined by ecount which is the first number you give the function when you call it
    frontright.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backleft.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backright.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); //This line rotates the motor but it will also make the robot wait and not go to the next line of code until this motor gets to the encoder count
}

void strafeRight (double ecount, double speed) {
    frontleft.resetRotation();    //These four lines reset the encoders in the drive base motors to 0
    frontright.resetRotation();
    backleft.resetRotation();
    backright.resetRotation();
    frontleft.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); //The front left motor and back right motor need to go forward and the back left and front right need to go backward for the robot to strafe to the right. The first and last lines make the front left and back right go forward and the second and third lines make the back left and front right motors go backward causing the robot to strafe right.
    frontright.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backleft.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backright.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); 
}

void strafeLeft (double ecount, double speed) {
    frontleft.resetRotation();    //These four lines reset the encoders in the drive base motors to 0
    frontright.resetRotation();
    backleft.resetRotation();
    backright.resetRotation();
    frontleft.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); //The code is the same as the previous function just that the motors are told to the opposite way from before, now front left and back right go backward and front right and back left go forward causing the robot to strafe left.
    frontright.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backleft.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
    backright.rotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct); 
}

void turnRight (double count, double speed) {
   backleft.resetRotation(); //Resets the encoder of the back left motor. This is the motor we are basing our turn off of since it travels the farthest
    if(frontleft.rotation(rotationUnits::deg) < count) { //A Basic if loop where it checks to see if the back left motor encoder is less then the number we introduce into the function (count)
    frontleft.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm); // If it passes the if loop it will begin spinning all the drive base motors the needed way to turn right
    backleft.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm); // It spins the left motors forward and the right motors backwards
    frontright.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    backright.spin(vex::directionType::rev,50,vex::velocityUnits::rpm);
    task::sleep(1000);
    while(backleft.rotation(rotationUnits::deg) < count) { // This while loop checks the speed of the back left motor while the back left motor is not at the wanted position. When it reaches that position it will stop the motors.
        if(backleft.velocity(velocityUnits::dps) < 1) {
            break;
        }
    }
        frontleft.stop();
        backleft.stop();
        frontright.stop();
        backright.stop(); 
    }
}

void turnLeft (double count, double speed) {
   backright.resetRotation(); //Resets the encoder of the back right motor. This is the motor we are basing our turn off of since it travels the farthest
    if(frontleft.rotation(rotationUnits::deg) < count) { //A Basic if loop where it checks to see if the back right motor encoder is less then the number we introduce into the function (count)
    frontleft.spin(vex::directionType::rev,50,vex::velocityUnits::rpm); // If it passes the if loop it will begin spinning all the drive base motors the needed way to turn right
    backleft.spin(vex::directionType::rev,50,vex::velocityUnits::rpm); // It spins the left motors backwards and the right motors forward
    frontright.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    backright.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);
    task::sleep(1000);
    while(backleft.rotation(rotationUnits::deg) < count) { // This while loop checks the speed of the back right motor while the back right motor is not at the wanted position. When it reaches that position it will stop the motors
        if(backleft.velocity(velocityUnits::dps) < 1) {
            break;
        }
    }
        frontleft.stop();
        backleft.stop();
        frontright.stop();
        backright.stop(); 
    }
}

void lift (double ecount, double speed) { // Very basic function where it will reset the encoders on the lift motors and then it will rotate the lift motors until it gets to the wanted position. This function will require the second lift motor to come to a stop before it will continue to the next line of code
  liftmotor1.resetRotation();
  liftmotor2.resetRotation();
  liftmotor1.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  liftmotor2.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void intake (double ecount, double speed) { // Very basic function where it will reset the encoders on the intake motors and then it will rotate the intake motors until it gets to the wanted position. This function will require the second lift motor to come to a stop before it will continue to the next line of code
  intake1.resetRotation();
  intake2.resetRotation();
  intake1.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  intake2.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

/* Driver Control Functions needed for the robot
  - raise lift height 1 L1 // Completed by function liftup On 6/3/2019
  - raise lift height 2 // Completed by function liftup On 6/3/2019
  - intake cubes // Completed by function obtaincube On 6/3/2019
  - release cubes // // Completed by function dispensecube On 6/3/2019
  - mecanum drive base // code in main.cpp
*/
/*
  - Gradual lift L1 up 
  - Gradual Lift l2 down stops at one cube height
  - Exact Lift Intake LEFTARROW starts at cube height 1 then goes down and intakes cube, then return back to one cube height
  - Bring lift to height max while also running intake to dispense cubes
*/

void liftup () {
  if (con.ButtonL1.pressing() ==1) {
    liftmotor1.spin(directionType::fwd, 100,velocityUnits::rpm);
    liftmotor1.spin(directionType::fwd, 100,velocityUnits::rpm);
  }

  else if (con.ButtonL2.pressing() ==1) {
    liftmotor1.spin(directionType::rev, 100,velocityUnits::rpm);
    liftmotor2.spin(directionType::rev, 100,velocityUnits::rpm);
    
    if(Limit.pressing() ==1) {
      liftmotor1.stop();
      liftmotor2.stop();
    }
  }
  
  else  {
    liftmotor1.stop();
    liftmotor2.stop();
  }

}

void obtaincube () {
  if (con.ButtonLeft.pressing() ==1) {
    liftmotor1.startRotateTo(0, rotationUnits::deg, 100,velocityUnits::rpm);
    liftmotor2.startRotateTo(0, rotationUnits::deg, 100,velocityUnits::rpm);
    intake1.spin(directionType::fwd, 200,velocityUnits::rpm);
    intake2.spin(directionType::fwd, 200,velocityUnits::rpm);
    task::sleep(1000);
    intake1.stop();
    intake2.stop();
    liftmotor1.startRotateTo(100, rotationUnits::deg, 100,velocityUnits::rpm);
    liftmotor2.rotateTo(100, rotationUnits::deg, 100,velocityUnits::rpm);
  }
}

void dispensecube () {
  liftmotor1.spin(directionType::fwd, 100,velocityUnits::rpm);
  liftmotor2.spin(directionType::fwd, 100,velocityUnits::rpm);
  intake1.spin(directionType::rev, 200,velocityUnits::rpm);
  intake2.spin(directionType::rev, 200,velocityUnits::rpm);
  
  if (con.ButtonRight.pressing() ==1) {
    liftmotor1.stop();
    liftmotor2.stop();
    intake1.stop();
    intake2.stop();
  }
}