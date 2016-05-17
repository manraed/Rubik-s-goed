/**@file servo.c
 * @brief Bevat de functies voor de aansturing van de servos en het onderhouden van de gerelateerde PWM-puls.
 * @author Maximiliaan Leyman
 * @author Maarten Anraed
 * @author Michiel Povré
 * @bug Geen gekend
 */


#include <p18f4550.h>
#include <delays.h>
#include <string.h>
#include "dwengoDelay.h"
#include "dwengoBoard.h"
#include "dwengoLCD.h"
#include "servo.h"

//D.m.v. deze macro's kunnen de verschillende PWM periodes ingegeven worden die overeenkomen met de juiste hoeken
#define HOEK0 15
#define HOEKN90 24
#define HOEK90 7
#define HOEK10 14
#define HOEKN10 16

//Eenmalig initialiseren van de (globale) variabelen die gebruikt worden bij de timer interrupts
unsigned short timervlag = 0;
unsigned char state1 = 15;
unsigned char state2 = 15;
unsigned char state3 = 15;
unsigned char state4 = 15;

/*Deze functie dient eenmalig uitgevoerd te worden bij het opstarten om de pinnen voor de servo's
  en de timer voor hun bediening te initialiseren*/

/**@brief: Initialiseert de timer, interrupts en pinnen correct for de operatie van de servo's
 * @param: void
 * @return: void
 */
void initServo() {
    
    /* Initialisatie Timer */
    RCONbits.IPEN = 1; /* Interrupt priority enable bit */
    IPR1bits.TMR1IP = 0 ; /*Priority voor de timer interrupt op laag zetten*/
    PIE1bits.TMR1IE = 1; /*Interrupt enable bit voor timer 1*/
    INTCONbits.GIE = 1; /*Global interrupt enable bit*/
    INTCONbits.PEIE = 1; /*Peripheral interrupt enable bit*/
    RCONbits.SBOREN = 0; /*BOR Software enable bit uizetten - a.h.v. het voorbeeld van practicum 2*/
    PIR1bits.TMR1IF = 0; /*Timer 1 interrupt flag klaarzetten om de interrupt op te vangen*/

    //T1CONbits.RD16 = 0; /* 16 bit read/write mode uit*/

    TMR1H = 0b11111111; /* Zet timer overflow op 1/10 van 1ms*/
    TMR1L = 0b01101001; /* Bij overflow van dit register wordt de TMR1IF flag bit op 1 gezet en de interrupt getriggerd*/
    T1CONbits.T1CKPS0 = 1; /*Prescaler */
    T1CONbits.T1CKPS1 = 1;
    
    /* Zetten servo-outputs */
    TRISBbits.RB4 = 0; /* R4-R7 pinnen zetten als output, voor het sturingssignaal van de servo's */
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    TRISBbits.RB7 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
    LATBbits.LATB6 = 0;
    LATBbits.LATB7 = 0;

    /*Timer 1 aan*/
    T1CONbits.TMR1ON = 1;
    
    
}

/*Deze functie dient elke 0.1ms opgeroepen te worden door de timer, en onderhoudt de juiste periode voor het signaal dat
 naar de servo's gestuurd wordt, a.d.h.v. de waarden opgeslagen in de state-variabelen*/

/**@brief: Bij elke timer interrupt wordt deze functie opgeroepen en zorgt ze dat de puls voor de servo's correct doorgegeven wordt
 * @param: void
 * @return: void
 */
void updateServo(void){
    /*Telkens de functie opgeroepen wordt, wordt de vlag geincrementeerd*/
    timervlag++;
    /*Wanneer de volle periode van 200*0.1ms = 20ms verlopen is, reset de vlag zich en worden alle outputs hoog gezet*/
    if(timervlag==200){
        SERV1 = 1;
        SERV2 = 1;
        SERV3 = 1;
        SERV4 = 1;
        timervlag = 0;
    }
    /*De outputs blijven hoog totdat de waarde in bijhorende state-variabele bereikt is, waarna ze op 0 gezet worden en
     laag blijven totdat de volgende periode begint.*/
    if(timervlag >= state1) SERV1 = 0;
    if(timervlag >= state2) SERV2 = 0;
    if(timervlag >= state3) SERV3 = 0;
    if(timervlag >= state4) SERV4 = 0;
}

/*Deze vier functies nemen een hoek als input, en updaten de servo's zo dat ze naar de bijhorende hoek draaien.*/

/**@brief: Deze functie zet de staat van servo 1 op de gegeven hoek
 * @param: char hoek: De gewenste hoek om de servo op te zetten
 * @return: void
 */
char servo1(char hoek){
    switch(hoek){
        case -90:{
            state1 = HOEKN90;
            break;
        }
        case 90:{
            state1 = HOEK90;
            break;
        }
        case 0:{
            state1 = HOEK0;
            break;
        }
        case -10:{
            state1 = HOEKN10;
            break;
        }
        case 10:{
            state1 = HOEK10;
            break;
        }
        default: unsupportedStateError(hoek, 1);
    }

}

/**@brief: Deze functie zet de staat van servo 2 op de gegeven hoek
 * @param: char hoek: De gewenste hoek om de servo op te zetten
 * @return: void
 */
char servo2(char hoek){
    switch(hoek){
        case -90:{
            state2 = HOEKN90;
            break;
        }
        case 90:{
            state2 = HOEK90;
            break;
        }
        case 0:{
            state2 = HOEK0;
            break;
        }
        case -10:{
            state2 = HOEKN10;
            break;
        }
        case 10:{
            state2 = HOEK10;
            break;
        }
        default: unsupportedStateError(hoek, 2);
    }
}

/**@brief: Deze functie zet de staat van servo 3 op de gegeven hoek
 * @param: char hoek: De gewenste hoek om de servo op te zetten
 * @return: void
 */
char servo3(char hoek){
    switch(hoek){
        case -90:{
            state3 = HOEKN90;
            break;
        }
        case 90:{
            state3 = HOEK90;
            break;
        }
        case 0:{
            state3 = HOEK0;
            break;
        }
        case -10:{
            state3 = HOEKN10;
            break;
        }
        case 10:{
            state3 = HOEK10;
            break;
        }
        default: unsupportedStateError(hoek, 3);
    }
}

/**@brief: Deze functie zet de staat van servo 4 op de gegeven hoek
 * @param: char hoek: De gewenste hoek om de servo op te zetten
 * @return: void
 */
char servo4(char hoek){
    switch(hoek){
        case -90:{
            state4 = HOEKN90;
            break;
        }
        case 90:{
            state4 = HOEK90;
            break;
        }
        case 0:{
            state4 = HOEK0;
            break;
        }
        case -10:{
            state4= HOEKN10;
            break;
        }
        case 10:{
            state4 = HOEK10;
            break;
        }
        default: unsupportedStateError(hoek, 4);
    }
}

/*Deze functie laat weten wanneer de gewenste hoek niet geimplementeerd is in de bovenstaande functies.*/

/**@brief: Deze functie wordt opgeroepen als er een ongeimplementeerde hoek gevraagd wordt en zet een error op het scherm
 * @param: char hoek: De gewenste hoek om de servo op te zetten, char servo: het nummer van de servo waarbij de fout optrad.
 * @return: void
 */
void unsupportedStateError(char hoek, char servo){
    clearLCD();
    appendStringToLCD("ERROR: Foute hoek bij servoaansturing");
    printIntToLCD(hoek,1,1);
    printIntToLCD(servo,1,8);
}