// This is the header file for the function that spins our intake
// Here if the Top and Bottom bumper on the left of the Controller are pressed it will spin the intake either forward or reverse
using namespace vex;
void intake() {
    if(Controller.ButtonL1.pressing() == 1) { // Here if the Top Bumper is pressed the intake will spin forward bringing the object inward 
       Intake1.spin(directionType::fwd,600,velocityUnits::rpm);
       Intake2.spin(directionType::fwd,600,velocityUnits::rpm);
    }
    
    else if(Controller.ButtonL2.pressing() == 1) { // Here if the Bottom Bumper is pressed the intake will spin reverse spitting the object out.
        Intake1.spin(directionType::rev,600,velocityUnits::rpm);
        Intake2.spin(directionType::rev,600,velocityUnits::rpm);
    }

    else { // Here if no bumper is pressed it will make the intake not spin at all.
    Intake1.stop();
    Intake2.stop();
    }
}