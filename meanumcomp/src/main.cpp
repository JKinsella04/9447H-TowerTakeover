// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

// // ---- START VEXCODE CONFIGURED DEVICES ----
// // Robot Configuration:
// // [Name]               [Type]        [Port(s)]
// // ---- END VEXCODE CONFIGURED DEVICES ----
// #include "vex.h"
//  // #include <algorithm>
//  // #include <cmath>
// #include "startup.h"
// #include "fourWheelDrive.h"
// #include "score.h"
// #include "trayTilt.h"
// #include "intakeSpin.h"
// #include "intake.h"
// #include "turnleft.h"
// #include "turnright.h"
// #include "intakeMove.h"
// #include "auton.h"
// #include "backup.h"
// 
// using namespace vex;
// vex::competition Competition;
// 
// void pre_auton(void) {
//   armMotor.setStopping(vex::brakeType::hold);
//   leftintake.setStopping(vex::brakeType::coast);
//   rightintake.setStopping(vex::brakeType::coast);
// }
// 
// void autonomous(void) {
// //  auton();
// //  vex::task::sleep(500);
//   fourWheelDrive(-300, 75);
// //    intake(-600, 75);
//  fourWheelDrive(300, 75);
// //  vex::task::sleep(1000);
// 
// }
// 
// void usercontrol(void) {
//   while (true) {
//     double effficency = traymotor.efficiency(percentUnits::pct);
//     Brain.Screen.clearScreen();
//     Brain.Screen.print(effficency);
//     float max = 127.0;
//     float left_percent = con.Axis3.value()/max;
//     float right_percent = con.Axis2.value()/max;
//        
//     float left_new_percent = left_percent * left_percent * left_percent;
//     float right_new_percent = right_percent * right_percent * right_percent;
//        
//     float motor_max = 50;
//     int left_power = left_new_percent * motor_max;
//     int right_power = right_new_percent * motor_max;
//        
//     frontleft.spin(fwd,left_power,vex::velocityUnits::pct);
//     backleft.spin(fwd,left_power,vex::velocityUnits::pct);
//     frontright.spin(fwd,right_power,vex::velocityUnits::pct);
//     backright.spin(fwd,right_power,vex::velocityUnits::pct);
//     
//     trayTilt();
//     
//     intakeSpin();
// 
//     intakeMove();
// 
//     backup();
//   }
// }
// 
// int main() {
//   // Set up callbacks for autonomous and driver control periods.
//   Competition.autonomous(autonomous);
//   Competition.drivercontrol(usercontrol);
//   // Run the pre-autonomous function.
//   pre_auton();
//   // Prevent main from exiting with an infinite loop.
//   while (1) {
//     vex::task::sleep(20); // Sleep the task for a short amount of time to
//                            // prevent wasted resources.
//   }
// }