/**@file bewegingen.c
 * @brief Bevat de functies voor de aansturing van de servos en het onderhouden van de gerelateerde PWM-puls.
 * @author Maarten Anraed
 * @author Maximiliaan Leyman
 * @author Michiel Povré
 * @bug Geen gekend
 */

#include <p18f4550.h>
#include "kleurensensor.h"
#include "dwengoDelay.h"

int frequentie = 0;

void initColorSensor(void){

    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;

    LATAbits.LATA0 = 0; /*Prescaler voor het outputsignaal op 2% zetten.*/
    LATAbits.LATA1 = 1;

    /*Initialisatie timer 3, nodig voor het meten van de frequentie van het signaal van de kleursensor*/
    /*Een redelijk deel van deze code is redundant met de initialisatie van timer 1, maar staat hier voor de veiligheid toch.*/
    /*De methode is niet afhankelijk van de initialisatie van timer 1 om timer 3 correct te initialiseren.*/


    RCONbits.IPEN = 1; /* Interrupt priority enable bit */
    IPR2bits.TMR3IP = 0; /* Timer 3 interrupt priority bit*/
    PIE2bits.TMR3IE = 1; /* Timer 3 interrupt enable bit*/
    INTCONbits.GIE = 1; /*Interrupts enablen high priority (nodig?)*/
    INTCONbits.PEIE = 1; /*Interrupts enablen low priority*/
    RCONbits.SBOREN = 0; /*Zeker zijn dat BOR uitstaat (volgens vb. practicum)*/

    //T3CONbits.RD16 = 0; /* 16 bit read/write mode uit */
    T3CONbits.T3CCP1 = 0; /*Zorgen dat timer 3 niet interfereert met de CCP modules*/
    T3CONbits.T3CCP2 = 0;

    TMR3H = 0b11111101; /* Zetten van overflowsnelheid voor timer 3: elke 50 microseconden*/
    TMR3L = 0b10100111;
    PIR2bits.TMR3IF = 0; /*Timer 3 interrupt flag klaarzetten*/
    T3CONbits.T3CKPS0 = 1; /*Prescaler setten voor timer 3*/
    T3CONbits.T3CKPS1 = 1;
    T3CONbits.TMR3ON = 1; /*Timer aanzeten*/
}

int readIn(int kleur){

    /*Timer 3 aanzetten om de kleuren in te kunnen lezen*/
    T3CONbits.TMR3ON = 1;

    /*rood*/
    
    //LATAbits.LATA2 = 0;
    //LATAbits.LATA3 = 0;
    //delay_ms(10);
    //return frequentie;
    

    
    /*blauw*/
    LATAbits.LATA3 = 1;
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;
    delay_s(200);
    
    /*clear*/
    //LATAbits.LATA2 = 1; /*Deze twee bits bepalen welke kleur er ingelezen wordt*/
    //LATAbits.LATA3 = 0;
    //delay_ms(10); /*Een kleine delay zorgt voor tijd om de kleur in te lezen*/
    //T3CONbits.TMR3ON = 0; /*De timer wordt terug uitgezet om de ingelezen waarde te behouden en om rekenkracht te sparen*/

    return frequentie;
    
    /*groen*/
  /*  LATAbits.LATA3 = 1;
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;
    delay_ms(200);*/

}
