
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
void startup() {
  traymotor.startRotateFor(100,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  //vex::task::sleep(20);
  traymotor.startRotateFor(-500,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  traymotor.resetRotation();
  }