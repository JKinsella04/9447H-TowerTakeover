using namespace vex;

extern brain Brain;

// VEXcode evices
extern controller con;
extern smartdrive Drivetrain;
extern motor trayMotor;
extern motor leftIntake;
extern motor rightIntake;
extern motor armMotor;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor rightMotorA;
extern motor rightMotorB;
extern inertial TurnGyroSmart;
extern line lineSensor1;
extern line lineSensor2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );