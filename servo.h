/* 
 * File:   servo.h
 * Author: michiel
 *
 * Created on 2 maart 2016, 16:36
 */


//#ifdef	__cplusplus
//extern "C" {
//#endif

#ifndef SERVO_H
#define	SERVO_H

#define SERV1 LATBbits.LATB4
#define SERV2 LATBbits.LATB5
#define SERV3 LATBbits.LATB6
#define SERV4 LATBbits.LATB7

    extern unsigned char state1;
    extern unsigned char state2;
    extern unsigned char state3;
    extern unsigned char state4;
    extern unsigned short timervlag;

    void initServo(void);
    void updateServo(void);
    char servo1(char hoek);//TODO
    char servo2(char hoek);//TODO
    char servo3(char hoek);//TODO
    char servo4(char hoek);//TODO

    void unsupportedStateError(char hoek, char servo);
    

#endif  /* SERVO_H */

//#ifdef	__cplusplus
//}
//#endif

