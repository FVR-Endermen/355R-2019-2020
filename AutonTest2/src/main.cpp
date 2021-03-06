/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       dmason                                                    */
/*    Created:      Fri Oct 18 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontMotor       motor         11              
// LeftBackMotor        motor         12              
// RightFrontMotor      motor         1               
// RightBackMotor       motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

// ideally this would be in another .h file

void MoveForward(float);
void RotateClockWise(float);

//Defining some constants we measure

float const WheelRadiusInInches = 2.0;
float const Pi = 3.14159267;

// something to measure -- its the diagonal distance between wheels 
// through the CENTER of the robot.  DIAMETER of the robot

// 16 inches is what is measured but the robot clearly needed more rotations

//float const DiagWheelBaseInInches = 16.0;  

// based on how it actually turns -- calibrated to 90 degrees on the floor...
float const DiagWheelBaseInInches = 22.0;




using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

// Drive in a square

  MoveForward(24.0);  
 RotateClockWise(142.0);
  MoveForward(22.0);
  RotateClockWise(-20.0);
  RotateClockWise(20.0);
  RotateClockWise(-20.0);

//RotateClockWise(90.0);
//MoveForward(6.0);

//RotateClockWise(90.0);
// MoveForward(6.0);
//RotateClockWise(90.0);

   vex::task::sleep(100);

  
}





// Function to move forward, howfar is in INCHES

void MoveForward(float howfar) {

// need to convert inches to number of rotations and then to degrees
// number of rotations is how many circumferences the argument howfar is

    float nRotations = howfar / Pi / WheelRadiusInInches / 2.0;

    //float RotationDegrees = nRotations * 360.0;

// What this is doing:
// spinToPosition tells it to spin the wheel until it hits the requested position
// the second argument is "degrees" which is a constant that tells it the angle is 
// in -- believe it or not -- degrees
// the last argument tells it to wait or not before moving to the next one.
// The default is true.  This means if we leave the default with the four statements
// below, it will rotate the first wheel, then the next, then the next, and the last
// If we set false, it will get the motor started, then move on to the next statement. 
// So here we set the first 3 to false, but the last one to true.  This should
// move all 4 at essentially the same time, but wait until the last one is done.
// It should move the drivetrain as a whole here. 

    LeftFrontMotor.spinToPosition(nRotations,turns,false); // false keeps spinning
    RightFrontMotor.spinToPosition(nRotations,turns,false); // also false
    LeftBackMotor.spinToPosition(nRotations,turns,false); // also false
    RightBackMotor.spinToPosition(nRotations,turns,true); // now true


// attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns);

   vex::task::sleep(100);

return;

}







// Function to rotate the robot clockwise, howfar is in DEGREES

void RotateClockWise(float howfar) {

// The idea is to rotate the motors enough to have them travel along
// the circumference of the circle drawn by the wheels around the
// center of the robot. 

    float RobotCircumference = Pi * DiagWheelBaseInInches;

// now we convert howfar into a number of ROBOT rotations

    float RobotRotations = howfar / 360.0; 

// how many wheel rotations is one robot rotation

    float WheelCircumference = Pi * WheelRadiusInInches * 2.0;

// how many times the wheel goes around to travel the circumference (one robot rotation)

    float WheelRotationsInRobotRotation = RobotCircumference / WheelCircumference;

// to turn clockwise, left wheels drive forward, right wheels drive backward.Brain

    float WheelRotations = RobotRotations * WheelRotationsInRobotRotation;

// and back to degrees

//    float LeftWheelDegrees = WheelRotations * 360.0;
//    float RightWheelDegrees = 0.0-LeftWheelDegrees;

//  Now we drive!

    LeftFrontMotor.spinToPosition(WheelRotations,turns,false); 
    LeftBackMotor.spinToPosition(WheelRotations,turns,false);  

    RightFrontMotor.spinToPosition(-WheelRotations,turns,false);  
    RightBackMotor.spinToPosition(-WheelRotations,turns,true);  


    // attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns); 

}