#include <p18f4550.h>
#include <delays.h>
#include <string.h>
#include "dwengoDelay.h"
#include "dwengoBoard.h"
#include "dc_motor.h"

void initPWM(){
    
    PR2 = 0b10000000; /*  periode PWM*/
    CCPR1L = 0b00000000; /* duty cycle PWM 1*/
    TRISAbits.RA4 = 0; /* poorten PWM 1 op 0 zetten */
    TRISCbits.RC2 = 0;/* poort CCP 1 als output zetten */
    CCP1CONbits.DC1B1 = 0; /* Duty cycle LSBs PWM1 */
    CCP1CONbits.DC1B0 = 0; /* Duty cycle LSBs PWM1 */
    CCP1CONbits.CCP1M = 0b1100;/* instellen module 1 als PWM*/
    
    CCPR2L = 0b00000000; /* duty cycle PWM 2*/
    TRISBbits.RB3 = 0; /* poorten PWM2 op 0 zetten*/
    TRISCbits.RC1 = 0;/* poort CCP2 als output zetten */
    CCP2CONbits.DC2B1 = 0; /* Duty cycle LSBs PWM2 */
    CCP2CONbits.DC2B0 = 0; /* Duty cycle LSBs PWM2 */
    CCP2CONbits.CCP2M = 0b1100;/* instellen module 2 als PWM*/
    T2CONbits.TMR2ON = 1; /* zet timer op voor PWM*/
}

void motor1(char richting, int tijd){
    if(richting==0){ /* achteruit*/
           LATAbits.LATA4 = 1;
           CCPR1L = 0b01000000;
       }
       else { /* vooruit */
           LATAbits.LATA4 = 0;
           CCPR1L = 0b01100000;
       }
    delay_ms(100*tijd); /* Delay van 100 ms per tijdseenheid*/
    LATAbits.LATA4 = 0; /* Motor afleggen*/
    CCPR1L = 0b00000000;
}

void motor2(char richting, int tijd){
    if(richting==0){ /* achteruit*/
           LATBbits.LATB3 = 1;
           CCPR2L = 0b01000000;
       }
       else { /* vooruit */
           LATBbits.LATB3 = 0;
           CCPR2L = 0b01100000;
       }
    delay_ms(100*tijd); /* Delay van 100 ms per tijdseenheid*/
    LATBbits.LATB3 = 0; /* Motor afleggen*/
    CCPR2L = 0b00000000;
}

void motor1open(){
    motor1(0,6);
}

void motor1toe(){
    motor1(1,4);
}

void motor2open(){
    motor2(0,6);
}

void motor2toe(){
    motor2(1,4);
}

