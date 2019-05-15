#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

vex::brain Brain;
vex::motor FrontRight (vex::PORT19, vex::gearSetting::ratio18_1,true);
vex::motor FrontLeft (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor BackRight (vex::PORT20, vex::gearSetting::ratio18_1,true);
vex::motor BackLeft (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor Intake1 (vex::PORT6, vex::gearSetting::ratio6_1,false);
vex::motor Intake2 (vex::PORT5, vex::gearSetting::ratio6_1,true);
vex::controller Controller = vex::controller();
vex::pwm_out Pwm_outa = vex::pwm_out(Brain.ThreeWirePort.A);
vex::pwm_out Pwm_outb = vex::pwm_out(Brain.ThreeWirePort.B);
vex::pwm_out Pwm_outc = vex::pwm_out(Brain.ThreeWirePort.C);
vex::pwm_out Pwm_outd = vex::pwm_out(Brain.ThreeWirePort.D);
vex::pwm_out Pwm_oute = vex::pwm_out(Brain.ThreeWirePort.E);
vex::pwm_out Pwm_outf = vex::pwm_out(Brain.ThreeWirePort.F);
vex::pwm_out Pwm_outg = vex::pwm_out(Brain.ThreeWirePort.G);
vex::pwm_out Pwm_outh = vex::pwm_out(Brain.ThreeWirePort.H);