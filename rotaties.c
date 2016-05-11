
#include <p18f4550.h>
#include <delays.h>
#include <string.h>
#include "dwengoDelay.h"
#include "dwengoBoard.h"
#include "dc_motor.h"
#include "servo.h"

//TODO
#define DEG0 5
#define DEG1 10
#define DEG2 15
#define DEG3 20
#define DEG4 25

/*char state1;  //begin altijd bij 1.5 ms
char state2; 
char state3; 
char state4; */

//TODO Matrix updates
void RCW() {
	// servoB 90 clockwise draaien
    state2 = DEG3;
	//M1 open doen
    motor1open();
	// servoB terug op 0 graden zetten
    state2 = DEG2;
	//M1 terug toe doen
    motor2toe();    

}

void RCCW() {
	//servoB 90 counter clockwise draaien 
    state2 = DEG1;
	//M1 open doen
    motor1open();
	//servoB terug op 0 graden zetten
    state1 = DEG2;
	//M1 terug toe doen
    motor1toe();
}

void LCW() {
	//servoD 90 clockwise draaien
    state4 = DEG3;
	//M1 open
    motor1open();
	//servoD terug op 0 graden zetten
    state4 = DEG2;
	//M1 terug toe doen
    motor1toe();
}

void LCCW() {
	//servoD 90 counter clockwise draaien 

	//M1 open doen

	//servoD terug op 0 graden zetten

	//M1 terug toe doen

}

void FCW() {
	//servoC 90  clockwise draaien 

	//M2 open doen

	//servoC terug op 0 graden zetten

	//M2 terug toe doen
}

void FCCW() {
	//servoC 90 counter clockwise draaien 

	//M2 open doen

	//servoC terug op 0 graden zetten

	//M2 terug toe doen
}

void BCW() {
	//servoA 90  clockwise draaien 

	//M2 open doen

	//servoA terug op 0 graden zetten

	//M2 terug toe doen

}

void BCCW() {
	//servoA 90  counter clockwise draaien 

	//M2 open doen

	//servoA terug op 0 graden zetten

	//M2 terug toe doen
}

void UCW() { // u=up, d=down
	// we maken van up eerst front
	//M2 open doen

	//tegelijk servoD 90 graden clockwise en servoB 90 graden counter clockwise

	//M2 toe doen

	//M1 open doen

	// servoD en servoB terug op 0

	//M1 toe doen

	// gebruik FCW

	//M2 open doen

	//tegelijk servoD 90 graden counter clockwise en servoB 90 graden clockwise

	// M2 toe doen
}

void UCCW() {
	// we maken van up eerst front
	//M2 open doen

	//tegelijk servoD 90 graden clockwise en servoB 90 graden counter clockwise

	//M2 toe doen

	//M1 open doen

	// servoD en servoB terug op 0

	//M1 toe doen

	// gebruik FCCW

	//M2 open doen

	//tegelijk servoD 90 graden counter clockwise en servoB 90 graden clockwise

	// M2 toe doen

}

void DCW() {
	// we maken van down eerst front
	//M2 open doen

	//tegelijk servoD 90 graden counter clockwise en servoB 90 graden clockwise

	//M2 toe doen

	//M1 open doen

	// servoD en servoB terug op 0

	//M1 toe doen

	// gebruik FCW

	//M2 open doen

	//tegelijk servoD 90 graden clockwise en servoB 90 graden counter clockwise

	// M2 toe doen

}

void DCCW() {
	// we maken van down eerst front
	//M2 open doen

	//tegelijk servoD 90 graden counter clockwise en servoB 90 graden clockwise

	//M2 toe doen

	//M1 open doen

	// servoD en servoB terug op 0

	//M1 toe doen

	// gebruik FCCW

	//M2 open doen

	//tegelijk servoD 90 graden clockwise en servoB 90 graden counter clockwise

	// M2 toe doen

}
