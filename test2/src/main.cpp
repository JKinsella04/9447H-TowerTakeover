#include "vex.h"
using namespace vex;

float motor_max = 100;
bool arm = 0;
int   autonomousSelection = 0;

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
void shwaydrive(double ecount, double speed);

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
  if(autonomousSelection == 0) { //Red Unprotected 
    con.Screen.clearLine(3);
    con.Screen.setCursor(3, 7);
    con.Screen.print("Red Unprot");
  } if(autonomousSelection == 4) { //Red Protetected
    con.Screen.clearLine(3);
    con.Screen.setCursor(3, 8);
    con.Screen.print("Red Prot");
  } if(autonomousSelection == 3) { //Blue Unprotected
    con.Screen.clearLine(3);
    con.Screen.setCursor(3, 6);
    con.Screen.print("Blue Unprot");
  } if(autonomousSelection == 7) { //Blue Protected
    con.Screen.clearLine(3);
    con.Screen.setCursor(3, 8);
    con.Screen.print("Blue Prot");
  } if(autonomousSelection == -1) { //None Selected
    con.Screen.clearLine(3);
    con.Screen.setCursor(3, 7);
    con.Screen.print("No Auton");
  }
}


void autonomous(void) {
if(autonomousSelection == 0) { //Red Unprotected   
  driveForward(15, 100);
  driveBackward(8, 50);
  intake(-1100, 100);
  armMotor.startRotateTo(0,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  driveForward(31, 50);
  driveBackward(10, 75);
  leftIntake.stop();
  rightIntake.stop();
  turnRight(360, 55);
  intake(-200, 100);
  trayMotor.startRotateTo(1200,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
  driveForward(17, 75);
  vex::task::sleep(850);
  trayMotor.startRotateTo(0,vex::rotationUnits::deg,80,velocityUnits::rpm);
  driveBackward(10, 75);
}
else if(autonomousSelection == 2) { //Red Protetected
    driveForward(12, 75);
    driveBackward(6, 75);
    intake(-1100, 100);
    armMotor.startRotateTo(10,vex::rotationUnits::deg,80,velocityUnits::rpm);
    rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
    leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
    driveForward(25, 75);
    turnLeft(260, 75);
    driveForward(15, 75);
    turnLeft(105, 75);
    leftIntake.stop();
    rightIntake.stop();
    trayMotor.startRotateTo(1000,vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
    intake(-200, 100);
    driveForward(17, 75);
    vex::task::sleep(750);
    trayMotor.startRotateTo(-60,vex::rotationUnits::deg,80,velocityUnits::rpm);
    driveBackward(15, 100);
}
else if(autonomousSelection == 1) { //Blue Unprotected
  driveForward(15, 100);
  driveBackward(8, 100);
  intake(-1100, 100);
  // armMotor.startRotateTo(0,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  driveForward(31, 50);
  driveBackward(10, 75);
  leftIntake.stop();
  rightIntake.stop();
  turnLeft(380, 75);
  intake(-200, 100);
  trayMotor.startRotateTo(1200,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
  driveForward(17, 75);
  vex::task::sleep(750);
  trayMotor.startRotateTo(0,vex::rotationUnits::deg,80,velocityUnits::rpm);
  driveBackward(10, 100);
}
else if(autonomousSelection == 3) { //Blue Protected
  driveForward(12, 75);
  driveBackward(6, 75);
  intake(-1100, 100);
  armMotor.startRotateTo(-10,vex::rotationUnits::deg,80,velocityUnits::rpm);
  rightIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  leftIntake.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
  driveForward(25, 75);
  turnRight(260, 75);
  driveForward(15, 75);
  turnRight(105, 75);
  leftIntake.stop();
  rightIntake.stop();
  trayMotor.startRotateTo(1200,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
  intake(-200, 100);
  driveForward(18, 75);
  vex::task::sleep(750);
  trayMotor.startRotateTo(-60,vex::rotationUnits::deg,80,velocityUnits::rpm);
  driveBackward(15, 100);
  }
}


void usercontrol(void) {
  // User control code here, inside the loop
  Brain.resetTimer();
  con.Screen.clearScreen();
  while (1) {
     
    float max = 127.0;
    float left_percent = con.Axis3.value()/max;
    float right_percent = con.Axis2.value()/max;
       
    float left_new_percent = left_percent * left_percent * left_percent;
    float right_new_percent = right_percent * right_percent * right_percent;
       
    // float motor_max = 100;
    int left_power = left_new_percent * motor_max;
    int right_power = right_new_percent * motor_max; //*7/9;
       
    leftMotorA.spin(fwd,left_power,vex::velocityUnits::pct);
    leftMotorB.spin(fwd,left_power,vex::velocityUnits::pct);
    rightMotorA.spin(fwd,right_power,vex::velocityUnits::pct);
    rightMotorB.spin(fwd,right_power,vex::velocityUnits::pct);
  
    pStack();
    // smartTrayTilt();
    intakeSpin();
    armMove(); 
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
    Brain.Screen.printAt( 177,  125, "  9447H  " );
    Brain.Screen.printAt(172, 90, "UnProtected");
    Brain.Screen.printAt(178, 160, "Protected");
    wait(25, msec);
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
    con.Screen.clearLine(2);
    con.Screen.setCursor(2, 10);
    con.Screen.print("Arm");
  }
  else if (con.ButtonX.pressing() == 1) {
    arm = 0;
    con.Screen.clearLine(2);
    con.Screen.setCursor(2, 10);
    con.Screen.print("Tray");
  }
  return 0;
  }
}

task CTimer() {
  while(1){
con.Screen.clearLine(1);
con.Screen.setCursor(1, 7);
con.Screen.print("Time Left %.4f", 105 - Brain.timer(timeUnits::sec));
if(Brain.timer(timeUnits::sec) >= 100){
  leftIntake.setBrake(coast);
  rightIntake.setBrake(coast);
  leftMotorA.setBrake(coast);
  leftMotorB.setBrake(coast);
  rightMotorA.setBrake(coast);
  rightMotorB.setBrake(coast);
  armMotor.setBrake(coast);
  trayMotor.setBrake(coast);
  con.Screen.setCursor(2, 7);
  con.Screen.print("5 Sec left!");
}
vex::task::sleep(25);
  return 0;
  }
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
  double kP =0.15;
  if( arm == 0){
  if (con.ButtonL1.pressing() ==1 && con.ButtonL2.pressing() ==0) {
    double error = 1100 - trayMotor.position(rotationUnits::deg);
    double Tpower = error*kP;
    // trayMotor.startRotateTo(1050,vex::rotationUnits::deg, Tpower,vex::velocityUnits::rpm);
    trayMotor.setVelocity(Tpower, velocityUnits::rpm);
    trayMotor.spin(directionType::fwd);

  } else if(con.ButtonL2.pressing() ==1) {
    trayMotor.startRotateTo(-60,vex::rotationUnits::deg, 80,vex::velocityUnits::rpm);
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
    armMotor.startRotateTo(400, vex::rotationUnits::deg, 100,vex::velocityUnits::rpm);
    vex::task::sleep(100);
    intake(-250,100);
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

void shwaydrive(double ecount, double speed) {
  leftMotorA.resetRotation();
  rightMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorB.resetRotation();
  
  leftMotorA.startRotateTo(ecount+30,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorA.startRotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  leftMotorB.startRotateTo(ecount+30,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
  rightMotorB.rotateTo(ecount,vex::rotationUnits::deg, speed,vex::velocityUnits::rpm);
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