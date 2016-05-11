#ifndef KLEURENSENSOR_H
#define	KLEURENSENSOR_H

#define SENSOR1OUT PORTBbits.RB1
#define SENSOR2OUT PORTBbits.RB2


extern int frequentie;

void initColorSensor(void);

void updateColours();

int readIn(int);


#endif


