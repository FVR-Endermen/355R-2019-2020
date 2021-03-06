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
// LeftFrontMotor       motor         5               
// LeftBackMotor        motor         6               
// RightFrontMotor      motor         9               
// RightBackMotor       motor         20              
// FeederLeftMotor      motor         3               
// FeederRightMotor     motor         10              
// RackAndPinionMotor   motor         8               
// LiftMotor            motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

// ideally this would be in another .h file

void MoveForward(float, int);
void FeederAction(float, bool);
void RotateClockWise(float, int);
void LiftStacker(float, bool);
void Strafe(float, int);

//Defining some constants we measure

float const WheelRadiusInInches = 2.0;
float const Pi = 3.14159267;

// something to measure -- its the diagonal distance between wheels 
// through the CENTER of the robot.  DIAMETER of the robot
float const DiagWheelBaseInInches = 22.0;

bool StopFeeder = true;


using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


    FeederAction(60,true);
   
    // These were a test -- don't use!
    //Strafe(20.0,50);
    //Strafe(-20.0,50);

   // MoveForward(32.0, 125);
     MoveForward(17.0, 70);
     RotateClockWise(94.0,110);
     FeederAction(42,true);
     MoveForward(11.5, 80);
     RotateClockWise(185.0,110);
    FeederAction(0,true);
     MoveForward(15.0, 80);
    FeederAction(32,true);
         MoveForward(18.0, 60);
  
  
  //   RotateClockWise(-45.0,100);

    FeederAction(30, true);    

    Strafe(-20.0,70);
    Strafe(2.0,60);

FeederAction(0,true);

    MoveForward(12,50);
    
    //MoveForward(-0.5,50);

   LiftStacker(3.56,true);
   

    MoveForward(-20.0, 70);

    //vex::task::sleep(500);
    //FeederAction(46, true);
    // stop feeder before turning

    /*
    FeederAction(20, true);

   // RotateClockWise(210.0);  // the old number
    RotateClockWise(-135.0,100);


    MoveForward(30.0,125);

    RotateClockWise(-10.0,100);

    MoveForward(15.0,125);



  //  RotateClockWise(-45.0);

    //vex::task::sleep(1000);
    //FeederAction(50,true);
  //  MoveForward(15,125);

    MoveForward(5.3,50);
 
    FeederAction(0,true);


    LiftStacker(2.4,true);

    FeederAction(40, false);    
    //FeederAction(0, false); 
    LiftStacker(0.75, false );
    MoveForward(-20.0, 30);
*/

// The old place steps
//    LiftStacker(2.0,true);

//    FeederAction(40, false);    
//    LiftStacker(1.0, false );
  
//  With new feeder 
/*
    LiftStacker(1.0, true);
    m-MoveForward(-1.0,30);
     LiftStacker(0.5, true);
    MoveForward(-1.0,30);
     LiftStacker(0.5, true);
    MoveForward(-1.0,30);
     LiftStacker(0.1, true);
    MoveForward(-1.0,30);
     LiftStacker(0.1, true);
    MoveForward(-1.0,30);
  //  LiftStacker(0.5, true);
  //  LiftStacker(0.5, true);
*/

  
  



    /*
    LiftStacker(0.8,true);
    //FeederAction(10,false);    MoveForward(-10.0, 50);

    LiftStacker(1.15, true);
    //FeederAction(20,false);
    //vex::task::sleep(500);
    FeederAction(40,false);
    LiftStacker(2.2,false);
    //LiftStacker(-2.2, true);
    FeederAction(0,true);

*/
    
}


void LiftStacker(float nRotations, bool direction){
  //float liftAngle = nRotations / 360; 
  if (direction == 1) {
    LiftMotor.setVelocity(20.0,percent);
    LiftMotor.spin(forward);
    RackAndPinionMotor.spinToPosition(nRotations,turns,true);
    LiftMotor.setVelocity(0.0,percent);
    LiftMotor.spin(forward);
  } else{
    RackAndPinionMotor.spinToPosition(-nRotations,turns,true);
  }

  RackAndPinionMotor.setPosition(0,turns);

}

void FeederAction(float FeederSpeed, bool direction){
  if (direction == 1) {
    FeederLeftMotor.setVelocity(FeederSpeed,percent);
    FeederRightMotor.setVelocity(FeederSpeed,percent);
    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);
  } else{
   FeederLeftMotor.setVelocity(-FeederSpeed,percent);
    FeederRightMotor.setVelocity(-FeederSpeed,percent);
    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);
  }
}

// Function to move forward, howfar is in INCHES

void MoveForward(float howfar, int howfast) {

// need to convert inches to number of rotations and then to degrees
// number of rotations is how many circumferences the argument howfar is

    float nRotations = howfar / Pi / WheelRadiusInInches / 2.0;

// motion speed
    int motorvelocity = howfast;

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

    LeftFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm, false); // false keeps spinning
    RightFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,false); // also false
    LeftBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,false); // also false
    RightBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,true); // now true


// attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns);


return;

}



// Function to strafe (comes from MoveForward), howfar is in INCHES
// Positive is to the right, negative is to the left




void Strafe(float howfar, int howfast) {

// need to convert inches to number of rotations and then to degrees
// number of rotations is how many circumferences the argument howfar is

    float nRotations = howfar / Pi / WheelRadiusInInches / 2.0;

// motion speed
    int motorvelocity = howfast;

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

// Now modified this to strafe -- which is moving left to right.  To do that 
// make the front and back wheels move in opposite directions.Brain

// Move right =
//  RightFrontMotor reverse
//  RightBackMotor  forward
//  LeftFrontMotor  forward
//  LeftBackMotor   reverse

//  Changing sign of nRotations to do this

    LeftFrontMotor.spinToPosition(nRotations,turns,motorvelocity,rpm, false); // false keeps spinning
    RightFrontMotor.spinToPosition(-nRotations,turns,motorvelocity,rpm,false); // also false
    LeftBackMotor.spinToPosition(-nRotations,turns,motorvelocity,rpm,false); // also false
    RightBackMotor.spinToPosition(nRotations,turns,motorvelocity,rpm,true); // now true


// attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns);


return;

}





// Function to rotate the robot clockwise, howfar is in DEGREES

void RotateClockWise(float howfar, int howfast) {

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

    LeftFrontMotor.spinToPosition(WheelRotations,turns,howfast, rpm, false); 
    LeftBackMotor.spinToPosition(WheelRotations,turns,howfast,rpm,false);  

    RightFrontMotor.spinToPosition(-WheelRotations,turns,howfast,rpm,false);  
    RightBackMotor.spinToPosition(-WheelRotations,turns,howfast,rpm,true);  


    // attempt to re-set motor encoder.Brain
LeftFrontMotor.setPosition(0, turns); 
RightFrontMotor.setPosition(0, turns);
LeftBackMotor.setPosition(0, turns);
RightBackMotor.setPosition(0, turns); 

}