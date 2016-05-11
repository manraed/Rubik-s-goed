/* 
 * File:   bewegingen.h
 * Author: Maarten
 *
 * Created on 27 april 2016, 13:52
 */

#ifndef BEWEGINGEN_H
#define	BEWEGINGEN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "servo.h"
#include "dc_motor.h"

/*Vlak in wijzerzin draaien*/
void draai_wijzerzin(int, char[6][9]);

/*Vlak in tegenwijzerzin draaien*/
void draai_tegenwijzerzin(int, char[6][9]);

/*Vlak tweemaal draaien*/
void draai_dubbel(int, char[6][9]);

/*Voorvlak naar rechts draaien*/
void draai_voor_naar_rechts(char[6][9]);

/*Voorvlak naar links draaien*/
void draai_voor_naar_links(char[6][9]);

/*Voorvlak naar achter draaien*/
void draai_voor_naar_achter(char[6][9]);

/*Kubus naar voor draaien (bovenvlak wordt voorvlak)*/
void draai_onder(char[6][9]);

/*Kubus naar achter draaien (bovenvlak wordt achtervlak)*/
void draai_boven(char[6][9]);

/*Kubus naar rechts draaien (bovenvlak wordt rechtse vlak)*/
void draai_rechts(char[6][9]);

/*Kubus naar links draaien (bovenvlak wordt links vlak)*/
void draai_links(char[6][9]);

/*Rechterkant van de kubus in wijzerzin draaien*/
void RCW(char[6][9]);

/*Rechterkant van de kubus in tegenwijzerzin draaien*/
void RCCW(char[6][9]);

/*Rechterkant van de kubus tweemaal in wijzerzin draaien*/
void RCW2(char[6][9]);

/*Linkerkant van de kubus in wijzerzin draaien*/
void LCW(char[6][9]);

/*Linkerkant van de kubus in tegenwijzerzin draaien*/
void LCCW(char[6][9]);

/*Linkerkant van de kubus tweemaal in wijzerzin draaien*/
void LCW2(char[6][9]);

/*Voorkant van de kubus in wijzerzin draaien*/
void FCW(char[6][9]);

/*Voorkant van de kubus in tegenwijzerzin draaien*/
void FCCW(char[6][9]);

/*Voorkant van de kubus in tweemaal in wijzerzin draaien*/
void FCW2(char[6][9]);

/*Achterkant van de kubus in wijzerzin draaien*/
void BCW(char[6][9]);

/*Achterkant van de kubus in tegenwijzerzin draaien*/
void BCCW(char[6][9]);

/*Achterkant van de kubus tweemaal in wijzerzin draaien*/
void BCW2(char[6][9]);

/*Bovenkant van de kubus in wijzerzin draaien*/
void UCW(char[6][9]);

/*Bovenkant van de kubus in tegenwijzerzin draaien*/
void UCCW(char[6][9]);

/*Bovenkant van de kubus tweemaal draaien*/
void UCW2(char[6][9]);

/*Onderkant van de kubus in wijzerzin draaien*/
void DCW(char[6][9]);

/*Onderkant van de kubus in tegenwijzerzin draaien*/
void DCCW(char[6][9]);

/*Onderkant van de kubus tweemaal draaien*/
void DCW2(char[6][9]);
#ifdef	__cplusplus
}
#endif

#endif	/* BEWEGINGEN_H */

