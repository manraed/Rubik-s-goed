#include "bewegingen.h"
#include "servo.h"
#include <stdio.h>
#include "dwengoDelay.h"

/* @brief: draait de elementen van het opgegeven vlak in wijzerzin.
 * Dit is een onmogelijke actie met de kubus (enkel bedoeld om de matrix aan te passen)
 * @param:  int vlak: het nummer van het vlak
 *          char matrix[6][9]: de matrix van de kubus
 * @return: void*/
int i;

void draai_wijzerzin(int vlak, char matrix[6][9]) { 
	char temp[9];
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[vlak][i];
	}
	matrix[vlak][0] = temp[6];
	matrix[vlak][1] = temp[3];
	matrix[vlak][2] = temp[0];
	matrix[vlak][3] = temp[7];
	matrix[vlak][4] = temp[4];
	matrix[vlak][5] = temp[1];
	matrix[vlak][6] = temp[8];
	matrix[vlak][7] = temp[5];
	matrix[vlak][8] = temp[2];
}

/* @brief: draait de elementen van het opgegeven vlak in tegenwijzerzin.
 * Dit is een onmogelijke actie met de kubus (enkel bedoeld om de matrix aan te passen)
 * @param:  int vlak: het nummer van het vlak
 *          char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_tegenwijzerzin(int vlak, char matrix[6][9]) {
	char temp[9];
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[vlak][i];
	}
	matrix[vlak][0] = temp[2];
	matrix[vlak][1] = temp[5];
	matrix[vlak][2] = temp[8];
	matrix[vlak][3] = temp[1];
	matrix[vlak][4] = temp[4];
	matrix[vlak][5] = temp[7];
	matrix[vlak][6] = temp[0];
	matrix[vlak][7] = temp[3];
	matrix[vlak][8] = temp[6];
}

/* @brief: draait de elementen van het opgegeven vlak tweemaal.
 * Dit is een onmogelijke actie met de kubus (enkel bedoeld om de matrix aan te passen)
 * @param:  int vlak: het nummer van het vlak
 *          char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_dubbel(int vlak, char matrix[6][9]) { 
	char temp[9];
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[vlak][i];
	}
	matrix[vlak][0] = temp[8];
	matrix[vlak][1] = temp[7];
	matrix[vlak][2] = temp[6];
	matrix[vlak][3] = temp[5];
	matrix[vlak][4] = temp[4];
	matrix[vlak][5] = temp[3];
	matrix[vlak][6] = temp[2];
	matrix[vlak][7] = temp[1];
	matrix[vlak][8] = temp[0];
}

/* @brief: draait de voorkant van de kubus naar de rechterkant en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_voor_naar_rechts(char matrix[6][9]){
        draai_boven(matrix[6][9]);
        draai_rechts(matrix[6][9]);
        draai_onder(matrix[6][9]);
}

/* @brief: draait de voorkant van de kubus naar de linkerkant en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_voor_naar_links(char matrix[6][9]) {
    draai_boven(matrix[6][9]);
    draai_links(matrix[6][9]);
    draai_onder(matrix[6][9]);
}

/* @brief: draait de voorkant van de kubus naar de achterkant en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_voor_naar_achter(char matrix[6][9]) {
    draai_boven(matrix[6][9]);
    draai_boven(matrix[6][9]);
    draai_links(matrix[6][9]);
    draai_links(matrix[6][9]);
}

/* @brief: draait de bovenkant van de kubus naar de voorkant (naar onder toe wanneer je ervoor staat).
 *          en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_onder(char matrix[6][9]) {
    char temp[9];
    int pos = 8;
    /*DC2 openen
    Servo2 draaien in tegenwijzerzin en servo4 tegelijk in wijzerzin
    DC2 sluiten
    DC1 openen
    Servo2 en 4 terugzetten
    DC1 sluiten*/
    motor1open();
    delay_ms(500);
    servo2(90);
    delay_ms(500);
    motor1toe();
    delay_ms(500);
    motor2open();
    delay_ms(500);
    servo2(0);
    servo4(90);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    motor1open();
    delay_ms(500);
    servo4(0);
    delay_ms(500);
    motor1toe();
    delay_ms(500);

    /*matrix aanpassen*/
    for (i = 0; i < 9; i++) {
	temp[i] = matrix[4][i];
	matrix[4][i] = matrix[0][i];
	matrix[0][i] = matrix[2][i];
    }
    for (i = 0; i < 9; i++) {
	matrix[2][i] = matrix[5][pos];
	pos--;
    }
    pos = 8;
    for (i = 0; i < 9; i++) {
	matrix[5][i] = temp[pos];
	pos--;
    }
    draai_wijzerzin(3, matrix);
    draai_tegenwijzerzin(1, matrix);
}

/* @brief: draait de bovenkant van de kubus naar de achterkant (naar boven toe wanneer je ervoor staat)
 *          en past de matrix aan
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_boven(char matrix[6][9]) {
	char temp[9];
        int pos = 8;
	/*DC2 openen
	Servo2 draaien in wijzerzin en servo4 tegelijk in tegenwijzerzin
        DC2 sluiten
        DC1 openen
	Servo2 en 4 terugzetten
        DC1 sluiten*/
        motor1open();
        delay_ms(500);
        servo2(-90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        motor2open();
        delay_ms(500);
        servo2(0);
        servo4(-90);
        delay_ms(500);
        motor2toe();
        delay_ms(500);
        motor1open();
        delay_ms(500);
        servo4(0);
        delay_ms(500);
        motor1toe();
        delay_ms(500);

	/*matrix aanpassen*/
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[2][i];
		matrix[2][i] = matrix[0][i];
		matrix[0][i] = matrix[4][i];
	}
	for (i = 0; i < 9; i++) {
		matrix[4][i] = matrix[5][pos];
		pos--;
	}
	pos = 8;
	for (i = 0; i < 9; i++) {
		matrix[5][i] = temp[pos];
		pos--;
	}
	draai_wijzerzin(1, matrix);
	draai_tegenwijzerzin(3, matrix);
}

/* @brief: draait de bovenkant van de kubus naar de rechterkant en past de matrix aan
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_rechts(char matrix[6][9]) {
	char temp[9];
	/*DC1 open
	ServoA 90° wijzerzin draaien en servoC 90° tegenwijzerzin
	DC1 sluiten
	DC2 openen
	ServoA en servoC terugzetten
	DC2 sluiten*/
        motor1open();
        delay_ms(500);
        servo1(90);
        servo3(-90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        motor2open();
        delay_ms(500);
        servo1(0);
        servo3(0);
        delay_ms(500);
        motor2toe();
        delay_ms(500);

	/*matrix aanpassen*/
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[0][i];
		matrix[0][i] = matrix[3][i];
		matrix[3][i] = matrix[5][i];
		matrix[5][i] = matrix[1][i];
		matrix[1][i] = temp[i];
	}
	draai_wijzerzin(4, matrix);
	draai_tegenwijzerzin(2, matrix);
}

/* @brief: draait de bovenkant van de kubus naar de linkerkant en past de matrix aan
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void draai_links(char matrix[6][9]) {
	char temp[9];
       /*DC1 openen
	ServoA 90° tegenwijzerzin en servoC 90° wijzerzin draaien
	DC1 sluiten
	DC2 openen
	ServoA en C terugzetten
	DC2 sluiten*/
        motor1open();
        delay_ms(500);
        servo1(-90);
        servo3(90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        motor2open();
        delay_ms(500);
        servo1(0); servo3(0);
        delay_ms(500);
        motor2toe();
        delay_ms(500);
	
	/*matrix aanpassen*/
	for (i = 0; i < 9; i++) {
		temp[i] = matrix[1][i];
		matrix[1][i] = matrix[5][i];
		matrix[5][i] = matrix[3][i];
		matrix[3][i] = matrix[0][i];
		matrix[0][i] = temp[i];
	}
	draai_wijzerzin(2, matrix);
	draai_tegenwijzerzin(4, matrix);
}

/* @brief: (Right ClockWise) draait het rechtervlak van de kubus in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void RCW(char matrix[6][9]) {
	char temp[3];
	/*DC1 openen
	ServoB 90° draaien in tegenwijzerzin
        DC1 sluiten 
        ServoB terugzetten*/
        motor1open();
        delay_ms(500);
        servo2(-90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        servo2(10);
        delay_ms(500);

	/*matrix aanpassen*/
	temp[0] = matrix[5][6];
	temp[1] = matrix[5][3];
	temp[2] = matrix[5][0];
	matrix[5][0] = matrix[2][8];
	matrix[5][3] = matrix[2][5];
	matrix[5][6] = matrix[2][2];
	for (i = 0; i < 3; i++) {
		matrix[2][2 + 3 * i] = matrix[0][2 + 3 * i];
		matrix[0][2 + 3 * i] = matrix[4][2 + 3 * i];
		matrix[4][2 + 3 * i] = temp[i];
	}
	draai_wijzerzin(1, matrix);
}

/* @brief: (Right CounterClockWise) draait het rechtervlak van de kubus in tegenwijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void RCCW(char matrix[6][9]) {
	char temp[3];
	/*DC1 openen
        ServoB 90° draaien in wijzerzin
        DC1 sluiten
        ServoB terugzetten*/
        motor1open();
        delay_ms(500);
        servo2(90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        servo2(0);
        delay_ms(500);
        
	/*matrix aanpassen*/
	temp[0] = matrix[5][6];
	temp[1] = matrix[5][3];
	temp[2] = matrix[5][0];
	matrix[5][6] = matrix[4][2];
	matrix[5][3] = matrix[4][5];
	matrix[5][0] = matrix[4][8];
	for (i = 0; i < 3; i++) {
		matrix[4][2 + 3 * i] = matrix[0][2 + 3 * i];
		matrix[0][2 + 3 * i] = matrix[2][2 + 3 * i];
		matrix[2][2 + 3 * i] = temp[i];
	}
	draai_tegenwijzerzin(1, matrix);
}

/* @brief: (Right ClockWise Twice) draait het rechtervlak van de kubus tweemaal in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void RCW2(char matrix[6][9]) {
        char temp[6];
        /*DC1 openen
	Servo2 90° draaien in wijzerzin
	DC1 sluiten
        Servo2 in tegenwijzerzin 
        DC1 openen
        Servo2 terugzetten
        DC1 sluiten*/
        motor1open();
        delay_ms(500);
        servo2(90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        servo2(-90);
        delay_ms(500);
        motor1open();
        delay_ms(500);
        servo2(0);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        
        /*matrix aanpassen*/
        for (i = 0; i < 3; i++) {
		temp[i] = matrix[0][2 + 3 * i];
		temp[i + 3] = matrix[2][2 + 3 * i];
		matrix[2][2 + 3 * i] = matrix[4][2 + 3 * i];
		matrix[4][2 + 3 * i] = temp[3 + i];
		matrix[0][2 + 3 * i] = matrix[5][6 - 3 * i];
	}
	matrix[0][2] = matrix[5][6];
	matrix[0][5] = matrix[5][3];
	matrix[0][8] = matrix[5][0];
	matrix[5][0] = temp[2];
	matrix[5][3] = temp[1];
	matrix[5][6] = temp[0];
	draai_dubbel(1, matrix);
}

/* @brief: (Left ClockWise) draait de linkerkant van de kubus in wijzerzin
 *          en past de matrix aan
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void LCW(char matrix[6][9]) {
	char temp[3];
	/*DC1 openen
        Servo4 90° in tegenwijzerzin draaien
	DC1 sluiten
        Servo4 terugzetten*/
        motor1open();
        delay_ms(500);
        servo4(-90);
        delay_ms(500);
        motor1toe();
        delay_ms(500);
        servo4(0);
        delay_ms(500);

    /*matrix aanpassen*/
    temp[0] = matrix[5][8];
    temp[1] = matrix[5][5];
    temp[2] = matrix[5][2];
    matrix[5][8] = matrix[4][0];
    matrix[5][5] = matrix[4][3];
    matrix[5][2] = matrix[4][6];
    for (i = 0; i < 3; i++) {
	matrix[4][3 * i] = matrix[0][3 * i];
	matrix[0][3 * i] = matrix[2][3 * i];
	matrix[2][3 * i] = temp[i];
    }
    draai_wijzerzin(3, matrix);
}

/* @brief: (Left CounterClockWise) draait de linkerkant van de kubus in tegenwijzerzin 
 *         en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void LCCW(char matrix[6][9]) {
    char temp[3];
    /*DC1 openen
    Servo4 90° draaien in wijzerzin
    DC1 sluiten
    Servo4 terugzetten*/
    motor1open();
    delay_ms(500);
    servo4(90);
    delay_ms(500);
    motor1toe();
    delay_ms(500);
    servo4(0);
    delay_ms(500);

    /*matrix aanpassen*/
    temp[0] = matrix[5][8];
    temp[1] = matrix[5][5];
    temp[2] = matrix[5][2];
    matrix[5][8] = matrix[2][0];
    matrix[5][5] = matrix[2][3];
    matrix[5][2] = matrix[2][6];
    for (i = 0; i < 3; i++) {
	matrix[2][3 * i] = matrix[0][3 * i];
	matrix[0][3 * i] = matrix[4][3 * i];
	matrix[4][3 * i] = temp[i];
    }
    draai_tegenwijzerzin(3, matrix);
}

/* @brief: (Left ClockWise Twice) draait het linkervlak van de kubus tweemaal in wijzerzin
 *          en past de matrix aan.
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void LCW2(char matrix[6][9]) {
    char temp[6];
    /*DC1 openen
    Servo4 90° draaien in wijzerzin
    D1 sluiten
    Servo4 in tegenwijzerzin 
    DC1 openen
    Servo 4 terugzetten
    DC1 sluiten*/
    motor1open();
    delay_ms(500);
    servo4(90);
    delay_ms(500);
    motor1toe();
    delay_ms(500);
    servo4(-90);
    delay_ms(500);
    motor1open();
    delay_ms(500);
    servo4(0);
    delay_ms(500);
    motor1toe();
    delay_ms(500);
      
    /*matrix aanpassen*/
    for (i = 0; i < 3; i++) {
	temp[i] = matrix[0][3 * i];
	temp[i + 3] = matrix[2][3 * i];
	matrix[2][3 * i] = matrix[4][3 * i];
	matrix[4][3 * i] = temp[3 + i];
    	matrix[0][3 * i] = matrix[5][8 - 3 * i];
    }
    matrix[0][0] = matrix[5][8];
    matrix[0][3] = matrix[5][5];
    matrix[0][6] = matrix[5][2];
    matrix[5][2] = temp[2];
    matrix[5][5] = temp[1];
    matrix[5][8] = temp[0];
    draai_dubbel(3, matrix);
}

/* @brief: (Front ClockWise) draait de voorkant van de kubus in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void FCW(char matrix[6][9]) {
    char temp[3];
    /*DC2 openen
    ServoC 90° draaien in tegenwijzerzin
    DC2 sluiten
    ServoC terugzetten
    */
    motor2open();
    delay_ms(500);
    servo3(-90);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    servo3(10);
    delay_ms(500);

    /*matrix aanpassen*/
    for (i = 6; i < 9; i++) {
	temp[i - 6] = matrix[3][i];
	matrix[3][i] = matrix[5][i];
	matrix[5][i] = matrix[1][i];
	matrix[1][i] = matrix[0][i];
	matrix[0][i] = temp[i - 6];
    }
    draai_wijzerzin(4, matrix);
}

/* @brief: (Front CounterClockWise) draait de voorkant van de kubus in tegenwijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void FCCW(char matrix[6][9]) {
    char temp[3];
    /*DC2 openen
    ServoC 90° draaien in wijzerzin
    DC2 sluiten
    ServoC terugzetten*/
    motor2open();
    delay_ms(500);
    servo3(90);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    servo3(0);
    delay_ms(500);

    /*matrix aanpassen*/
    for (i = 6; i < 9; i++) {
	temp[i - 6] = matrix[0][i];
	matrix[0][i] = matrix[1][i];
	matrix[1][i] = matrix[5][i];
	matrix[5][i] = matrix[3][i];
	matrix[3][i] = temp[i - 6];
    }
    draai_tegenwijzerzin(4, matrix);
}

/* @brief: (Front ClockWise Twice) draait het voorvlak van de kubus tweemaal in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void FCW2(char matrix[6][9]) {
    char temp[6];
    /*DC2 openen
    Servo1 90° in wijzerzin draaien
    DC2 sluiten
    Servo1 90 in tegenwijzerzin draaien
    DC2 openen
    Servo1 terugzetten
    DC2 sluiten*/
    motor2open();
    delay_ms(500);
    servo1(90);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    servo1(-90);
    delay_ms(500);
    motor2open();
    delay_ms(500);
    servo1(0);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    
    /*matrix aanpassen*/
    for (i = 0; i < 3; i++) {
    	temp[i] = matrix[0][6 + i];
	matrix[0][6 + i] = matrix[5][i + 6];
	matrix[5][6 + i] = temp[i];
	temp[i + 3] = matrix[1][6 + i];
	matrix[1][6 + i] = matrix[3][i + 6];
	matrix[3][6 + i] = temp[i + 3];
    }
    draai_dubbel(4, matrix);
}

/* @brief: (Back ClockWise) draait de achterkant van de kubus in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void BCW(char matrix[6][9]) {
    char temp[3];
    /*DC2 openen
    Servo1 90° in tegenwijzerzin draaien
    DC2 sluiten
    Servo1 terugdraaien*/
    motor2open();
    delay_ms(500);
    servo1(-90);
    delay_ms(500);
    motor2toe();
    servo1(0);
    delay_ms(500);
        
    /*matrix aanpassen*/
    for (i = 0; i < 3; i++) {
	temp[i] = matrix[0][i];
	matrix[0][i] = matrix[1][i];
	matrix[1][i] = matrix[5][i];
	matrix[5][i] = matrix[3][i];
	matrix[3][i] = temp[i];
    }
    draai_wijzerzin(2, matrix);
}

/* @brief: (Back CounterClockWise) draait de achterkant van de kubus in tegenwijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void BCCW(char matrix[6][9]) {
    char temp[3];
    /*DC2 openen
    Servo1 90° in wijzerzin draaien
    DC2 sluiten
    Servo1 terugdraaien*/
    motor2open();
    delay_ms(500);
    servo1(90);
    delay_ms(500);
    motor2toe();
    servo1(0);
    delay_ms(500);

    /*matrix aanpassen*/
    for (i = 0; i < 3; i++) {
    	temp[i] = matrix[3][i];
    	matrix[3][i] = matrix[5][i];
	matrix[5][i] = matrix[1][i];
	matrix[1][i] = matrix[0][i];
	matrix[0][i] = temp[i];
    }
    draai_tegenwijzerzin(2, matrix);
}

/* @brief: (Back ClockWise Twice) draait de achterkant van de kubus tweemaal in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void BCW2(char matrix[6][9]) {
    char temp[6];
    /*DC2 openen
    Servo1 90° in wijzerzin draaien
    DC2 sluiten
    Servo1 90 in tegenwijzerzin draaien
    DC2 openen
    Servo1 terugzetten
    DC2 sluiten*/
    motor2open();
    delay_ms(500);
    servo1(90);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    servo1(-90);
    delay_ms(500);
    motor2open();
    delay_ms(500);
    servo1(0);
    delay_ms(500);
    motor2toe();
    delay_ms(500);
    
    /*Matrix aanpassen*/
    for (i = 0; i < 3; i++) {
	temp[i] = matrix[0][i];
	matrix[0][i] = matrix[5][i];
	matrix[5][i] = temp[i];
	temp[i + 3] = matrix[1][i];
	matrix[1][i] = matrix[3][i];
	matrix[3][i] = temp[i + 3];
    }
    draai_dubbel(2, matrix);
}

/* @brief: (Up ClockWise) draait de bovenkant van de kubus in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void UCW(char matrix[6][9]) {
    draai_onder(matrix);
    FCW(matrix);
    draai_boven(matrix);
}

/* @brief: (Up CounterClockWise) draait de bovenkant van de kubus in tegenwijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void UCCW(char matrix[6][9]) {
    draai_onder(matrix);
    FCCW(matrix);
    draai_boven(matrix);
}

/* @brief: (Up ClokWise Twice) draait de bovenkant van de kubus tweemaal
 * @param: char matrix[6][9]: de matrix van de kubus
 * @return: void */
void UCW2(char matrix[6][9]){
    draai_onder(matrix);
    FCW2(matrix);
    draai_boven(matrix);
}

/* @brief: (Down ClockWise) draait de onderkant van de kubus in wijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void DCW(char matrix[6][9]) {
    draai_boven(matrix);
    FCW(matrix);
    draai_onder(matrix);
}

/* @brief: (Down CounterClockWise) draait de onderkant van de kubus in tegenwijzerzin
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void DCCW(char matrix[6][9]) {
    draai_boven(matrix);
    FCCW(matrix);
    draai_onder(matrix);
}

/* @brief: (Down ClockWise Twice) draait de onderkant van de kubus in tweemaal
 * @param:  char matrix[6][9]: de matrix van de kubus
 * @return: void*/
void DCW2(char matrix[6][9]) {
    draai_boven(matrix);
    FCW2(matrix);
    draai_onder(matrix);
}