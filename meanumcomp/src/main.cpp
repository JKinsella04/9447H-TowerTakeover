#include "vex.h"
#include <algorithm>
#include <cmath>
#include "startup.h"
#include "fourWheelDrive.h"
#include "score.h"
#include "trayTilt.h"
#include "intakeSpin.h"

using namespace vex;
vex::competition Competition;

void pre_auton(void) {
  traymotor.setStopping(vex::brakeType::hold);
}

void autonomous(void) {
  // Since we are early in the season we do not have any autonomous programs
  // created to test since we do not have an exact robot design to base an
  // autonomous off of.
  
}

void usercontrol(void) {
  while (true) {
    // Get the raw sums of the X and Y joystick axes
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    float motor_max = 85;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max;
       
    frontleft.spin(fwd,left_power,vex::velocityUnits::pct);
    backleft.spin(fwd,left_power,vex::velocityUnits::pct);
    frontright.spin(fwd,right_power,vex::velocityUnits::pct);
    backright.spin(fwd,right_power,vex::velocityUnits::pct);
    
    trayTilt();
    
    //intakeSpin();
        if (con.ButtonUp.pressing() == 1) {
      leftintake.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
      rightintake.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
    } else if (con.ButtonRight.pressing() == 1) {
      leftintake.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
      rightintake.spin(vex::directionType::rev, 50, vex::velocityUnits::rpm);
    } else {
      leftintake.stop();
      rightintake.stop();
    }
    //if(con.ButtonUp.pressing() ==1) {
      //startup();
    //}
    //if(con.ButtonLeft.pressing() ==1) {
     // score();
   // }
  vex::task::sleep(150);
  //Brain.Screen.clearScreen();
  con.Screen.clearScreen();
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}