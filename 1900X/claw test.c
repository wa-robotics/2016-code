#pragma config(Sensor, dgtl1,  btn1,           sensorTouch)
#pragma config(Sensor, dgtl2,  btn2,           sensorTouch)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

	while(1) {
		motor[port9] = vexRT[Btn6U]*127 - vexRT[Btn6D]*127;
	}

}