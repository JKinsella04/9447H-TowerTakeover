#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

vex::brain Brain;
vex::motor frontright (vex::PORT19, vex::gearSetting::ratio18_1,true);
vex::motor frontleft (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor backright (vex::PORT20, vex::gearSetting::ratio18_1,true);
vex::motor backleft (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor liftmotor1 (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor liftmotor2 (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor leftintake (vex::PORT3, vex::gearSetting::ratio18_1,true);
vex::motor rightintake (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::controller con(vex::controllerType::primary);

vex::limit Limit = vex::limit(Brain.ThreeWirePort.A);
vex::pwm_out Pwm_outb = vex::pwm_out(Brain.ThreeWirePort.B);
vex::pwm_out Pwm_outc = vex::pwm_out(Brain.ThreeWirePort.C);
vex::pwm_out Pwm_outd = vex::pwm_out(Brain.ThreeWirePort.D);
vex::pwm_out Pwm_oute = vex::pwm_out(Brain.ThreeWirePort.E);
vex::pwm_out Pwm_outf = vex::pwm_out(Brain.ThreeWirePort.F);
vex::pwm_out Pwm_outg = vex::pwm_out(Brain.ThreeWirePort.G);
vex::pwm_out Pwm_outh = vex::pwm_out(Brain.ThreeWirePort.H);