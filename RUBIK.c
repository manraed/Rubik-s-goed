#include <p18f4550.h>
#include <delays.h>
#include <string.h>
#include "dwengoDelay.h"
#include "dwengoConfig.h"
#include "dwengoBoard.h"
#include "dwengoLCD.h"
#include "dc_motor.h"
#include "servo.h"
#include "kleurensensor.h"
#include "bewegingen.h"
//#include "rotaties.h"



unsigned char vlag = 0;
unsigned char kleurTimerState = 0;
unsigned char kleurTimerVlag = 0;
char flip = 0;
int a;
 
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
 
// interrupt handler routines DO NOT EDIT
#pragma code high_vector=0x08
void high_vector() {
	_asm
		goto YourHighPriorityISRCode
	_endasm
}
#pragma code

#pragma code low_vector=0x18
void low_vector() {
	_asm
		goto YourLowPriorityISRCode
	_endasm
}
#pragma code


// interrupt handler routines
#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode() {

}
 
#pragma interrupt YourLowPriorityISRCode
void YourLowPriorityISRCode() {
    if(PIR1bits.TMR1IF==1){


        updateServo();
        
        /*if(vlag==0){
            vlag = 1;
            SERV4 = 1;
        }
        else{
            vlag = 0;
            SERV4 = 0;
        }*/
        
        
        PIR1bits.TMR1IF = 0;
        //TMR1H = 0b11111111;
        //TMR1L = 0b01110001;
        TMR1H = 0b11111111;
        TMR1L = 0b10010100;

    }

    if(PIR2bits.TMR3IF==1){

        kleurTimerState++;

        if(kleurTimerVlag == 0 && SENSOR1OUT == 1){
            frequentie = kleurTimerState * 50;
            kleurTimerState = 0;
        }
        kleurTimerVlag = SENSOR1OUT;


        PIR2bits.TMR3IF = 0;
        TMR3H = 0b11111101;
        TMR3L = 0b10100111;

    }
}





// main program
void main(void) {
    
   /* PR2 = 0b10000000;   periode */
    /*CCPR2L = 0b10000000; /* duty cycle*/
    /*TRISBbits.RB3 = 0; /* als output zetten*/
    /*TRISCbits.RC1 = 0;/* als output zetten */
    /*CCP2CONbits.DC2B1 = 0; /* Duty cycle LSBs */
    /*CCP2CONbits.DC2B0 = 0; /* Duty cycle LSBs */
    /*CCP2CONbits.CCP2M = 0b1100;/* instellen PWM als output*/
    /*T2CONbits.TMR2ON = 1; /* zet timer op voor PWM*/
    //while(0){
    //   delay_s(1);
     //  if(vlag==0){
    //       LATBbits.LATB3 = 1;
    //       CCPR2L = 0b00000000;
    //       vlag = 1;
    //   }
    //   else {
    //       LATBbits.LATB3 = 0;
    //       CCPR2L = 0b10000000;
    //       vlag = 0;
    //   }
    //}
    //CCPR2L = 0;
    initPWM();
    initLCD();
    initServo();
    initColorSensor();
    //delay_s(1);
    //motor2(1,3); /* vooruit */
    //delay_s(2);
    //motor2(0,3); /*  achteruit/open */
  while(0){
    motor1(1,3);
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 2");
    motor2(0,3);
    delay_s(1);
    motor2(1,3);
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 1");
    motor1(0,3);
    delay_s(1);
    
  }
    
    // servo proberen
    state1 = 15; /* begin altijd bij 1.5 ms*/
    state2 = 15;
    state3 = 15;
    state4 = 15;


    clearLCD();
    for(flip = 1;flip<11;flip++){
        printIntToLCD(flip,0,1);
        delay_s(1);
    }

    /*
    clearLCD();
    appendStringToLCD("Motor 2 toe");
    motor2toe();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 1 open");
    motor1open();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Servo draaien naar 5");
    servo2(-90);
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 1 toe");
    motor1toe();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Servo draaien naar 14");
    servo2(0);
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 1 open");
    motor1open();
    delay_s(1);
    
    //state1 = 12;
    */
    
    /*
    clearLCD();
    appendStringToLCD("Motor 1 toe");
    motor1toe();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 2 open");
    motor2open();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Servo draaien naar 5");
    state2 = 5;
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 2 toe");
    motor2toe();
    delay_s(1);
    clearLCD();
    appendStringToLCD("Servo draaien naar 14");
    state2 = 14;
    delay_s(1);
    clearLCD();
    appendStringToLCD("Motor 2 open");
    motor2open();
    delay_s(1);

    state2 = 12;
    */

    //Kleurensensor
    while(1){

        clearLCD();
        for(flip = 1;flip<6;flip++){
            printIntToLCD(flip,0,1);
            delay_s(1);
        }

        clearLCD();
        appendStringToLCD("Periode gelezen:");
        a = readIn(0);
        printIntToLCD(a,1,3);
        delay_s(2);

        /*
        printIntToLCD(state1,0,1);
        printIntToLCD(state2,0,5);
        printIntToLCD(state3,1,1);
        printIntToLCD(state4,1,5);
         cur */

    }

    while(1){
        int i; int j;
        char boven[9] = "WWWWWWWWW";
	char rechts[9] = "RRRRRRRRR";
	char achter[9] = "BBBBBBBBB";
	char links[9] = "OOOOOOOOO";
	char voor[9] = "GGGGGGGGG";
	char onder[9] = "YYYYYYYYY";
	char matrix[6][9];

	/*Matrix invullen*/
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 9; j++) {
			if (i == 0) {
				matrix[i][j] = boven[j];
			}
			if (i == 1) {
				matrix[i][j] = rechts[j];
			}
			if (i == 2) {
				matrix[i][j] = achter[j];
			}
			if (i == 3) {
				matrix[i][j] = links[j];
			}
			if (i == 4) {
				matrix[i][j] = voor[j];
			}
			if (i == 5) {
				matrix[i][j] = onder[j];
			}
		}
	}
        UCCW(matrix);
    }

    
 }

//Nog te doen voor servo.c
//TODO Prescaler bits controleren
//TODO Evt. timer periode aanpassen
//TODO 16 bit read-writemode nakijken - waarschijnlijk lijn deleten

