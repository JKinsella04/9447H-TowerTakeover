using namespace vex;
void intake() {
    if(Controller.ButtonL1.pressing() == 1) {
       Intake1.spin(directionType::fwd,600,velocityUnits::rpm);
       Intake2.spin(directionType::fwd,600,velocityUnits::rpm);
    }
    
    else if(Controller.ButtonL2.pressing() == 1) {
        Intake1.spin(directionType::rev,600,velocityUnits::rpm);
        Intake2.spin(directionType::rev,600,velocityUnits::rpm);
    }

    else {
    Intake1.stop();
    Intake2.stop();
    }
}