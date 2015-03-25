#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Sensor, S3,     ,               sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-irseeker-v2.h";
#include "JoystickDriver.c"
int AUTMOTPOW = 25;
//int AUTMOTPOW = 90;


void setArm(float target)
{
	while((nMotorEncoder[motorArm]) < target)
	{
		motor[motorArm] = 90;
	}
	while((nMotorEncoder[motorArm]) > target)
	{
		motor[motorArm] = -90;
	}
	motor[motorArm] = 0;
}
void setArm(float target, int power)
{
	while((nMotorEncoder[motorArm]) < target)
	{
		motor[motorArm] = power;
	}
	while((nMotorEncoder[motorArm]) > target)
	{
		motor[motorArm] = -power;
	}
	motor[motorArm] = 0;
}

void dropBall()
{
	servo[servo2] = 202;
}
void closeBall()
{
	servo[servo2] = 160;
}
void dropBallWiggle(int freq, int total)
{
	time1[timer2] = 0;
	while(time1[timer2] < total)
	{
		dropBall();
		time1[timer3] = 0;
		while(time1[timer3] < freq/2  && time1[timer2] < total)
		{

		}
		closeBall();
		time1[timer3] = 0;
		while(time1[timer3] < freq/2  && time1[timer2] < total)
		{

		}
	}
}

void stopMotors()
{
	motor[motorLeft] = 0;
	motor[motorRight] = 0;
}
void stopAllTime(int time)
{
		stopMotors();
		wait1Msec(time);
}

void turnLeftEncoder(float clicks)
{
	motor[motorRight] = 0;
	motor[motorLeft] = AUTMOTPOW;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks)
	{
		//do nohing
	}
	stopMotors();
}

void turnRightEncoder(float clicks)
{
	motor[motorRight] = 0;
	motor[motorLeft] = -AUTMOTPOW;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks)
	{
		//do nohing
	}
	stopMotors();
}

void turnRightEncoder(float clicks, int time)
{
	motor[motorRight] = 0;
	motor[motorLeft] = -AUTMOTPOW;
	time1[T1]= 0;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks && time1[T1] < time)
	{
		//do nohing
	}
	stopMotors();
}

void turnRightBackEncoder(float clicks, int time) //Robbie was here
{
	motor[motorRight] = 0;
	motor[motorLeft] = AUTMOTPOW;
	time1[T1]= 0;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks && time1[T1] < time)
	{
		//do nohing
	}
	stopMotors();
}
void turnLeftBackEncoder(float clicks, int time)
{
	motor[motorRight] = -AUTMOTPOW;
	motor[motorLeft] = 0;
	time1[T1]= 0;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks && time1[T1] < time)
	{
		//do nohing
	}
	stopMotors();
}

void moveForward()
{
	motor[motorLeft] = -AUTMOTPOW;
	motor[motorRight] = AUTMOTPOW;
}

void moveBackward()
{
	motor[motorLeft] = AUTMOTPOW;
	motor[motorRight] = -AUTMOTPOW;
}

void moveForwardEncoder(float clicks)
{
	moveForward();
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks)
	{
		//do nohing
	}
	stopMotors();
}
void moveForwardEncoder(float clicks, int time)
{
	moveForward();
	time1[T1]= 0;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks && time1[T1] < time)
	{
		//do nohing
	}
	stopMotors();
}

void moveBackwardEncoder(float clicks)
{
	moveBackward();
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks)
	{
		//do nohing
	}
	stopMotors();
}
void moveBackwardEncoderSpecial(float clicks)
{
	moveBackward();
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks)
	{
		//do nohing
		if (abs(nMotorEncoder[motorLeft]) >= clicks/2)
		{
			servo[servo1] = 155;
		}
	}
	stopMotors();
}
void moveBackwardEncoder(float clicks, int time)
{
	moveBackward();
	time1[T1]= 0;
	nMotorEncoder[motorLeft] = 0;
	while(abs(nMotorEncoder[motorLeft]) < clicks && time1[T1] < time)
	{
		//do nohing
	}
	stopMotors();
}

/////////////////////////////////////////////////////////////////////////////////////////




task main()
{
	nxtDisplayTextLine(0, "Ramp Autonomous%s", "");
	//waitForStart();
	int direction = 0;
	int direction2 = 0;
	int strength = 0;
	int strength2 = 0;
	string phase = "movingToBlueLine";
	int irPosition = -1;
	bool running = true;
	HTIRS2readEnhanced(S2,direction,strength);
	HTIRS2readEnhanced(S3,direction2,strength2);
	nMotorEncoder[motorArm] = 0;
	//motor[motorA] = 100;
	servo[servo1] = 230;
	servo[servo2] = 160;
	setArm(-1850);

	AUTMOTPOW = 100;
	moveBackwardEncoder(10246);
	stopAllTime(500);
	AUTMOTPOW = 30;
	moveBackwardEncoderSpecial(651);
	stopAllTime(500);
	//servo[servo1] = 155;
	setArm(-9200);
	stopAllTime(500);
	turnRightBackEncoder(6550, 1000000);
	stopAllTime(500);
	moveForwardEncoder(1675);
	stopAllTime(1500);
	dropBallWiggle(200,2500);
	stopAllTime(500);
	turnRightBackEncoder(225, 1000000);
	stopAllTime(500);
	AUTMOTPOW = 100;
	moveBackwardEncoder(13500);
	stopAllTime(500);


	setArm(-2000,70);
	setArm(0,20);
}
