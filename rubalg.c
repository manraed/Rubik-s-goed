#include "rubalg.h"
#include "bewegingen.h"

// STAGE 1: maken van een wit kruis

/*@brief: functie lost fase 1 op: het maken van een witkruis
 * maakt een wit kruis door een wit-kleur edgepiece op de juiste plaats te brengen
 * startfase van deze functie moet het wit vlak vanboven en het groene vlak vooraan zijn: dit staat zo, omdat de kubus zo in de solver dient geplaatst te worden
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@bug: zit nog bug: het reeds gevonden kruis wordt toch soms nog verbroken
 *@return void (matrix heeft nu een wit vlak) */
void maak_wit_kruis(char matrix[6][9]) {
	int wb; int wo; int wg; int wr;
	// eerst wit-blauw edgepiece correct plaatsen
	wb = find_edgepiece('W', 'B', matrix); 
   // wb/10 is vlak, wb%10 is positie
	if (wb % 10 == 1 && wb / 10 == 0) { draai_voor_naar_links(matrix); }
	if (wb / 10 != 0 || wb % 10 != 1) {
		bringdownedge(wb / 10, wb % 10, matrix);
		wb = find_edgepiece('W', 'B', matrix);
		if (wb / 10 == 5) { // het witte van wb zit in ondervlak
			// draai zodat blauw gealligneerd is met het blauwe vlak
			if (wb % 10 == 3) { DCW(matrix); }
			if (wb % 10 == 5) { DCCW(matrix); }
			if (wb % 10 == 7) { DCW2(matrix); }
			BCW2(matrix);  // naar boven draaien
			draai_voor_naar_links(matrix); // zet blauw rechts
		}
		else {
			if (wb / 10 == 1) { // witte ligt in rechtervlak, blauw in onder
				DCW(matrix);
				BCW2(matrix);
			}
			if (wb / 10 == 3) {
				DCCW(matrix);
				BCW2(matrix);
			}
			if (wb / 10 == 4) {
				DCW2(matrix);
				BCW2(matrix);
			}
			if (wb / 10 == 2) {
				BCW2(matrix);
			}
			draai_voor_naar_links(matrix); /* zet blauw rechts*/
			RCCW(matrix);
			UCW(matrix);
			FCCW(matrix);
			UCCW(matrix);
		} 
	}
	/*	nu staat wit-blauw correct, volgende is wit-oranje */
	wo = find_edgepiece('W', 'O', matrix);
	/* draai wit-oranje naar beneden */
	if (wo / 10 == 1) {
		if (wo % 10 == 1) { BCCW(matrix); }// wit zit nu beneden
		if (wo % 10 == 7) { FCW(matrix); }// wit zit beneden
	}
	if (wo / 10 == 0) {
		if (wo % 10 == 3) { LCW2(matrix); }
		if (wo % 10 == 7) { FCW2(matrix); }
	}
	if (wo / 10 == 2) {
		if (wo % 10 == 3) { LCCW(matrix); }
		if (wo % 10 == 5) { BCCW(matrix); }
		if (wo % 10 == 7) { BCW2(matrix); }
	}
	if (wo / 10 == 3) {
		bringdownedge(wo / 10, wo % 10, matrix);
	}
	if (wo / 10 == 4) {
		if (wo % 10 == 1) { FCW2(matrix); }
		if (wo % 10 == 3) { RCW(matrix); }
		if (wo % 10 == 5) { FCW(matrix); }
	}
	wo = find_edgepiece('W', 'O', matrix); // positie van wit-oranje in ondervlak
	if (wo % 10 == 1 && wo / 10 == 0) { draai_voor_naar_links(matrix); }
	if (wo / 10 != 0 || wo % 10 != 1) { // anders ligt oranje al goed
		if (wo / 10 == 5) { // het witte van wo zit in ondervlak
			if (wo % 10 == 5) { DCCW(matrix); } // juist draaien zodat gealligneerd is met blauwcenter
			if (wo % 10 == 7) { DCW2(matrix); }
			if (wo % 10 == 3) { DCW(matrix); }
			BCW2(matrix); // naar boven draaien
			draai_voor_naar_links(matrix); // zet rood naar rechts
		}
		else { // witte zit niet juist: Ri-U-Fi-Ui doen om goed te krijgen
			if ( wo / 10 == 1) { // witte ligt in rechtervlak, oranje in onder
				DCW(matrix);
				BCW2(matrix);
			}
			if (wo / 10 == 3) {
				DCCW(matrix);
				BCW2(matrix);
			}
			if (wo / 10 == 4) {
				DCW2(matrix);
				BCW2(matrix);
			}
			if (wo / 10 == 2) {
				BCW2(matrix);
			}
			draai_voor_naar_links(matrix); /* zet oranje rechts*/
			RCCW(matrix);
			UCW(matrix);
			FCCW(matrix);
			UCCW(matrix);
		} // let op: vlak oranje staat nu rechts
	}

	// blauw en oranje zitten goed: nu groen-wit piece
	wg = find_edgepiece('W', 'G', matrix);
	if (wg % 10 == 1 && wg / 10 == 0) { draai_voor_naar_links(matrix); }
	if (wg / 10 == 1) {
		if (wg % 10 == 1) { BCCW(matrix); }// wit zit nu beneden
		if (wg % 10 == 7) { FCW(matrix); }// wit zit beneden
	}
	if (wg / 10 == 0) {
		if (wg % 10 == 3) { LCW2(matrix); }
		if (wg % 10 == 7) { FCW2(matrix); }
	}
	if (wg / 10 == 2) {
		// bij 1 zit hij goed
		if (wg % 10 == 3) { LCCW(matrix); }
		if (wg % 10 == 5) { BCCW(matrix); }
		if (wg % 10 == 7) { BCW2(matrix); }
	}
	if (wg / 10 == 3) {
		bringdownedge(wg / 10, wg % 10, matrix);
	}
	if (wg / 10 == 4) {
		if (wg % 10 == 1) { FCW2(matrix); }
		if (wg % 10 == 3) { LCW(matrix); }
		if (wg % 10 == 5) { FCW(matrix); }
	}
	wg = find_edgepiece('W', 'G', matrix);
	if (wg / 10 == 5) { // het witte van wg zit in ondervlak
		if (wg % 10 == 3) { DCW(matrix); } 
		if (wg % 10 == 5) { DCCW(matrix); }
		if (wg % 10 == 7) { DCW2(matrix); }
		BCW2(matrix); // naar boven draaien
		draai_voor_naar_links(matrix); // zet groen rechts
	}
	else { // witte zit niet juist: Ri-U-Fi-Ui doen om goed te krijgen
		if (wg / 10 == 1) { // witte ligt in rechtervlak, groene in onder
			DCW(matrix);
			BCW2(matrix);
		}
		if (wg / 10 == 3) {
			DCCW(matrix);
			BCW2(matrix);
		}
		if (wg / 10 == 4) {
			DCW2(matrix);
			BCW2(matrix);
		}
		if (wg / 10 == 2) {
			BCW2(matrix);
		}
		draai_voor_naar_links(matrix); /* zet groen rechts*/
		RCCW(matrix);
		UCW(matrix);
		FCCW(matrix);
		UCCW(matrix);
	} // let op: vlak groen staat nu rechts
	  // blauw,oranje en groen zitten goed: nu rood-wit 
	wr = find_edgepiece('W', 'R', matrix);
	//	 wb/10 is vlak, wb%10 is positie
	if (wr / 10 == 1) {
		if (wr % 10 == 1) { BCCW(matrix); }// wit zit nu beneden
		if (wr % 10 == 7) { FCW(matrix); }// wit zit beneden
	}
	if (wr / 10 == 0) {
		if (wr % 10 == 3) { LCW2(matrix); }
		if (wr % 10 == 7) { FCW2(matrix); }
	}
	if (wr / 10 == 2) {
		// bij 1 zit hij goed
		if (wr % 10 == 3) { LCCW(matrix); }
		if (wr % 10 == 5) { BCCW(matrix); }
		if (wr % 10 == 7) { BCW2(matrix); }
	}
	if (wr / 10 == 3) {
		bringdownedge(wr / 10, wr % 10, matrix);
	}
	if (wr / 10 == 4) {
		if (wr % 10 == 3) { LCW(matrix); DCW(matrix); LCCW(matrix); }
		if (wr % 10 == 5) { FCW(matrix); DCW(matrix); FCCW(matrix);	}
	}
	wr = find_edgepiece('W', 'R', matrix);
	if (wr % 10 == 1 && wr / 10 == 0) { draai_voor_naar_links(matrix); }
	if (wr / 10 != 0 || wr % 10 != 1) { 
		bringdownedge(wr / 10, wr % 10, matrix);
		wr = find_edgepiece('W', 'R', matrix);
		if (wr / 10 == 5) { // het witte van wr zit in ondervlak
			if (wr % 10 == 3) { DCW(matrix); } 
			if (wr % 10 == 5) { DCCW(matrix); }
			if (wr % 10 == 7) { DCW2(matrix); }
			BCW2(matrix); // naar boven draaien
			draai_voor_naar_links(matrix); // rood rechts zetten
		}
		else { // witte zit niet juist: Ri-U-Fi-Ui doen om goed te krijgen
			if (wr / 10 == 1) { // witte ligt in rechtervlak, rode in onder
				DCW(matrix);
				BCW2(matrix);
			}
			if (wr / 10 == 3) {
				DCCW(matrix);
				BCW2(matrix);
			}
			if (wr / 10 == 4) {
				DCW2(matrix);
				BCW2(matrix);
			}
			if (wr / 10 == 2) {
				BCW2(matrix);
			}
			draai_voor_naar_links(matrix); /* zet rood rechts*/
			RCCW(matrix);
			UCW(matrix);
			FCCW(matrix);
			UCCW(matrix);
		} // let op: vlak rood staat nu rechts: zoals start positie

	}
}

/*@brief: hulpfunctie die de edgepiecepositie zoekt van edgepiece met kleuren a en b
 *@param: char matrix[6][9]: de matrix van de kubus
 *        char a: kleur van blok
 *		  char b: kleur van blok
 *@return  int: tiental is het vlak van char a, eenheid de positie van char a in het vlak, geeft dus positie van eerst meegegeven kleur terug! */
int find_edgepiece(char a, char b, char matrix[6][9]){ // geeft vlak en positie terug in een int[2], werkt!
    int i; int j;
	int result ; 
	//edge enkel op pos met oneven indexen zoeken
	for (i = 0; i < 6; i++) {
	for (j = 1; j < 8; j += 2) {
		if (matrix[i][j] == a) { // blokje is kleur a
			if (i == 0) {
				if (j == 1) {
					if (matrix[2][7] == b) {
						return 10 * i + j;
					}
						}
				if (j == 3) {
					if (matrix[3][5] == b) {
						return 10 * i + j;
					}
						}
				if (j == 5) {
					if (matrix[1][3] == b) {
						return 10 * i + j;
							}
						}
				if (j == 7) {
					if (matrix[4][1] == b) {
						return 10 * i + j;
							}
						}
					}
			if (i == 1) {
				if (j == 1) {
					if (matrix[2][5] == b) {
						return 10 * i + j;
							}
						}
				if (j == 3) {
					if (matrix[0][5] == b) {
						return 10 * i + j;
							}
						}
				if (j == 5) {
					if (matrix[5][3] == b) {
						return 10 * i + j;
							}
						}
				if (j == 7) {
					if (matrix[4][5] == b) {
						return 10 * i + j;
							}
						}
					}
			if (i == 2) {
				if (j == 1) {
					if (matrix[5][1] == b) {
						return 10 * i + j;
							}
						}
				if (j == 3) {
					if (matrix[3][1] == b) {
						return 10 * i + j;
							}
						}
				if (j == 5) {
					if (matrix[1][1] == b) {
						return 10 * i + j;
							}
						}
				if (j == 7) {
					if (matrix[0][1] == b) {
						return 10 * i + j;
							}
						}
					}

			if(i == 3) {
				if (j == 1) {
					if (matrix[2][3] == b) {
						return 10 * i + j;
							}
						}
				if (j == 3) {
					if (matrix[5][5] == b) {
						return 10 * i + j;
							}
						}
				if (j == 5) {
					if (matrix[0][3] == b) {
						return 10 * i + j;
							}
						}
				if (j == 7) {
					if (matrix[4][3] == b) {
						return 10 * i + j;
							}
						}
					}
			if( i == 4){
			    if (j == 1) {
					if (matrix[0][7] == b) {
						return 10 * i + j;
							}
						}
				if (j == 3) {
					if (matrix[3][7] == b) {
						return 10 * i + j;
							}
						}
				if (j == 5) {
					if (matrix[1][7] == b) {
						return 10 * i + j;
							}
						}
				if (j == 7) {
					if (matrix[5][7] == b) {
						return 10 * i + j;
							}
						}
					}
			if(i == 5){
				if (j == 1) {
					if (matrix[2][1] == b) {
						return 10 * i + j;
							}
						}
				if (j == 3) {
					if (matrix[1][5] == b) {
						return 10 * i + j;
							}
						}
				if (j == 5) {
					if (matrix[3][3] == b) {
						return 10 * i + j;
							}
						}
			    if (j == 7) {
					if (matrix[4][7] == b) {
						return 10 * i + j;
							}
						}
					}
				}
			}
		}
			return result = 0;	
}

/*@brief: hulpfunctie die een edgepiece naar beneden draait zonder de reeds gemaakt elementen van het wit kruis weer te verbreken
 *@param:  char matrix[6][9]: de matrix van de kubus
 *         int a: vlak van edgepiece-blok
 *	       int b: positie van edgepiece-blok in het vlak
 *@return void  */
void bringdownedge(int a, int b, char matrix[6][9]) {  											
	if (a == 0) { // wit
		if (b == 1) { BCW2(matrix); } 
		if (b == 3) { LCW2(matrix); }
		if (b == 5) { RCW2(matrix); }
		if (b == 7) { FCW2(matrix); }
	}
	if (a == 4) {//groen, 
		if (b == 3) { LCW(matrix); }
		if (b == 5) { RCCW(matrix); }
		if (b == 1) { FCW2(matrix);  }
	}
	if (a == 3) { //oranje
		if (b == 1) { BCW(matrix); }
		if (b == 5) { LCW2(matrix);  }
		if (b == 7) { LCW(matrix); }
	}
	if (a == 1) { // rood
		if (b == 3) { RCW2(matrix); }
		if (b == 1) { RCW(matrix); }
		if (b == 7) { RCCW(matrix); }
	}
	if (a == 2) { // blauw
		if (b == 3) { LCCW(matrix); }
		if (b == 5) { RCW(matrix); }
		if (b == 7) { BCW2(matrix); }
	   }
	}





// STAGE 2: cornerpieces oplossen zodat volledig wit vlak is opgelost

/*@brief: lost fase 2 op: het maken van een volledig wit kruis + de eerste laag aanliggend aan het witte vlak bevat de correcte kleuren
 * Dit gebeurt door de  4 cornerpieces op de juiste plaats in te schuiven
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void solve_corner_pieces(char matrix[6][9]) {
	int cp1; int cp2;
	/* eerst wit-blauw-rood cornerpiece inschuiven */
	cp1 = find_corner_piece('W', 'B', 'R', matrix); 
	if (cp1 / 10 != 0 && cp1 != 10 && cp1 != 16 && cp1 != 26 && cp1 != 28 && cp1 != 32 && cp1 != 38 && cp1 != 40 && cp1 != 42) { // indien cornerpiece vanboven zit
		wit_blauw_rood_inschuiven(cp1, matrix);
	}
	else { // blok zit vanboven, eruit draaien, terug positie zoeken, juist draaien en invoegen
		if (cp1 == 10 || cp1 == 28 || cp1 == 2) { RCW(matrix); DCW(matrix); RCCW(matrix); } // 10 en 28 zelfde blokje
		if (cp1 == 16 || cp1 == 42 || cp1 == 8) { RCCW(matrix); DCW(matrix); RCW(matrix); }
		if (cp1 == 26 || cp1 == 32 || cp1 == 0) { LCCW(matrix); DCW(matrix); LCW(matrix); }
		if (cp1 == 38 || cp1 == 40 || cp1 == 6) { LCW(matrix); DCW(matrix); LCCW(matrix); }
		cp1 = find_corner_piece('W', 'B', 'R', matrix); // terug positie zoeken
		wit_blauw_rood_inschuiven(cp1, matrix);
	}
	
	/* wit-blauw-oranje cornerpiece inschuiven */
	cp2 = find_corner_piece('W', 'B', 'O', matrix);
	if (cp2 / 10 != 0 && cp2 != 10 && cp2 != 16 && cp2 != 26 && cp2 != 28 && cp2 != 32 && cp2 != 38 && cp2 != 40 && cp2 != 42) { // // indien cornerpiece vanboven zit
		wit_blauw_oranje_inschuiven(cp2, matrix);
	}
	else { // blok zit vanboven, eruit draaien, terug positie zoeken, juist draaien en invoegen
		if (cp2 == 10 || cp2 == 28 || cp2 == 2) { RCW(matrix); DCW(matrix); RCCW(matrix); } // 10 en 28 zelfde blokje
		if (cp2 == 16 || cp2 == 42 || cp2 == 8) { RCCW(matrix); DCW(matrix); RCW(matrix); }
		if (cp2 == 26 || cp2 == 32 || cp2 == 0) { LCCW(matrix); DCW(matrix); LCW(matrix); }
		if (cp2 == 38 || cp2 == 40 || cp2 == 6) { LCW(matrix); DCW(matrix); LCCW(matrix); }
		cp2 = find_corner_piece('W', 'B', 'O', matrix); // terug positie zoeken
		wit_blauw_oranje_inschuiven(cp2, matrix);
	}

	/*  wit-groen-rood cornerpiece inschuiven */
	cp2 = find_corner_piece('W', 'G', 'R', matrix); // noem cp2 ipv cp3, moet ik minder aanpassen
	if (cp2 / 10 != 0 && cp2 != 10 && cp2 != 16 && cp2 != 26 && cp2 != 28 && cp2 != 32 && cp2 != 38 && cp2 != 40 && cp2 != 42) { // // indien cornerpiece vanboven zit 
		wit_groen_rood_inschuiven(cp2, matrix);
	}
	else { // blok zit vanboven, eruit draaien, terug positie zoeken, juist draaien en invoegen
		if (cp2 == 10 || cp2 == 28 || cp2 == 2) { RCW(matrix); DCW(matrix); RCCW(matrix); } // 10 en 28 zelfde blokje
		if (cp2 == 16 || cp2 == 42 || cp2 == 8) { RCCW(matrix); DCW(matrix); RCW(matrix); }
		if (cp2 == 26 || cp2 == 32 || cp2 == 0) { LCCW(matrix); DCW(matrix); LCW(matrix); }
		if (cp2 == 38 || cp2 == 40 || cp2 == 6) { LCW(matrix); DCW(matrix); LCCW(matrix); }
		cp2 = find_corner_piece('W', 'G', 'R', matrix); // terug positie zoeken
		wit_groen_rood_inschuiven(cp2, matrix);
	}
	
	/*  wit-groen-oranje cornerpiece inschuiven */
	cp2 = find_corner_piece('W', 'G', 'O', matrix);
	if (cp2 / 10 != 0 && cp2 != 10 && cp2 != 16 && cp2 != 26 && cp2 != 28 && cp2 != 32 && cp2 != 38 && cp2 != 40 && cp2 != 42) { // indien cornerpiece vanboven zit
		wit_groen_oranje_inschuiven(cp2, matrix);
	}
	else { // blok zit vanboven, eruit draaien, terug positie zoeken, juist draaien en invoegen
		if (cp2 == 10 || cp2 == 28 || cp2 == 2) { RCW(matrix); DCW(matrix); RCCW(matrix); } // 10 en 28 zelfde blokje
		if (cp2 == 16 || cp2 == 42 || cp2 == 8) { RCCW(matrix); DCW(matrix); RCW(matrix); }
		if (cp2 == 26 || cp2 == 32 || cp2 == 0) { LCCW(matrix); DCW(matrix); LCW(matrix); }
		if (cp2 == 38 || cp2 == 40 || cp2 == 6) { LCW(matrix); DCW(matrix); LCCW(matrix); }
		cp2 = find_corner_piece('W', 'G', 'O', matrix); // terug positie zoeken
		wit_groen_oranje_inschuiven(cp2, matrix);
	}
}

/*@brief: hulpfunctie die wit-blauw-rood in het witte vlak schuift op de gewenste plaats
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void wit_blauw_rood_inschuiven(int cp1,char matrix[6][9]) { 
	if (cp1 == 12 || cp1 == 22 || cp1 == 50) { // rechtsboven vanonder
		while (cp1 != 2 || matrix[0][2] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			BCCW(matrix); 
			DCCW(matrix);
			BCW(matrix); 
			DCW(matrix);
			cp1 = find_corner_piece('W', 'B', 'R', matrix);
		}
	}
	if (cp1 == 18 || cp1 == 48 || cp1 == 56) { // rechtsonder vanonder
		DCW(matrix);
		while (cp1 != 2 || matrix[0][2] != 'W') {  // moet 1x 2x of 3x gebeuren tot goed zit
			BCCW(matrix); 
			DCCW(matrix);
			BCW(matrix); 
			DCW(matrix);
			cp1 = find_corner_piece('W', 'B', 'R', matrix);
		}
	}
	if (cp1 == 36 || cp1 == 46 || cp1 == 58) { // linksonder vanonder
		DCW2(matrix); 
		while (cp1 != 2 || matrix[0][2] != 'W') {  // moet 1x 2x of 3x gebeuren tot goed zit
			BCCW(matrix); 
			DCCW(matrix);
			BCW(matrix); 
			DCW(matrix);
			cp1 = find_corner_piece('W', 'B', 'R', matrix);
		}
	}
	if (cp1 == 20 || cp1 == 30 || cp1 == 52) { // linksboven vanonder
		DCCW(matrix);
		while (cp1 != 2 || matrix[0][2] != 'W') {  // moet 1x 2x of 3x gebeuren tot goed zit
			BCCW(matrix); 
			DCCW(matrix);
			BCW(matrix); 
			DCW(matrix);
			cp1 = find_corner_piece('W', 'B', 'R', matrix);
		}
	}
}

/*@brief: hulpfunctie die wit-blauw-oranje in het witte vlak schuift op de gewenste plaats
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void wit_blauw_oranje_inschuiven(int cp2, char matrix[6][9]) {
	if (cp2 == 12 || cp2 == 22 || cp2 == 50) { // rechtsboven vanonder
		DCW(matrix);
		while ( cp2 != 0  || matrix[0][0] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			LCCW(matrix); 
			DCCW(matrix);
			LCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'B', 'O', matrix);
		}
	}
	if (cp2 == 18 || cp2 == 48 || cp2 == 56) { // rechtsonder vanonder
		DCW2(matrix); 
		while (cp2 != 0 || matrix[0][0] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			LCCW(matrix); 
			DCCW(matrix);
			LCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'B', 'O', matrix);
		}
	}
	if (cp2 == 36 || cp2 == 46 || cp2 == 58) { // linksonder vanonder
		DCCW(matrix);
		while (cp2 != 0 || matrix[0][0] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			LCCW(matrix); 
			DCCW(matrix);
			LCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'B', 'O', matrix);
		}
	}
	if (cp2 == 20 || cp2 == 30 || cp2 == 52) { // rechtsboven vanonder
		while (cp2 != 0 || matrix[0][0] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			LCCW(matrix); 
			DCCW(matrix);
			LCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'B', 'O', matrix);
		}
	}
}

/*@brief: hulpfunctie die wit-groen-oranje in het witte vlak schuift op de gewenste plaats
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void wit_groen_oranje_inschuiven(int cp2, char matrix[6][9]) {
	if (cp2 == 12 || cp2 == 22 || cp2 == 50) { // rechtsboven vanonder
		DCW2(matrix); 
		while (cp2 != 6 || matrix[0][6] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			FCCW(matrix); 
			DCCW(matrix);
			FCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'O', matrix);
		}
	}
	if (cp2 == 18 || cp2 == 48 || cp2 == 56) { // rechtsonder vanonder
		DCCW(matrix);
		while (cp2 != 6 || matrix[0][6] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			FCCW(matrix); 
			DCCW(matrix);
			FCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'O', matrix);
		}
	}
	if (cp2 == 36 || cp2 == 46 || cp2 == 58) { // linksonder vanonder
		while (cp2 != 6 || matrix[0][6] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			FCCW(matrix); 
			DCCW(matrix);
			FCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'O', matrix);
		}
	}
	if (cp2 == 20 || cp2 == 30 || cp2 == 52) { // rechtsboven 
		DCW(matrix);
		while (cp2 != 6 || matrix[0][6] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			FCCW(matrix); 
		    DCCW(matrix);
			FCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'O', matrix);
		}
	}
}

/*@brief: hulpfunctie die wit-groen-rood in het witte vlak schuift op de gewenste plaats
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void wit_groen_rood_inschuiven(int cp2, char matrix[6][9]) {
	if (cp2 == 12 || cp2 == 22 || cp2 == 50) { // rechtsboven vanonder
		DCCW(matrix); 
		while (cp2 != 8 || matrix[0][8] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			RCCW(matrix); 
			DCCW(matrix);
			RCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'R', matrix);
		}
	}
	if (cp2 == 18 || cp2 == 48 || cp2 == 56) { // rechtsonder vanonder
		while (cp2 != 8 || matrix[0][8] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			RCCW(matrix); 
			DCCW(matrix);
			RCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'R', matrix);
		}
	}
	if (cp2 == 36 || cp2 == 46 || cp2 == 58) { // linksonder vanonder
		DCW(matrix);
		while (cp2 != 8 || matrix[0][8] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			RCCW(matrix); 
			DCCW(matrix);
			RCW(matrix); 
			DCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'R', matrix);
		}
	}
	if (cp2 == 20 || cp2 == 30 || cp2 == 52) { // rechtsboven 
		DCW2(matrix);
		while (cp2 != 8 || matrix[0][8] != 'W') { // moet 1x 2x of 3x gebeuren tot goed zit
			RCCW(matrix); 
			DCCW(matrix);
			RCW(matrix); 
			UCW(matrix);
			cp2 = find_corner_piece('W', 'G', 'R', matrix);
		}
	}
}





// STAGE 3: middelste laag oplossen naar de juiste kleur

/*@brief: lost fase 3 op:  de middelste laag van de matrix oplossen naar de juiste kleur
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@bug: functie draai_links gebeurt 2x na elkaar: kan in een functie geschreven worden voor minder mechanische bewegingen
 *@bug: deze functie kan nog geoptimaliseerd worden!
 *@return void  */
void solve_middle_layer(char matrix[6][9]) {
	int controle = 0;
	draai_links(matrix); draai_links(matrix); // zie dat vlak geel naar boven komt te staan
	while (controle == 0) {
		while (midden_test(matrix) == 1) {
		 midden_indraaien(matrix);
	}
		UCW(matrix);
		if (find_good_edge_piece(matrix) == 0) { // alle edge pieces hebben een gele: er zit dus ergens een blok fout
			if (matrix[1][1] == matrix[2][4]) { draai_voor_naar_links(matrix); recht_midden_plaatsen(matrix); draai_voor_naar_rechts(matrix); goto tussen; }
			if (matrix[1][7] == matrix[4][4]) { recht_midden_plaatsen(matrix); goto tussen; }
			if (matrix[2][3] == matrix[3][4]) { draai_voor_naar_rechts(matrix);  links_midden_plaatsen(matrix); draai_voor_naar_links(matrix); goto tussen; }
			if (matrix[2][5] == matrix[1][4]) { draai_voor_naar_links(matrix); draai_voor_naar_links(matrix); links_midden_plaatsen(matrix); draai_voor_naar_rechts(matrix);
			draai_voor_naar_rechts(matrix); goto tussen;
			}
			if (matrix[4][3] == matrix[3][4]) { links_midden_plaatsen(matrix); goto tussen; }
			if (matrix[1][7] == matrix[4][4]) { draai_voor_naar_links(matrix); links_midden_plaatsen(matrix); draai_voor_naar_rechts(matrix); goto tussen; }
		tussen:
			;
		}
		// controleer of middelste laag ok is
		if ( matrix[1][1] == 'O' && matrix[1][7] == 'O' && matrix[2][3] == 'B' && matrix[2][5] == 'B' && matrix[3][1] == 'R' && matrix[3][7] == 'R' && matrix[4][3] == 'G' && matrix[4][5] == 'G') { // alles zit goed ALS GEEL VANBOVEN ZIT EN GROEN VANVOOR!!!!!!!!
			controle = 1;
		}
	}
	

}

/*@brief: hulpfunctie die kleur op juiste positie  in middelste laag plaatst
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@bug: optimalisatie: functie voor_naar_links X 2 schrijven 
 *@return void  */
void midden_indraaien(char matrix[6][9]) {
start : 
	;
	if (matrix[1][3] == 'O') { // oranje verticale lijn (T-vorm)
		if (matrix[0][5] == 'B') { // rechts in midden plaatsen
			draai_voor_naar_links(matrix);
			recht_midden_plaatsen(matrix);
			draai_voor_naar_rechts(matrix);
			goto next;
		}
		if (matrix[0][5] == 'G') {
			draai_voor_naar_links(matrix);
			links_midden_plaatsen(matrix);
			draai_voor_naar_rechts(matrix);
			goto next;
		}
	}
	if (matrix[2][7] == 'B') { 
		if (matrix[0][1] == 'R') { // rechts in midden plaatsen 
			draai_voor_naar_links(matrix); draai_voor_naar_links(matrix);
			recht_midden_plaatsen(matrix);
			draai_voor_naar_links(matrix); draai_voor_naar_links(matrix);
			goto next;
		}
		if (matrix[0][1] == 'O') {
			draai_voor_naar_links(matrix); draai_voor_naar_links(matrix);
			links_midden_plaatsen(matrix);
			draai_voor_naar_links(matrix); draai_voor_naar_links(matrix);
			goto next;
		}
	}
	if (matrix[3][5] == 'R') {
		if (matrix[0][3] == 'G') { // rechts in midden plaatsen 
			draai_voor_naar_rechts(matrix); 
			recht_midden_plaatsen(matrix);
			draai_voor_naar_links(matrix);
			goto next;
		}
		if (matrix[0][3] == 'B') {
			draai_voor_naar_rechts(matrix); 
			links_midden_plaatsen(matrix);
			draai_voor_naar_links(matrix);
			goto next;
		}
	}
	if (matrix[4][1] == 'G') {
		if (matrix[0][7] == 'O') { // rechts in midden plaatsen 
			recht_midden_plaatsen(matrix); goto next;
		}
		if (matrix[0][7] == 'R') {
			links_midden_plaatsen(matrix); goto next;

		}
	}
	if (find_good_edge_piece(matrix) == 0) { // alle edge pieces hebben een gele: er zit dus ergens een blok fout
		if (matrix[1][1] == matrix[2][4]) { draai_voor_naar_links(matrix); recht_midden_plaatsen(matrix); goto tussen; }
		if (matrix[1][7] == matrix[4][4]) { recht_midden_plaatsen(matrix); goto tussen; }
		if (matrix[2][3] == matrix[3][4]) { draai_voor_naar_rechts(matrix);  links_midden_plaatsen(matrix); goto tussen; }
		if (matrix[2][5] == matrix[1][4]) { draai_voor_naar_links(matrix); draai_voor_naar_links(matrix); links_midden_plaatsen(matrix); goto tussen; }
		if (matrix[4][3] == matrix[3][4]) { links_midden_plaatsen(matrix); goto tussen; }
		if (matrix[1][7] == matrix[4][4]) { draai_voor_naar_links(matrix); links_midden_plaatsen(matrix); goto tussen; }
	tussen:
		;
	}
	UCW(matrix);
	goto start;
next:;

}

/*@brief: hulpfunctie die kijkt of er nog bruikbare edge-pieces zijn
*@param:  char matrix[6][9]: de matrix van de kubus
*@return int: 1 als er bruikbare gevonden is,0 indien niet  */
int find_good_edge_piece(char matrix[6][9]) {
	if (matrix[0][1] != 'Y') {
		if (matrix[2][7] != 'Y') { return 1; }
	}
	if (matrix[0][3] != 'Y') {
		if (matrix[3][5] != 'Y') { return 1; }
	}
	if (matrix[0][5] != 'Y') {
		if (matrix[1][3] != 'Y') { return 1; }
	}
	if (matrix[0][7] != 'Y') {
		if (matrix[4][1] != 'Y') { return 1; }
	}
	return 0;
}
/*@brief: hulpfunctie die kleur rechts van center-piece in middelste laag plaatst
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void recht_midden_plaatsen(char matrix[6][9]) {
	UCW(matrix);
	RCW(matrix);
	UCCW(matrix);
	RCCW(matrix);
	UCCW(matrix);
	FCCW(matrix);
	UCW(matrix);
	FCW(matrix);
}

/*@brief: hulpfunctie die kleur links van center-piece in middelste laag plaatst
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void links_midden_plaatsen(char matrix[6][9]) {
	UCCW(matrix);
	LCCW(matrix);
	UCW(matrix);
	LCW(matrix);
	UCW(matrix);
	FCW(matrix);
	UCCW(matrix);
	FCCW(matrix);
}

/*@brief: hulpfunctie die test of de middelste laag in orde is
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return int: 0 als het in orde is, 1 als het nog niet in orde is  */
int midden_test(char matrix[6][9]) {
	if (((matrix[2][7] == 'B' && (matrix[0][1] == 'R' || matrix[0][1] == 'O')))) { return 1; }
	if (((matrix[1][3] == 'O' && (matrix[0][5] == 'B' || matrix[0][5] == 'G')))) { return 1; }
	if (((matrix[3][5] == 'R' && (matrix[0][3] == 'G' || matrix[0][3] == 'B')))) { return 1; }
	if (((matrix[4][1] == 'G' && (matrix[0][7] == 'O' || matrix[0][7] == 'R')))) { return 1; }
	return 0;
}




// STAGE 4: geel kruis maken

/*@brief: lost fase 4 op: maakt een geel kruis
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void maak_geel_kruis(char matrix[6][9]) {
	int a = maak_geel_tussenstap(matrix);
	if (a != 0) {
		omsingelde_hoek(matrix); // indien geen enkel geval -> omsingelde hoek rotaties doen en functie opnieuw oproepen
		maak_geel_tussenstap(matrix);
	}
}

/*@brief: hulpfunctie die correcte bewegingen doet bij 4 states van het gele vlak
* er zijn 4 states: een reeds opgelost geel kruis, dan is deze fase reeds correct
*                   een horizontale gele lijn
*                   een hoek opsingeld met gele kleuren
*@param:  char matrix[6][9]: de matrix van de kubus
*@bug : potentiele bug in het controleren van de gele blokken
*@return int: 0 indien het opgelost is, 1 indien niet  */
int maak_geel_tussenstap(char matrix[6][9]) {
	// 4 states

	// state 1: opgelost geel kruis
	if (matrix[0][1] == 'Y' && matrix[0][3] == 'Y' && matrix[0][5] == 'Y' && matrix[0][7] == 'Y') {
		return 0;
	}
	// state 2: 'omsingelde hoek'
	// @bug potentiele bug 
	if (matrix[0][1] == 'Y' && matrix[0][3] == 'Y' && matrix[0][4] == 'Y' && matrix[0][5] != 'Y') {
		omsingelde_hoek(matrix);
		return 0;
	}
	if (matrix[0][1] == 'Y' && matrix[0][5] == 'Y' && matrix[0][4] == 'Y' && matrix[0][3] != 'Y') {
		UCCW(matrix);
		omsingelde_hoek(matrix);
		return 0;
	}
	if (matrix[0][7] == 'Y' && matrix[0][5] == 'Y' && matrix[0][4] == 'Y' && matrix[0][3] != 'Y') {
		UCW2(matrix);
		omsingelde_hoek(matrix);
		return 0;
	}
	if (matrix[0][7] == 'Y' && matrix[0][3] == 'Y' && matrix[0][4] == 'Y' && matrix[0][5] != 'Y') {
		UCW(matrix);
		omsingelde_hoek(matrix);
		return 0;
	}
	// state 3: horizontale lijn
	if (matrix[0][3] == 'Y' && matrix[0][3] == 'Y' && matrix[0][5] == 'Y') {
		horizontale_lijn(matrix);
		return 0;
	}
	if (matrix[0][1] == 'Y' && matrix[0][7] == 'Y' && matrix[0][4] == 'Y') {
		UCW(matrix);
		horizontale_lijn(matrix);
		return 0;
	}
	return 1;
}

/*@brief: hulpfunctie die correcte beweging doet voor horizontale lijn
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void horizontale_lijn(char matrix[6][9]) {
	FCW(matrix);
	RCW(matrix);
	UCW(matrix);
	RCCW(matrix);
	UCCW(matrix);
	FCCW(matrix);
}

/*@brief: hulpfunctie die correcte beweging doet voor een omsingelde hoek
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void omsingelde_hoek(char matrix[6][9]) {
	FCW(matrix);
	UCW(matrix);
	RCW(matrix);
	UCCW(matrix);
	RCCW(matrix);
	FCCW(matrix);

}





// STAGE 5: geel vlak maken

/*@brief: lost fase 5 op: maak een geel vlak
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void maak_geel_vlak(char matrix[6][9]) {
	// 3 states:
start:
	// state 1: 
	if (matrix[0][0] != 'Y' && matrix[0][2] != 'Y' && matrix[0][6] != 'Y' && matrix[0][8] != 'Y') { // geen extra geel buiten het gele kruis
		if (matrix[3][8] == 'Y') {
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[2][6] == 'Y') {
			UCCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[1][0] == 'Y') {
			UCW2(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[4][2] == 'Y') {
			UCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
	}
		// state 2: 1 corner is geel
		if (matrix[0][6] == 'Y' && matrix[0][2] != 'Y' && matrix[0][0] != 'Y' && matrix[0][8] != 'Y') { // linksonder is geel, REST IS NIET GEEL
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[0][0] == 'Y' && matrix[0][2] != 'Y' && matrix[0][6] != 'Y' && matrix[0][8] != 'Y') {
			UCCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[0][2] == 'Y' && matrix[0][0] != 'Y' && matrix[0][6] != 'Y' && matrix[0][8] != 'Y') {
			UCW2(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[0][8] == 'Y' && matrix[0][2] != 'Y' && matrix[0][6] != 'Y' && matrix[0][0] != 'Y') {
			UCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;

		}
		// state 3: er zitten 2 of meer gele corner pieces goed
		if (matrix[4][0] == 'Y') {
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[1][6] == 'Y') {
			UCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[2][8] == 'Y') {
			UCW2(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
		if (matrix[3][2] == 'Y') {
			UCCW(matrix);
			geel_vlak_beweging(matrix);
			if (matrix[0][0] == 'Y' && matrix[0][2] == 'Y' && matrix[0][6] == 'Y' && matrix[0][8] == 'Y') { // volledig wit vlak, zet check op 1, vlak is opgelost
				goto end;
			}
			goto start;
		}
	end:
		;
	}

/*@brief: hulpfunctie met de correcte beweging voor het maken van een geel vlak
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void geel_vlak_beweging(char matrix[6][9]) {
	RCW(matrix);
	UCW(matrix);
	RCCW(matrix);
	UCW(matrix);
	RCW(matrix);
	UCW2(matrix);
	RCCW(matrix);
}





// STAGE 6: oplossen van de volledige kubus door de laatste blokken correct te plaatsen

/*@brief: hulpfunctie die de hoeken correct plaatst met de aanliggende vlakken
 * bestaat uit 2 states : alle hoekkleuren liggen goed en slechts 2 kleuren liggen juist
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@bug draai-boven 2 X
 *@return void  */
void yellow_corner_correct(char matrix[6][9]) { 
	// kubus ligt met gele vlak vanboven en groene vlak vanvoor
	//eerste: controleren of de twee achterste hoekstukken op de juiste plek zitten
	//als dit niet zo is, staan er twee diagonaal wel juist (dus ofwel links-voor en rechts-achter, of rechts-voor en links-achter)
	// het zit goed:
	start:
	//state 1: alle hoekkleuren liggen goed
	
	if (matrix[3][2] == matrix[3][8] && matrix[2][6] == matrix[2][8] && matrix[1][0] == matrix[1][6] && matrix[4][0] == matrix[4][2]) { 
		// zet een kleur bij juiste vlak, dan staan ze allemaal correct
		if (matrix[1][3] != matrix[1][4]) {
			if (matrix[1][3] == matrix[2][4]) { UCCW(matrix); }
			if (matrix[1][3] == matrix[3][4]) { UCW2(matrix); }
			if (matrix[1][3] == matrix[4][4]) { UCW(matrix); }
		}
		goto end; // naar einde functie gaan
	}
	// 2 kleuren gelijk: dit vlak naar achter draaien en da voorste kleuren juist maken
	if (matrix[3][2] == matrix[3][8] ) { 
		if (matrix[3][2] == matrix[1][4]) {
			UCW2(matrix);
			draai_voor_naar_rechts(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[3][2] == matrix[2][4]) {
			UCW(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[3][2] == matrix[3][4]) {
			draai_voor_naar_links(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[3][2] == matrix[4][4]) {
			UCCW(matrix);
			draai_voor_naar_rechts(matrix); draai_voor_naar_rechts(matrix); // kan verbeterd worden
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
	}
	if (matrix[4][0] == matrix[4][2] ) { 
		if (matrix[4][0] == matrix[1][4]) {
			UCCW(matrix);
			draai_voor_naar_rechts(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[4][0] == matrix[2][4]) {
			UCW2(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[4][0] == matrix[3][4]) {
			UCW(matrix);
			draai_voor_naar_links(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[4][0] == matrix[4][4]) {
			draai_voor_naar_rechts(matrix); draai_voor_naar_rechts(matrix); // kan verbeterd worden
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
	}
	if (matrix[1][0] == matrix[1][6] ) {
			if (matrix[1][0] == matrix[1][4]) {
				draai_voor_naar_rechts(matrix);
				verwissel_edgepieces_vooraan(matrix); goto end;
			}
			if (matrix[1][0] == matrix[2][4]) {
				UCCW(matrix);
				verwissel_edgepieces_vooraan(matrix); goto end;
			}
			if (matrix[1][0] == matrix[3][4]) {
				UCW2(matrix);
				draai_voor_naar_links(matrix);
				verwissel_edgepieces_vooraan(matrix); goto end;
			}
			if (matrix[1][0] == matrix[4][4]) {
				UCW(matrix);
				draai_voor_naar_rechts(matrix); draai_voor_naar_rechts(matrix); // kan verbeterd worden
				verwissel_edgepieces_vooraan(matrix); goto end;
			}
		}
	if (matrix[2][6] == matrix[2][8] ) {
		if (matrix[2][6] == matrix[1][4]) {
			UCW(matrix);
			draai_voor_naar_rechts(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[2][6] == matrix[2][4]) {
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[2][6] == matrix[3][4]) {
			UCCW(matrix);
			draai_voor_naar_links(matrix);
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
		if (matrix[2][6] == matrix[4][4]) {
			UCW2(matrix);
			draai_voor_naar_rechts(matrix); draai_voor_naar_rechts(matrix); // kan verbeterd worden
			verwissel_edgepieces_vooraan(matrix); goto end;
		}
	}
	verwissel_edgepieces_vooraan(matrix); goto start; // niet

end:
	;
}

/*@brief: hulpfunctie die de hoeken vooraan aanpast
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void verwissel_edgepieces_vooraan(char matrix[6][9]) {
	RCCW(matrix);
	FCW(matrix);
	RCCW(matrix);
	BCW2(matrix);
	RCW(matrix);
	FCCW(matrix);
	RCCW(matrix);
	BCW2(matrix);
	RCW2(matrix);
	UCCW(matrix);
}

/*@brief: functie die de laatste stap oplost
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void ( geeft volledig opgeloste kubus ) */
void get_endstate(char matrix[6][9]) {
	// zorg ervoor dat kubus start in positie: geel vlak vanboven, groen vlak vanvoor
	if (matrix[1][4] == 'G') { draai_voor_naar_links(matrix); }
	if (matrix[2][4] == 'G') { draai_voor_naar_links(matrix); draai_voor_naar_links(matrix); }
	if (matrix[3][4] == 'G') { draai_voor_naar_rechts(matrix); }

	
	// kubus start met geel vlak vanboven
start:
	
	if (matrix[1][0] == matrix[1][3] && matrix[2][6] == matrix[2][7] && matrix[3][2] == matrix[3][5] && matrix[4][0] == matrix[4][1]) { goto end; } // opgelost
	if (matrix[1][0] == matrix[1][3] || matrix[2][6] == matrix[2][7] || matrix[3][2] == matrix[3][5] || matrix[4][0] == matrix[4][1]) {// er zitten 3 blokken niet juist
		if (matrix[1][0] == matrix[1][3] && matrix[1][0] == matrix[1][6]) {
			if (matrix[1][3] == 'O') { // oranje is ok
				draai_voor_naar_rechts(matrix);  // zet oranje vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[1][3] == 'G') { // groen
				UCW(matrix);
				draai_voor_naar_links(matrix);  draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[1][3] == 'R') { // rood
				UCW2(matrix);
				draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[1][3] == 'B') { // blauw
				UCCW(matrix);
				// blauw staat reeds vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
		}
		if (matrix[2][6] == matrix[2][7] && matrix[2][6] == matrix[2][8]) {
			if (matrix[2][7] == 'O') { // oranje is ok
				UCW(matrix);
				draai_voor_naar_rechts(matrix);  // zet oranje vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[2][7] == 'G') { // groen
				UCW2(matrix);
				draai_voor_naar_links(matrix);  draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[2][7] == 'R') { // rood
				UCCW(matrix);
				draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[2][7] == 'B') { // blauw
				// blauw staat reeds vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
		}

		if (matrix[3][2] == matrix[3][5] && matrix[3][2] == matrix[3][8]) {
			if (matrix[3][5] == 'O') { // oranje is ok
				UCW2(matrix);
				draai_voor_naar_rechts(matrix);  // zet oranje vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[3][5] == 'G') { // groen
				UCCW(matrix);
				draai_voor_naar_links(matrix);  draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[3][5] == 'R') { // rood
				draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[3][5] == 'B') { // blauw
				UCW(matrix);
				// blauw staat reeds vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
		}
		if (matrix[4][0] == matrix[4][1] && matrix[4][0] == matrix[4][2]) {
			if (matrix[4][1] == 'O') { // oranje is ok
				UCCW(matrix);
				draai_voor_naar_rechts(matrix);  // zet oranje vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[4][1] == 'G') { // groen
				draai_voor_naar_links(matrix);  draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[4][1] == 'R') { // rood
				UCW(matrix);
				draai_voor_naar_links(matrix);  // zet groen vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
			if (matrix[4][1] == 'B') { // blauw
				UCW2(matrix);
				// blauw staat reeds vanachter
				if (matrix[3][5] == matrix[1][4]) { // clockwise doordraaien
					yellow_edges_clockwise(matrix); goto end;
				}
				else {
					yellow_edges_counter_clockwise(matrix); goto end;
				}
			}
		}
	}
	yellow_edges_clockwise(matrix);
	goto start;
end:
	;
}

/*@brief: hulpfunctie die de edgepieces clockwise doorschuift van vlak
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void yellow_edges_clockwise(char matrix[6][9]) {
	FCW2(matrix);
	UCW(matrix);
	LCW(matrix);
	RCCW(matrix);
	FCW2(matrix);
	LCCW(matrix);
	RCW(matrix);
	UCW(matrix);
	FCW2(matrix);
}

/*@brief: hulpfunctie die de edgepieces counter-clockwise doorschuift van vlak
 *@param:  char matrix[6][9]: de matrix van de kubus
 *@return void  */
void yellow_edges_counter_clockwise(char matrix[6][9]) {
	FCW2(matrix);
	UCCW(matrix);
	LCW(matrix);
	RCCW(matrix);
	FCW2(matrix);
	LCCW(matrix);
	RCW(matrix);
	UCCW(matrix);
	FCW2(matrix);
}

/*@brief: hulpfunctie die de cornerpiece vindt
 *@param:  char matrix[6][9]: de matrix van de kubus
          char a: kleur 
		  char b: kleur
		  char c: kleur
 *@return int: geeft positie terug van kleur a op dezelfde manier als find_edge_piece  */
int find_corner_piece(char a, char b, char c, char matrix[6][9]) {
    int i; int j;
    for(i = 0; i < 6; i++) {
		for (j = 0; j < 9; j += 2) { // 4 en 6 iteratie zijn overbodig: corners zijn enkel 0 2 6 8 
			if (matrix[i][j] == 'W' && j!=4) {

				if (i == 0) { // wit ligt in vlak 0
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[2][6] == b && matrix[3][2] == c) || (matrix[2][6] == c && matrix[3][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[2][8] == b && matrix[1][0] == c) || (matrix[2][8] == c && matrix[1][0] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[3][8] == b && matrix[4][0] == c) || (matrix[3][8] == c && matrix[4][0] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[1][6] == b && matrix[4][2] == c) || (matrix[1][6] == c && matrix[4][2] == b)) {
							return i * 10 + j;
						}
					}
				}

				if (i == 1) { // wit ligt in vlak 1
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[0][2] == b && matrix[2][8] == c) || (matrix[0][2] == c && matrix[2][8] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[2][2] == b && matrix[5][0] == c) || (matrix[2][2] == c && matrix[5][0] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[0][8] == b && matrix[4][2] == c) || (matrix[0][8] == c && matrix[4][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[4][8] == b && matrix[5][6] == c) || (matrix[4][8] == c && matrix[5][6] == b)) {
							return i * 10 + j;
						}
					}
				}
				if (i == 2) { // wit ligt in vlak 1
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[3][0] == b && matrix[5][2] == c) || (matrix[3][0] == c && matrix[5][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[1][2] == b && matrix[5][0] == c) || (matrix[1][2] == c && matrix[5][0] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[0][0] == b && matrix[3][2] == c) || (matrix[0][0] == c && matrix[3][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[0][2] == b && matrix[1][0] == c) || (matrix[0][2] == c && matrix[1][0] == b)) {
							return i * 10 + j;
						}
					}
				}
				if (i == 3) { // wit ligt in vlak 1
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[2][0] == b && matrix[5][2] == c) || (matrix[2][0] == c && matrix[5][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[0][0] == b && matrix[2][6] == c) || (matrix[0][0] == c && matrix[2][6] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[4][6] == b && matrix[5][8] == c) || (matrix[4][6] == c && matrix[5][8] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[0][6] == b && matrix[4][0] == c) || (matrix[0][6] == c && matrix[4][0] == b)) {
							return i * 10 + j;
						}
					}
				}
				if (i == 4) { // wit ligt in vlak 1
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[0][6] == b && matrix[3][8] == c) || (matrix[0][6] == c && matrix[3][8] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[0][8] == b && matrix[1][6] == c) || (matrix[0][8] == c && matrix[1][6] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[3][6] == b && matrix[5][8] == c) || (matrix[3][6] == c && matrix[5][8] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[1][8] == b && matrix[5][6] == c) || (matrix[1][8] == c && matrix[5][6] == b)) {
							return i * 10 + j;
						}
					}
				}
				if (i == 5) { // wit ligt in vlak 1
					if (j == 0) { // wit ligt op positie 0 in vlak 1
						if ((matrix[1][2] == b && matrix[2][2] == c) || (matrix[1][2] == c && matrix[2][2] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 2) { // op positie 2
						if ((matrix[2][0] == b && matrix[3][0] == c) || (matrix[2][0] == c && matrix[3][0] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 6) {
						if ((matrix[1][8] == b && matrix[4][8] == c) || (matrix[1][8] == c && matrix[4][8] == b)) {
							return i * 10 + j;
						}
					}
					if (j == 8) {
						if ((matrix[3][6] == b && matrix[4][6] == c) || (matrix[3][6] == c && matrix[4][6] == b)) {
							return i * 10 + j;
						}
					}
				}
			}
		}
	}
}