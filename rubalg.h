/*Zoekt een 'edgepiece' met kleur a en b, geeft de positie van kleur a terug (in decimaal getal)
Daarbij is tiental het vlak, en eenheid de positie op dat vlak*/

#ifndef RUBALG_H
#define	RUBALG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "servo.h"
#include "dc_motor.h"
#include "bewegingen.h"

int find_edgepiece(char, char, char[6][9]);
int find_corner_piece(char a, char b, char c, char[6][9]);
void bringdownedge(int a, int b, char[6][9]);

void wit_blauw_rood_inschuiven(int cp1, char[6][9]);
void wit_blauw_oranje_inschuiven(int cp2, char[6][9]);
void wit_groen_rood_inschuiven(int cp2, char[6][9]);
void wit_groen_oranje_inschuiven(int cp2, char[6][9]);

void solve_middle_layer(char[6][9]);
int midden_test(char[6][9]);
void recht_midden_plaatsen(char[6][9]);
void links_midden_plaatsen(char[6][9]);
void midden_indraaien(char[6][9]);
int find_good_edge_piece(char[6][9]);

void maak_geel_kruis(char[6][9]);
int maak_geel_tussenstap(char[6][9]);
void omsingelde_hoek(char[6][9]);
void horizontale_lijn(char[6][9]);

void maak_geel_vlak(char[6][9]);
void geel_vlak_beweging(char[6][9]);

void verwissel_edgepieces_vooraan(char[6][9]);
void yellow_corner_correct(char[6][9]);

void get_endstate(char[6][9]);
void yellow_edges_clockwise(char[6][9]);
void yellow_edges_counter_clockwise(char[6][9]);

void maak_wit_kruis(char[6][9]);
void solve_corner_pieces(char[6][9]);
#ifdef	__cplusplus
}
#endif

#endif	/* RUBALG_H*/