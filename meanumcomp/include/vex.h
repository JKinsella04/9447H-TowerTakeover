#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "v5.h"
#include "v5_vcs.h"
/*
  Here we include 6 header files that are required for the code we write to work
  when given to the cortex. These includes are automatically added when creating
  a vexcode project. Lines 12-21 are the lines that define our motors in the vex
  motor class. The motor class is defined in a separate document that is made from installing vex code
  (A class in C++ is a user defined type or data structure declared
  with keyword class that has data and functions)
  We create objects in the motor's class to make motors, controllers in the controller's class and brains in the brain's class.
  From doing this we are creating an object in the motor class. When doing this we are able to name the object anything and it will take the 
  object and be able to run any function that is defined in the motor class.
  An example of this would be 
    vex::motor frontright (vex::PORT19, vex::gearSetting::ratio18_1,true);
  Then in main.cpp
    frontleft.spin(fwd, front_left, velocityUnits::pct);
  Since we first created the object frontright in the motor class we were later able to make the object execute a function from the motor class

  After creating the motor controller and brain we also create objects in all of the pwm ports on the cortex so we can plug our LEDs in any port to make them light up
  But on Port A for the 3 wire ports we do have to create an object in the limit switch class because we might use a limit switch for our intake.
*/

 vex::brain Brain;
vex::motor frontright (vex::PORT13, vex::gearSetting::ratio18_1,true);
vex::motor frontleft (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor backright (vex::PORT9, vex::gearSetting::ratio18_1,true);
vex::motor backleft (vex::PORT17, vex::gearSetting::ratio18_1,false);
vex::motor traymotor (vex::PORT16, vex::gearSetting::ratio36_1,false);
vex::motor leftintake (vex::PORT12, vex::gearSetting::ratio36_1,false);
vex::motor rightintake (vex::PORT4, vex::gearSetting::ratio36_1,true);
vex::motor armMotor (vex::PORT10, vex::gearSetting::ratio36_1,true);
vex::controller con(vex::controllerType::primary);

// vex::limit Limit = vex::limit(Brain.ThreeWirePort.A);
// vex::pwm_out Pwm_outb = vex::pwm_out(Brain.ThreeWirePort.B);
// vex::pwm_out Pwm_outc = vex::pwm_out(Brain.ThreeWirePort.C);
// vex::pwm_out Pwm_outd = vex::pwm_out(Brain.ThreeWirePort.D);
// vex::pwm_out Pwm_oute = vex::pwm_out(Brain.ThreeWirePort.E);
// vex::pwm_out Pwm_outf = vex::pwm_out(Brain.ThreeWirePort.F);
// vex::pwm_out Pwm_outg = vex::pwm_out(Brain.ThreeWirePort.G);
// vex::pwm_out Pwm_outh = vex::pwm_out(Brain.ThreeWirePort.H);