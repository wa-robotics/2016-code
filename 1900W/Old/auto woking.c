#pragma config(Sensor, in1,    knob,           sensorPotentiometer)
#pragma config(Motor,  port1,           LiftRightB,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           LiftRightM,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LiftRightT,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           DBL,           tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           DFL,           tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           DFR,           tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           DBR,           tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LiftLeftT,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LiftLeftM,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LiftLeftB,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)


//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
//#include "LCD Wizard 2.c"
//#include "LCD Selection Wizard.c"

void pre_auton() {
	//startTask(lcdSelection);
}
/* void stopMotors()
{
motor[LiftRight] = 0;
motor[LiftRight] = 0;
motor[LiftRight] = 0;
motor[LiftLeft] = 0;
motor[LiftLeft] = 0;
motor[LiftLeft] = 0;
}

void LiftUp(float rotations)
{
nMotorEncoder[LiftRight] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
}
stopMotors ();
}
void LiftDown (float rotatitons)
{
nMotorEncoder[LiftLeft] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = -127;
motor[LiftRight] = -127;
motor[LiftRight] = -127;
motor[LiftLeft] = -127;
motor[LiftLeft] = -127;
motor[LiftLeft] = -127;
}
stopMotors ();
}
void LiftUp (float rotations)
{
nMotorEncoder[LiftRight] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
}
}

task main()
{
LiftUp(1)
LiftUp(-1)
LiftUp(1)
nMotorEncoder[LiftRight] = 0;
moveFoward(.

*/

void setLiftMotors(int power)
{
	motor[LiftLeftB] = power;
	motor[LiftLeftM] = power;
	motor[LiftLeftT] = power;
	motor[LiftRightB] = power;
	motor[LiftRightM] = power;
	motor[LiftRightT] = power;
}

void setLeftDtMotors(int power) {
	//set left drivetrain motors to power
	motor[DBL] = power;
	motor[DFL] = power;
}

void setRightDtMotors(int power) {
	//set right drivetrain motors to power
	motor[DBR] = power;
	motor[DFR] = power;
}

void moveLift(int power) {
	//while time1[T1] is less than time
	//set motors to power
	motor[LiftLeftT] = power;
	motor[LiftLeftB] = power;
	motor[LiftLeftM] = power;
	motor[LiftRightB] = power;
	motor[LiftRightM] = power;
	motor[LiftRightT] = power;
}
void drive(int powerL, int powerR) {
	//while time1[T1] is less than time
	//set drivetrain motors to ptime
	motor[DBL] = powerL;
	motor[DFL] = powerL;
	motor[DBR] = powerR;
	motor[DFR] = powerR;
}
void turnRight(int power) {
	//while time1[T1] is less than time
	//set drivetrain motors to ptime
	motor[DBL] = -power;
	motor[DFL] = -power;
	motor[DBR] = power;
	motor[DFR] = power;
}

task autonomousLeft()
{
	moveLift(-127);
	wait10Msec(30);
	moveLift(40);
	wait10Msec(150);
	moveLift(0);
	drive(125,118);
	wait10Msec(130);
	drive(-125,-125);
	wait10Msec(30);
	drive(0,0);
	turnRight(-125);
	wait10Msec(95);
	turnRight(0);
	drive(-125,-125);
	wait10Msec(75);
	drive(0,0);
	moveLift(127);
	wait10Msec(55);
	moveLift(0);
}

task autonomousRight ()
{
	moveLift(-127);
	wait10Msec(30);
	moveLift(40);
	wait10Msec(150);
	moveLift(0);
	drive(125,118);
	wait10Msec(130);
	drive(-125,-125);
	wait10Msec(30);
	drive(0,0);
	turnRight(125);
	wait10Msec(95);
	turnRight(0);
	drive(-125,-125);
	wait10Msec(75);
	drive(0,0);
	moveLift(127);
	wait10Msec(55);
	moveLift(0);
}

task skillsauton ()
{
	moveLift(0);
	drive(-127,-127);
	wait10Msec(40);
	drive(0,0);
	moveLift(-127);
	wait10Msec(60);
	moveLift(0);
	drive(0,0);
	wait10Msec(200);
	moveLift(60);
	wait10Msec(70);
	moveLift(0);
	drive(-125,-125);
	wait10Msec(70);
	drive(0,0);
	moveLift(127);
	wait10Msec(110);
	moveLift(0);
	wait10Msec(40);
	moveLift(-127);
	wait10Msec(70);
	moveLift(0);
	drive(125,125);
	wait10Msec(70);
	moveLift(0);
	drive(0,0);
	wait10Msec(200);
	moveLift(60);
	wait10Msec(70);
	moveLift(0);
	drive(-125,-125);
	wait10Msec(70);
	drive(0,0);
	moveLift(127);
	wait10Msec(110);
	moveLift(0);
	wait10Msec(40);
	moveLift(-127);
	wait10Msec(70);
	moveLift(0);
	drive(125,125);
	wait10Msec(70);
	moveLift(0);
	drive(0,0);
	wait10Msec(200);
	moveLift(60);
	wait10Msec(70);
	moveLift(0);
	drive(-125,-125);
	wait10Msec(70);
	drive(0,0);
	moveLift(127);
	wait10Msec(110);
	moveLift(0);
	wait10Msec(40);
	moveLift(-127);
	wait10Msec(70);
	moveLift(0);
	drive(125,125);
	wait10Msec(70);
	moveLift(0);
	drive(0,0);
	wait10Msec(200);
	moveLift(60);
	wait10Msec(70);
	moveLift(0);
	drive(-125,-125);
	wait10Msec(70);
	drive(0,0);
	moveLift(127);
	wait10Msec(110);
	moveLift(0);
	wait10Msec(40);
	moveLift(-127);
	wait10Msec(70);
	moveLift(0);
	drive(125,125);
	wait10Msec(70);
	moveLift(0);
	drive(0,0);
	wait10Msec(200);

	/*
	moveLift(60);
	wait10Msec(50);
	moveLift(0);
	drive(-125,-118);
	wait10Msec(50);
	drive(0,0);
	moveLift(127);
	wait10Msec(50);
	moveLift(-127);
	wait10Msec(60);
	drive(125,118);
	wait10Msec();
	drive(-125,-125);
	moveLift(127);
	moveLift(-127);
	drive(125,125);
	drive(0,0);
	*/
}

task autonomous() {
	if (SensorValue[knob] >=0 && SensorValue[knob] <1365)
	{
		startTask(autonomousLeft);
	}
	else if (SensorValue[knob] >=1365 && SensorValue[knob] <2730)
	{
		startTask(autonomousRight);
	}
	else
	{
		startTask(skillsauton);
	}
	while(true){}
}
/*if(autonChoices.startingTile == "left")
{
startTask(autonomousLeft);
}
if(autonChoices.startingTile == "programmingSkills")
{
//start auto skills task
}
if(autonChoices.startingTile == "right")
{
//start right auto play
}*/
//if
//}

bool auton = false;
task usercontrol()
{
//startTask(autonomous);
while(auton == false)
{
	if (vexRT[Btn5U]) {
		setLiftMotors(127);
		} else if (vexRT[Btn5D]) {
		setLiftMotors(-127);
		} else {
		setLiftMotors(9);
	}
	motor[DBL] = vexRT[Ch3];
	motor[DFL] = vexRT[Ch3];
	motor[DBR] = vexRT[Ch2];
	motor[DFR] = vexRT[Ch2];
	wait1Msec(25);
}
}


//(vexRT[Btn7D && Btn7R] == 1)
