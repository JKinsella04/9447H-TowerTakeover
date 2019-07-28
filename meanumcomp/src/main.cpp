#include "README.h"
#include "vex.h"
//#include "pseudo.h"
#include <algorithm>
#include <cmath>

using namespace vex;
vex::competition Competition;

void pre_auton(void) {
  // Since we are early in the season we do not have anything to do in the
  // pre-auton phase before the match starts so we have no code here yet.
}

void autonomous(void) {
  // Since we are early in the season we do not have any autonomous programs
  // created to test since we do not have an exact robot design to base an
  // autonomous off of.
}

void usercontrol(void) {
  while (true) {
    // Get the raw sums of the X and Y joystick axes
    double front_left =
        (double)(con.Axis3.position(pct) +
                 con.Axis4.position(
                     pct)); // The raw value of the front left wheel based off
                            // the position of the Left Joystick
    double back_left =
        (double)(con.Axis3.position(pct) -
                 con.Axis4.position(
                     pct)); // The raw value of the back left wheel based off
                            // the position of the Left Joystick
    double front_right =
        (double)(con.Axis3.position(pct) -
                 con.Axis4.position(
                     pct)); // The raw value of the front right wheel based off
                            // the position of the Left Joystick
    double back_right =
        (double)(con.Axis3.position(pct) +
                 con.Axis4.position(
                     pct)); // The raw value of the back right wheel based off
                            // the position of the Left Joystick

    // Find the largest possible sum of X and Y axes of the Left Joystick on the
    // V5 Controller. We do this so later we can scale down the speed of the
    // motors.
    double max_raw_sum =
        (double)(abs(con.Axis3.position(pct)) + abs(con.Axis4.position(pct)));

    // Find the largest joystick value. We do this because we need to scale down
    // the sums of the wheels to the maximum of the joysticks.
    double max_XYstick_value = (double)(std::max(abs(con.Axis3.position(pct)),
                                                 abs(con.Axis4.position(pct))));

    // The largest sum will be scaled down to the largest joystick value, and
    // the others will be scaled by the same amount to preserve directionality
    if (max_raw_sum != 0) {
      front_left = front_left / max_raw_sum * max_XYstick_value;
      back_left = back_left / max_raw_sum * max_XYstick_value;
      front_right = front_right / max_raw_sum * max_XYstick_value;
      back_right = back_right / max_raw_sum * max_XYstick_value;
    }

    // Now to consider rotation
    // Naively add the rotational axis
    front_left = front_left + con.Axis1.position(pct);
    back_left = back_left + con.Axis1.position(pct);
    front_right = front_right - con.Axis1.position(pct);
    back_right = back_right - con.Axis1.position(pct);

    // What is the largest sum, or is 100 larger? This checks each wheel
    // position and sees if the wheel's value is greater than 100
    max_raw_sum =
        std::max(std::abs(front_left),
                 std::max(std::abs(back_left),
                          std::max(std::abs(front_right),
                                   std::max(std::abs(back_right), 100.0))));

    // Scale everything down by the factor that makes the largest only 100, if
    // it was over
    front_left = front_left / max_raw_sum * 100.0;
    back_left = back_left / max_raw_sum * 100.0;
    front_right = front_right / max_raw_sum * 100.0;
    back_right = back_right / max_raw_sum * 100.0;

    // Write the manipulated values out to the motors
    // This is the code that actually makes the robot move and all the rest
    // before was just to make the drive base be able to go foward, backward,
    // strafe left and right, and turn right and left.
    frontleft.spin(fwd, front_left, velocityUnits::pct);
    backleft.spin(fwd, back_left, velocityUnits::pct);
    frontright.spin(fwd, front_right, velocityUnits::pct);
    backright.spin(fwd, back_right, velocityUnits::pct);
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
    //obtaincube();
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(100); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}