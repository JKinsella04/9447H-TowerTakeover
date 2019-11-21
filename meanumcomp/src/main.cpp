#include "vex.h"
 // #include <algorithm>
 // #include <cmath>
#include "startup.h"
#include "fourWheelDrive.h"
#include "score.h"
#include "trayTilt.h"
#include "intakeSpin.h"
#include "intake.h"
#include "turnleft.h"
#include "turnright.h"
#include "intakeMove.h"
#include "auton.h"
#include "backup.h"

using namespace vex;
vex::competition Competition;

void pre_auton(void) {
  armMotor.setStopping(vex::brakeType::hold);
}

void autonomous(void) {
 auton();
}

void usercontrol(void) {
  while (true) {
    double effficency = traymotor.efficiency(percentUnits::pct);
    Brain.Screen.clearScreen();
    Brain.Screen.print(effficency);
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    float motor_max = 50;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max;
       
    frontleft.spin(fwd,left_power,vex::velocityUnits::pct);
    backleft.spin(fwd,left_power,vex::velocityUnits::pct);
    frontright.spin(fwd,right_power,vex::velocityUnits::pct);
    backright.spin(fwd,right_power,vex::velocityUnits::pct);
    
    trayTilt();
    
    intakeSpin();

    intakeMove();

    backup();
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