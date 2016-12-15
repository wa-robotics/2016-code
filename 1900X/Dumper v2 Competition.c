#pragma config(Sensor, in1,    catPot,         sensorPotentiometer)
#pragma config(Sensor, in2,    autonSelectPot, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  hangLock,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  platformLock,   sensorDigitalOut)
#pragma config(Sensor, dgtl3,  rDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  lDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  platformDown,   sensorTouch)
#pragma config(Sensor, dgtl8,  platformLockPos, sensorTouch)
#pragma config(Sensor, dgtl9,  platformRelease, sensorDigitalOut)
#pragma config(Motor,  port2,           lDriveFront,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           lDriveBack,    tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           leftDump12,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           leftDump3,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           rightDump3,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightDump12,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           rDriveBack,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rDriveFront,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
//#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void setDumpMotors(int power) {
	motor[leftDump12] = power;
	motor[leftDump3] = power;
	motor[rightDump12] = power;
	motor[rightDump3] = power;
}

void setLeftDtMotors(int power) {
	motor[lDriveFront] = power;
	motor[lDriveBack] = power;
}

void setRightDtMotors(int power) {
	motor[rDriveFront] = power;
	motor[rDriveBack] = power;
}

task platformLockController() {
	bool platformLocked = false;
	int IN = 1;
	int OUT = 0;
	while(1) {
		if(SensorValue[platformLock]) {
			platformLocked = false;
		} else {
			platformLocked = true;
		}

		if(vexRT[Btn5D]) {
			setDumpMotors(-127);
			if(platformLocked)
			{
				SensorValue[platformLock] = IN;
			}
		} else if(vexRT[Btn5U]) {
			if(platformLocked) {
				SensorValue[platformLock] = IN;
				wait1Msec(200);
			}
			setDumpMotors(127);

		} else if (!platformDown) { //compensation power when lift is up
			setDumpMotors(-45);
		} else {
			setDumpMotors(0);
		}

		if(SensorValue[platformDown] && !platformLocked && !vexRT[Btn5U]) {
			SensorValue[platformLock] = OUT;
		}
		if(vexRT[Btn8D]) {
			SensorValue[platformLock] = OUT;
		} else if(vexRT[Btn8U])
		{
			SensorValue[platformLock] = IN;
		}
	}
}

#include "Dumper v2 Auton.c"

task autonomous() {
	const int AUTON_LEFT_STARS = 1206, //this is the upper limit (<=) to select
						AUTON_LEFT_CUBE = 1952,
						AUTON_RIGHT_STARS = 2952,
						AUTON_RIGHT_CUBE = 3510,
						AUTON_SKILLS = 4095;

	int autonSelection = SensorValue[autonSelectPot];

	if (autonSelection <= AUTON_LEFT_STARS) {
		startTask(autonKnockStarsLeft);

	} else if (autonSelection <= AUTON_LEFT_CUBE) {
		startTask(autonStarsCubeLeft);

	} else if (autonSelection <= AUTON_RIGHT_STARS) {
		startTask(autonKnockStarsRight);

	} else if (autonSelection <= AUTON_RIGHT_CUBE) {
		startTask(autonStarsCubeRight);

	} else if (autonSelection <= AUTON_SKILLS) {
		startTask(autonSkills);

	}

}

task drivetrainController() {
	int lYRequested,
			rYRequested,
			lYLastSent = 0,
			rYLastSent = 0,
			lY,
			rY,
			slewRateLimit = 15,
			threshold = 15;
	while(true) {
		lYRequested = vexRT[Ch3];
		rYRequested = vexRT[Ch2];
		if (abs(lYRequested - lYLastSent) > slewRateLimit) { //if the new power requested is greater than the slew rate limit
			if (lYRequested > lYLastSent) {
				lY += slewRateLimit; //only increase the power by the max allowed by the slew rate
			} else {
				lY -= slewRateLimit; //only decrease the power by the max allowed by the slew rate
			}
		} else {
			lY = (lYRequested == 0) ? 0 : lY;
		}
		lYLastSent = lY;
		if (abs(rYRequested - rYLastSent) > slewRateLimit) {
			if (rYRequested > rYLastSent) {
				rY += slewRateLimit;
			} else {
				rY -= slewRateLimit;
			}
		} else {
			rY = (rYRequested == 0) ? 0 : rY;
		}
		rYLastSent = rY;
		motor[lDriveFront] = (abs(lY) > threshold) ? lY : 0;
		motor[lDriveBack] = (abs(lY) > threshold) ? lY : 0;
		motor[rDriveFront] = (abs(rY) > threshold) ? rY : 0;
		motor[rDriveBack] = (abs(rY) > threshold) ? rY : 0;
		wait1Msec(15);
	}
}

task usercontrol()
{
	/*
	SensorValue[hangLock] = 0;
	//sensorValue[platformLock] = 1;
	//setDumpMotors(40)
	//wait10Msec(5);
	//setDumpMotors(0);
	SensorValue[rDriveEnc] = 0;
	wait10Msec(50);
	while(SensorValue[rDriveEnc] > -2100)
	{
		setRightDtMotors(-75);
		setLeftDtMotors(-75);
	}
	//setDumpMotors(-50);
	//wait10Msec(18);
	//setDumpMotors(0);
	while(SensorValue[rDriveEnc] > -2775)
	{
		setLeftDtMotors(-124.5);
		setRightDtMotors(-26.5);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	//start play 2
	wait10Msec(50);
	while(SensorValue[rDriveEnc] < -2275)
	{
		setLeftDtMotors(85);
		setRightDtMotors(85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] > -350)
	{
		setLeftDtMotors(85);
		setRightDtMotors(-85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] < 1300)
	{
		setLeftDtMotors(85);
		setRightDtMotors(85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	SensorValue[platformLock] = 1;
	wait10Msec(34);
	setDumpMotors(18);
	wait10Msec(25);
	setDumpMotors(-12);
	SensorValue[rDriveEnc] = 0;
	wait10Msec(50);
	while(SensorValue[rDriveEnc] < 600)
	{
		setLeftDtMotors(-60);
		setRightDtMotors(60);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] > -242)
	{
		setLeftDtMotors(-60);
		setRightDtMotors(-60);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	setDumpMotors(100);
	wait10Msec(50);
	setDumpMotors(0);*/
	/*SensorValue[rDriveEnc] = 0;
	wait10Msec(50);
	while(SensorValue[rDriveEnc] > -900)
	{
		setRightDtMotors(-75);
		setLeftDtMotors(-75);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(300);
	SensorValue[platformLock] = 1;
	setDumpMotors(95);
	wait10Msec(17);
	while(SensorValue[rDriveEnc] > -3092)
	{
		setRightDtMotors(-120);
		setLeftDtMotors(-120);
	}
	setDumpMotors(0);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(25);
	while(SensorValue[rDriveEnc] < -2350)
	{
		setRightDtMotors(75);
		setLeftDtMotors(75);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	while(sensorValue[platformDown] == 0)
	{
		setDumpMotors(-120);
	}
	SensorValue[platformLock] = 0;
	setDumpMotors(0);
	wait10Msec(300);
	SensorValue[platformLock] = 1;
	setDumpMotors(95);
	wait10Msec(17);
	while(SensorValue[rDriveEnc] > -3092)
	{
		setRightDtMotors(-120);
		setLeftDtMotors(-120);
	}
	setDumpMotors(0);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(25);
	while(SensorValue[rDriveEnc] < -2350)
	{
		setRightDtMotors(75);
		setLeftDtMotors(75);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	while(sensorValue[platformDown] == 0)
	{
		setDumpMotors(-120);
	}
	SensorValue[platformLock] = 0;
	setDumpMotors(0);
	wait10Msec(300);
	SensorValue[platformLock] = 1;
	setDumpMotors(95);
	wait10Msec(17);
	while(SensorValue[rDriveEnc] > -3092)
	{
		setRightDtMotors(-120);
		setLeftDtMotors(-120);
	}
	setDumpMotors(0);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(25);
	while(SensorValue[rDriveEnc] < -2350)
	{
		setRightDtMotors(75);
		setLeftDtMotors(75);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	while(sensorValue[platformDown] == 0)
	{
		setDumpMotors(-120);
	}
	SensorValue[platformLock] = 0;
	setDumpMotors(0);
	while(SensorValue[rDriveEnc] > -2275)
	{
		setLeftDtMotors(-85);
		setRightDtMotors(-85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] > -650)
	{
		setLeftDtMotors(85);
		setRightDtMotors(-85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] < 1300)
	{
		setLeftDtMotors(85);
		setRightDtMotors(85);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	SensorValue[platformLock] = 1;
	wait10Msec(34);
	setDumpMotors(18);
	wait10Msec(25);
	setDumpMotors(-12);
	SensorValue[rDriveEnc] = 0;
	wait10Msec(50);
	while(SensorValue[rDriveEnc] < 600)
	{
		setLeftDtMotors(-60);
		setRightDtMotors(60);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(50);
	SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] > -242)
	{
		setLeftDtMotors(-60);
		setRightDtMotors(-60);
	}
	setLeftDtMotors(0);
	setRightDtMotors(0);
	setDumpMotors(100);
	wait10Msec(50);
	setDumpMotors(0);*/
	//startTask(autonomous);
	//stopTask(usercontrol);
	//startTask(platformLockController);
	//startTask(drivetrainController);
	while(1) {
		if(vexRT[Btn6U])
		{
			SensorValue[hangLock] = 0;
		}
		else if(vexRT[Btn6D])
		{
			SensorValue[hangLock] = 1;
		}
	}
}
