// VEX V5 C++ Project
#include "vex.h"
#include <algorithm>
#include <cmath>
#include <rollerintake.h>
#include <lift.h>

using namespace vex;




int main(void) {
    while(true) {
        //Get the raw sums of the X and Y joystick axes
        double front_left  = (double)(con.Axis3.position(pct) + con.Axis4.position(pct));
        double back_left   = (double)(con.Axis3.position(pct) - con.Axis4.position(pct));
        double front_right = (double)(con.Axis3.position(pct) - con.Axis4.position(pct));
        double back_right  = (double)(con.Axis3.position(pct) + con.Axis4.position(pct));
        
        //Find the largest possible sum of X and Y
        double max_raw_sum = (double)(abs(con.Axis3.position(pct)) + abs(con.Axis4.position(pct)));
        
        //Find the largest joystick value
        double max_XYstick_value = (double)(std::max(abs(con.Axis3.position(pct)),abs(con.Axis4.position(pct))));
        
        //The largest sum will be scaled down to the largest joystick value, and the others will be
        //scaled by the same amount to preserve directionality
        if (max_raw_sum != 0) {
            front_left  = front_left / max_raw_sum * max_XYstick_value;
            back_left   = back_left / max_raw_sum * max_XYstick_value;
            front_right = front_right / max_raw_sum * max_XYstick_value;
            back_right  = back_right / max_raw_sum * max_XYstick_value;
        }
        
        //Now to consider rotation
        //Naively add the rotational axis
        front_left  = front_left  + con.Axis1.position(pct);
        back_left   = back_left   + con.Axis1.position(pct);
        front_right = front_right - con.Axis1.position(pct);
        back_right  = back_right  - con.Axis1.position(pct);
        
        //What is the largest sum, or is 100 larger?
        max_raw_sum = std::max(std::abs(front_left),std::max(std::abs(back_left),std::max(std::abs(front_right),std::max(std::abs(back_right),100.0))));
        
        //Scale everything down by the factor that makes the largest only 100, if it was over
        front_left  = front_left  / max_raw_sum * 100.0;
        back_left   = back_left   / max_raw_sum * 100.0;
        front_right = front_right / max_raw_sum * 100.0;
        back_right  = back_right  / max_raw_sum * 100.0;
        
        //Write the manipulated values out to the motors
         frontleft.spin(fwd,front_left, velocityUnits::pct);
         backleft.spin(fwd,back_left,  velocityUnits::pct);
         frontright.spin(fwd,front_right,velocityUnits::pct);
         backright.spin(fwd,back_right, velocityUnits::pct);
    }
}
 