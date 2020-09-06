/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
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
// FeederLeftMotor      motor         16              
// FeederRightMotor     motor         5               
// RackAndPinionMotor   motor         8               
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
float const DiagWheelBaseInInches = 21.75;

bool StopFeeder = true;

// Things for driver control

// Deadband stops the motors when Axis values are close to zero.
int deadband = 5;

// How fast the feeder motors will spin
int FeederSpeed = 50;
int LifterSpeed = 30;


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

// commenting out to test
//    LiftStacker(0.35,true);

    FeederAction(42,true);
   
    // These were a test -- don't use!
    //Strafe(20.0,50);
    //Strafe(-20.0,50);

    MoveForward(19.0, 175);
    MoveForward(30.0, 35);

    //vex::task::sleep(500);
    //FeederAction(46, true);
    // stop feeder before turning
    FeederAction(20, true);

   // RotateClockWise(210.0);  // the old number
    RotateClockWise(180.0,100);


    MoveForward(28.0,125);

    RotateClockWise(-45.0,100);

    //vex::task::sleep(1000);
    //FeederAction(50,true);
    MoveForward(15,125);

    FeederAction(0, false);    

    MoveForward(5.3,50);

    LiftStacker(2.0,true);

    FeederAction(40, false);    
    //FeederAction(0, false); 
    LiftStacker(1.0, false );

// Original RedRight Auton ends here

    MoveForward(-12.0, 30);


    FeederAction(0, false);    


    RotateClockWise(-135.0,100);
    LiftStacker(1.0, false );

// Backed up, rotated to point to blue, and adjusted stacker -- ready to go!

    MoveForward(40.0, 175);
    FeederAction(40, true); 

    //Near Center Line   

    RotateClockWise(-10.0,100);

    MoveForward(15.0, 30);

    // Aiming for next line of blocks

    RotateClockWise(5.0,100);

    MoveForward(40.0, 30);

    // Aim for blue goal

    RotateClockWise(50.0,100);

    //vex::task::sleep(1000);
    //FeederAction(50,true);

    // Placing stack code from above 
    MoveForward(15,125);

    FeederAction(0, false);    

    MoveForward(5.3,50);

    LiftStacker(2.0,true);

    FeederAction(40, false);    
    //FeederAction(0, false); 
    LiftStacker(1.0, false );
    MoveForward(-12.0, 30);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();
    // What is the state of button L1
    bool L1Down = Controller1.ButtonL1.pressing();
    // What is the state of button R1
    bool R1Down = Controller1.ButtonR1.pressing();

    bool UpArrowPushed = Controller1.ButtonUp.pressing();
    bool DownArrowPushed = Controller1.ButtonDown.pressing();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LeftFrontMotor.setVelocity(0, percent);
      LeftBackMotor.setVelocity(0, percent);

    } else {
      // Set the speed to leftMotorSpeed
      LeftFrontMotor.setVelocity(leftMotorSpeed, percent);
      LeftBackMotor.setVelocity(leftMotorSpeed, percent);

    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      RightFrontMotor.setVelocity(0, percent);
      RightBackMotor.setVelocity(0, percent);

    } else {
      // Set the speed to rightMotorSpeed
      RightFrontMotor.setVelocity(rightMotorSpeed, percent);
      RightBackMotor.setVelocity(rightMotorSpeed, percent);

    }

    // Spin both motors in the forward direction.
    LeftFrontMotor.spin(forward);
    LeftBackMotor.spin(forward);

    RightFrontMotor.spin(forward);
    RightBackMotor.spin(forward);


//  stop motors if nobody is pressed or if BOTH are pressed
    if ( (!L1Down && !R1Down) || (L1Down && R1Down) ) {
       FeederLeftMotor.setVelocity(0,percent);
       FeederRightMotor.setVelocity(0,percent);
// L1 pressed feeds in
    } else if (L1Down && !R1Down)   {
       FeederLeftMotor.setVelocity(FeederSpeed,percent);
       FeederRightMotor.setVelocity(FeederSpeed,percent);
// R1 pressed pushes out       
    } else if (R1Down && !L1Down)   {
       FeederLeftMotor.setVelocity(-FeederSpeed,percent);
       FeederRightMotor.setVelocity(-FeederSpeed,percent);
    } else {  // should never get here
      FeederLeftMotor.setVelocity(0,percent);
      FeederRightMotor.setVelocity(0,percent);
    }
    
  // actually spin the Feeder motors

    FeederLeftMotor.spin(forward);
    FeederRightMotor.spin(forward);


//  up and down arrows
 
   if ( (!UpArrowPushed && !DownArrowPushed) || (UpArrowPushed && DownArrowPushed) ) {
       RackAndPinionMotor.setVelocity(0,percent);
      
// Up Arrow tilts it up
    } else if (UpArrowPushed && !DownArrowPushed)   {
         RackAndPinionMotor.setVelocity(LifterSpeed,percent);
       
// Down arrow tilts it down       
    } else if (DownArrowPushed && !UpArrowPushed)   {
      RackAndPinionMotor.setVelocity(-LifterSpeed,percent);
       
    } else {  // should never get here
      RackAndPinionMotor.setVelocity(0,percent);
      
    }
RackAndPinionMotor.spin(forward);






    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}




void LiftStacker(float nRotations, bool direction){
  //float liftAngle = nRotations / 360; 
  if (direction == 1) {
    RackAndPinionMotor.spinToPosition(nRotations,turns,true);
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
