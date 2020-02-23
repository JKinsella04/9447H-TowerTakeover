#include "vex.h"
using namespace vex;

float motor_max = 100;
bool arm = 0;
int   autonomousSelection = -1;

void intakeSpin();
void armMove();
void smartTrayTilt();
void brakes();
void resetBrakes();
void pStack();

void driveForward(double ecount, double speed);
void driveBackward(double ecount, double speed);
void intake(double ecount, double speed);
void turnLeft(double count, double speed);
void turnRight(double count, double speed);
void ddtrain(double ecount, double speed);

void displayButtonControls( int index, bool pressed );
void userTouchCallbackPressed();
void userTouchCallbackReleased();

task ControlType();
task Cubes();
task CTimer();

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  TurnGyroSmart.calibrate();
  armMotor.setBrake(hold);
  trayMotor.setBrake(hold);
  leftIntake.setBrake(hold);
  rightIntake.setBrake(hold);
}


void autonomous(void) {
if(autonomousSelection == 0) { //Red Unprotected 
  
}
if(autonomousSelection == 4) { //Red Protetected
  
}
if(autonomousSelection == 3) { //Blue Unprotected
  
}
if(autonomousSelection == 7) { //Blue Protected
  
}

  ////////////////// 9 Point Begin ///////////////////////
  // rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // vex::task::sleep(2000);
  //   //Toggles the intakes on to pick up cubes
  // driveForward(40, 50);
  //   //Goes forward picking up the preload and the 4 cubes in a row
  // turnLeft(45, 50);
  //   //We turn left after picking up the cubes so we are at the right angle to backup behind the new row of cubes for us to pick up.
  // leftIntake.stop();
  // rightIntake.stop();
  //   //we stop spinning the intakes before we begin backing up.
  // driveBackward(30, 100);
  //   //We go backwards untill the robot is behind the next row of cubes for us to pickup
  // turnRight(45, 50);
    //The robot turns right to face the cubes that we want to pick up
  ////////////////// 5 Point Begin ///////////////////////
  //  /*
  // rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::rpm);
  // // vex::task::sleep(2000);
  //   //Toggles the intakes on to pick up this row of cubes
  // driveForward(45, 50); 
  // vex::task::sleep(100);
  //   //Goes forward so the intakes actually intake cubes
  // driveBackward(30, 100);
  //   //Goes back so we can turn right to face the goal zone at a perfect 45 degree angle
  // turnRight(345, 75); //Red 450 Blue 360
  //   //Turns right to look towards the goal zone at a 45 degree angle
  // leftIntake.stop();
  // rightIntake.stop();
  //   //We stop the intakes before going into the goal goal zones
  // vex::task::sleep(100);
  // intake(-400, 100);
  // trayMotor.startRotateTo(1100,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  // driveForward(11, 100);
  // vex::task::sleep(1500);
  // */
  
  // vex::task::sleep(100);
  // ddtrain(100, 100);
  // vex::task::sleep(500);
  // driveBackward(10, 50);
  // driveForward(2, 75);
  
  /**/
    //We go forward into the goal zone then stack the 9 cubes and back up after bringing the tray perpindicular to the ground.
  }


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    // float motor_max = 100;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max;
       
    leftMotorA.spin(fwd,left_power,vex::velocityUnits::pct);
    leftMotorB.spin(fwd,left_power,vex::velocityUnits::pct);
    rightMotorA.spin(fwd,right_power,vex::velocityUnits::pct);
    rightMotorB.spin(fwd,right_power,vex::velocityUnits::pct);
  
    pStack();
    // smartTrayTilt();
    intakeSpin();
    armMove();
  if( autonomousSelection == 0 ){
    leftIntake.spin(directionType::fwd);
  }
    ControlType();
    Cubes();
    // CTimer();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

    Brain.Screen.pressed( userTouchCallbackPressed );
    Brain.Screen.released( userTouchCallbackReleased );
    
    // background
    Brain.Screen.setFillColor( vex::color(0x400000) );
    Brain.Screen.setPenColor( vex::color(0x400000) );
    Brain.Screen.drawRectangle( 0, 0, 120, 480 );
    Brain.Screen.setFillColor( vex::color(0x000040) );
    Brain.Screen.setPenColor( vex::color(0x000040) );
    Brain.Screen.drawRectangle( 350, 0, 120, 480 );

    // initial display
    displayButtonControls( 0, false );
  // Prevent main from exiting with an infinite loop.
  while (true) {
    Brain.Screen.printAt( 150,  125, "  9447H  " );
    Brain.Screen.printAt(175, 40, "UnProtected");
    Brain.Screen.printAt(176, 160, "Protected");
    wait(100, msec);
  }
}


task Cubes() {
  while(1) {
  if (lineSensor1.value(analogUnits::pct) == 55){
  // if (arm == 0){
      motor_max = 20; 
  }
  else{
    motor_max = 100;
  }
  return 0;
  }
}

task ControlType() {
  while(1){
  if(con.ButtonA.pressing() == 1){
    arm = 1;
    con.Screen.clearScreen();
    con.Screen.print("Arm");
  }
  else if (con.ButtonX.pressing() == 1) {
    arm = 0;
    con.Screen.clearScreen();
    con.Screen.print("Tray");
  }
  return 0;
  }
}

task CTimer() {
  Brain.resetTimer();
  con.Screen.setCursor(1, 1);
  while(1) {
    double time = Brain.timer(timeUnits::sec);
    con.Screen.print(time);
    if (time >= 100000){
      leftIntake.setBrake(coast);
      rightIntake.setBrake(coast);
      leftMotorA.setBrake(coast);
      leftMotorB.setBrake(coast);
      rightMotorA.setBrake(coast);
      rightMotorB.setBrake(coast);
      armMotor.setBrake(coast);
      trayMotor.setBrake(coast);
    }
  }
  return 0;
}

void brakes(){
  leftIntake.setBrake(coast);
  rightIntake.setBrake(coast);
  leftMotorA.setBrake(hold);
  leftMotorB.setBrake(hold);
  rightMotorA.setBrake(hold);
  rightMotorB.setBrake(hold);
}
void resetBrakes(){
  leftIntake.setBrake(hold);
  rightIntake.setBrake(hold);
  leftMotorA.setBrake(coast);
  leftMotorB.setBrake(coast);
  rightMotorA.setBrake(coast);
  rightMotorB.setBrake(coast);
}

void pStack() {
  double kP =0.2;
  if( arm == 0){
  if (con.ButtonL1.pressing() ==1) {
    double error = 1100 - trayMotor.position(rotationUnits::deg);
    double Tpower = error*kP;
    // trayMotor.startRotateTo(1050,vex::rotationUnits::deg, Tpower,vex::velocityUnits::rpm);
    trayMotor.setVelocity(Tpower, velocityUnits::rpm);
    trayMotor.spin(directionType::fwd);

  } else if(con.ButtonL2.pressing() ==1) {
    trayMotor.rotateTo(0,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
  }
  else{
    trayMotor.stop();
  }
  }
  if (arm == 1) {
    if (con.ButtonUp.pressing() == 1) {
      brakes();
      trayMotor.spin(vex::directionType::fwd, 80, vex::velocityUnits::rpm);
      if(trayMotor.rotation(rotationUnits::deg) >= 500) {
        trayMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
      }
    } else if (con.ButtonRight.pressing() == 1) {
      trayMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::rpm);
    } else {
      trayMotor.stop();
      resetBrakes();
    }
  }
}

void intakeSpin(){
    if (con.ButtonR1.pressing() == 1) {
      leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (con.ButtonR2.pressing() == 1) {
      leftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    } else {
      leftIntake.stop();
      rightIntake.stop();
    }
}

void armMove(){
  if (con.ButtonL1.pressing() ==1 && con.ButtonL2.pressing()==1) {
    armMotor.startRotateTo(200, vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
    vex::task::sleep(100);
    intake(-150,100);
  }
  if(arm == 0) {
    if (con.ButtonUp.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    } else if (con.ButtonRight.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    } 
  }
  else if (arm == 1) {
    if (con.ButtonL1.pressing() == 1) {
      armMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    } else if (con.ButtonL2.pressing() == 1) {
      armMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::rpm);
    } else {
      armMotor.stop();
    } 
  }
}

void driveForward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::fwd, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void driveBackward(double ecount,double speed) {
  Drivetrain.driveFor(directionType::rev, ecount, distanceUnits::in, speed, velocityUnits::rpm);
}

void intake(double ecount,double speed) { //spins both intakes for the specified encoder count. continues to next line of code after the right intake finishes spinning.
  leftIntake.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightIntake.rotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

void turnLeft(double ecount, double speed) {
  leftMotorA.resetRotation();
  rightMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorB.resetRotation();

  leftMotorA.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorA.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  leftMotorB.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorB.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
}

void turnRight(double ecount, double speed) {
    leftMotorA.resetRotation();
  rightMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorB.resetRotation();
  
  leftMotorA.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorA.startRotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  leftMotorB.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorB.rotateTo(-ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
}

void ddtrain(double ecount, double speed){ //go forward with and go to next line of code
  leftMotorA.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  leftMotorB.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightMotorA.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
  rightMotorB.startRotateFor(ecount, vex::rotationUnits::deg, speed,vex::velocityUnits::pct);
}

// collect data for on screen button
typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color color;
    const char *label;
} button;

// Button definitions
button buttons[] = {
  {   30,  30, 60, 60,  false, 0xE00000, " RUP" },
  {  390,  30, 60, 60,  false, 0x0000E0, " BUP" },
  {   30, 150, 60, 60,  false, 0xE00000, " RP" },
  {  390, 150, 60, 60,  false, 0x0000E0, " BP" }
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;
      
      return(index);
    }
    return (-1);
}
/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();
    
    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }
    
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();
    
    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      initButtons();

      // now set this one as true
      buttons[index].state = true;
      
      // save as auton selection
      autonomousSelection = index;
      
      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {
      
      if( buttons[i].state )
        c = buttons[i].color;
      else
        c = vex::color::black;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        c = c + 0x404040;
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );
  
      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

      // draw label
      if(  buttons[i].label != NULL )
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
    }
}