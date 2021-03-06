//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "vex.h"
using namespace vex;

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
int debug() { /* This is a Task that will start running before the match starts in the Pre-Auton phase 
                 that will just be a debug screen that runs throughout the match in the background */
    /* variables for temperatures for the motors in celsius 
      These are just estimate right now will need tests to know what temps are "cool", "warm", and "hot"*/
    double cool = 0; 
    double warm = 50;
    double hot = 70;
    Brain.Screen.setPenWidth(3); /* Increases the size of the text to be easier to read */
    while(true){
      Brain.Screen.clearScreen();
      /* These 3 if statements will compare the temperature of the tilter motor. if it is between 0 and 50 degrees Celsius it will be "cool" 
          and will display the temp in green and create a green circle on the Cortex screen. Then if it is between 50 and 70 degrees it will be "warm"
          and will display everything in orange. Then if it is over 70 degrees it will be "hot" and will display everything in red */
      if(tilter.temperature(vex::temperatureUnits::celsius) >= cool) {
        Brain.Screen.setPenColor(color::green);
        Brain.Screen.printAt(2, 30, "Tilter Temp:%f",tilter.temperature(vex::temperatureUnits::celsius));
        Brain.Screen.drawCircle(100, 100, 20, green);
      }
      if(tilter.temperature(vex::temperatureUnits::celsius) >= warm) {
        Brain.Screen.setPenColor(color::orange);
        Brain.Screen.printAt(2, 30, "Tilter Temp:%f",tilter.temperature(vex::temperatureUnits::celsius));
        Brain.Screen.drawCircle(100, 100, 20, orange);
      }
      if(tilter.temperature(vex::temperatureUnits::celsius) >= hot) {
        Brain.Screen.setPenColor(color::red);
        Brain.Screen.printAt(2, 30, "Tilter Temp:%f",tilter.temperature(vex::temperatureUnits::celsius));
        Brain.Screen.drawCircle(100, 100, 20, red);
      }
      Brain.Screen.render();
      vex::task::sleep(20);

    }
  return 0;
}

void score() {
  if(con.ButtonL1.pressing() ==1) {
    /*
    move the Tray Tilter to {ENCODER COUNT} to be perpindicular to the ground
    while also slighty spinning the intake motor reverse to allow the cube at the bottom of the stack to be realeased
    back up
    */
    tilter.startRotateTo(540, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
    leftintake.spin(directionType::rev);
    rightintake.spin(directionType::rev);
    vex::task::sleep(500);
    leftintake.stop();
    rightintake.stop();
    fourWheelDrive(-250, 50);
    
  }
}

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

void strafeRight(double ecount, double speed) {
  frontleft.resetRotation(); // These four lines reset the encoders in the drive base motors to 0
  frontright.resetRotation();
  backleft.resetRotation();
  backright.resetRotation();
  frontleft.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct); // The front left motor and back right motor need to go forward
                // and the back left and front right need to go backward for the
                // robot to strafe to the right. The first and last lines make the front left and back right go forward and the second and
                // third lines make the back left and front right motors go backward causing the robot to strafe right.
  frontright.startRotateTo(-ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backleft.startRotateTo(-ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backright.rotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void strafeLeft(double ecount, double speed) {
  frontleft.resetRotation(); // These four lines reset the encoders in the drive base motors to 0
  frontright.resetRotation();
  backleft.resetRotation();
  backright.resetRotation();
  frontleft.startRotateTo(-ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct); // The code is the same as the previous function
                                // just that the motors are told to the opposite
                                // way from before, now front left and back right
                                // go backward and front right and back left go
                                // forward causing the robot to strafe left.
  frontright.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backleft.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  backright.rotateTo(-ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void turnRight(double count, double speed) {
  backleft.resetRotation(); // Resets the encoder of the back left motor. This is the motor we are basing our turn off of since it travels the farthest
  if (frontleft.rotation(rotationUnits::deg) < count) { // A Basic if loop where it checks to see if the back left motor
               // encoder is less then the number we introduce into the function (count)
    frontleft.spin(vex::directionType::fwd, 50,vex::velocityUnits::rpm); // If it passes the if loop it will begin
                                  // spinning all the drive base motors the needed way to turn right
    backleft.spin(vex::directionType::fwd, 50,vex::velocityUnits::rpm); // It spins the left motors forward
                                            // and the right motors backwards
    frontright.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    backright.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    task::sleep(1000);
    while (backleft.rotation(rotationUnits::deg) <
           count) { // This while loop checks the speed of the back left motor
                    // while the back left motor is not at the wanted position. When it reaches that position it will stop the motors.
      if (backleft.velocity(velocityUnits::dps) < 1) {
        break;
      }
    }
    frontleft.stop();
    backleft.stop();
    frontright.stop();
    backright.stop();
  }
}

void turnLeft(double count, double speed) {
  backright.resetRotation(); // Resets the encoder of the back right motor. This
                             // is the motor we are basing our turn off of since it travels the farthest
  if (frontleft.rotation(rotationUnits::deg) <
      count) { // A Basic if loop where it checks to see if the back right motor
               // encoder is less then the number we introduce into the function (count)
    frontleft.spin(vex::directionType::rev, 50,vex::velocityUnits::rpm); // If it passes the if loop it will begin
                                  // spinning all the drive base motors the needed way to turn right
    backleft.spin(vex::directionType::rev, 50,vex::velocityUnits::rpm); // It spins the left motors backwards and the right motors forward
    frontright.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    backright.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    task::sleep(1000);
    while (backleft.rotation(rotationUnits::deg) < count) { // This while loop checks the speed of the back right motor
                    // while the back right motor is not at the wanted position. When it reaches that position it will stop the motors
      if (backleft.velocity(velocityUnits::dps) < 1) {
        break;
      }
    }
    frontleft.stop();
    backleft.stop();
    frontright.stop();
    backright.stop();
  }
}

void lift(double ecount,double speed) { // Very basic function where it will reset the encoders on
                    // the lift motors and then it will rotate the lift motors until it gets to the wanted position. This function will
                    // require the second lift motor to come to a stop before it will continue to the next line of code
  traymotor.resetRotation();
  traymotor.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void intake(double ecount,double speed) { // Very basic function where it will reset the encoders on
                    // the intake motors and then it will rotate the intake motors until it gets to the wanted position. This
                    // function will require the second lift motor to come to a stop before it will continue to the next line of code
  leftintake.resetRotation();
  rightintake.resetRotation();
  leftintake.startRotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightintake.rotateTo(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
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
    traymotor.spin(directionType::fwd, 100,velocityUnits::rpm);
    traymotor.spin(directionType::fwd, 100,velocityUnits::rpm);
  }

  else if (con.ButtonL2.pressing() ==1) {
    traymotor.spin(directionType::rev, 100,velocityUnits::rpm);
    
    if(Limit.pressing() ==1) {
      traymotor.stop();
    }
  }
  
  else  {
    traymotor.stop();
  }

}

void obtaincube () {
  if (con.ButtonLeft.pressing() ==1) {
    /*
    traymotor.startRotateTo(0, rotationUnits::deg, 100,velocityUnits::rpm);
    .startRotateTo(0, rotationUnits::deg, 100,velocityUnits::rpm);
    */
    leftintake.spin(directionType::fwd, 200,velocityUnits::rpm);
    rightintake.spin(directionType::fwd, 200,velocityUnits::rpm);
    //task::sleep(1000);
    //leftintake.stop();
    //rightintake.stop();
    /*
    traymotor.startRotateTo(100, rotationUnits::deg, 100,velocityUnits::rpm);
    .rotateTo(100, rotationUnits::deg, 100,velocityUnits::rpm);
    */
  }
  else if (con.ButtonRight.pressing() ==1) {
    leftintake.spin(directionType::rev, 200,velocityUnits::rpm);
    rightintake.spin(directionType::rev, 200,velocityUnits::rpm);
  }

  else {
    leftintake.stop();
    rightintake.stop();
  }
}

void scorecube () {
  if(con.ButtonR2.pressing() ==1) {
    traymotor.rotateFor(200, vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
    traymotor.startRotateFor(-200, vex::rotationUnits::deg, 50,vex::velocityUnits::pct);
    fourWheelDrive(-200, 50);
  }
  }
void moveTray () {

     if(con.ButtonL1.pressing()==1 ) {
      traymotor.spin(directionType::fwd, 50, velocityUnits::pct);
     }
     else if(con.ButtonL2.pressing()==1) {
       traymotor.spin(directionType::rev, 50,velocityUnits::pct);
     }
    else{
      traymotor.stop();
    }
     }
  

