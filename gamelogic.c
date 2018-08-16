#include "gamelogic.h"

int init() {
	cells = calloc(1, sizeof(struct Cells)); // alokacja pamieci dla zmiennej strukturalnej
	gencounter = 0; // inicjalizacja licznika
	flag = 0;		// inicjalizacja flagi tworzenia

	srand(time(NULL)); // ziarno dla generatora liczb pseudolosowych

	if(!initgraphics()) { // jesli inicjalizacja graficznej czesci programu sie powiedzie
		disp(cells);
		return 0;
	}
	else 
		return 1;
}

void randomize() {
	gencounter = 0; // reset generacji
	flag = 0;		// reset flagi
	clear();		// reset matrycy i ekranu
	
	for (int i = OFFSET; i < COLS-OFFSET; i++) { // przechodzenie przez wszystkie komorki
		for (int j = OFFSET; j < ROWS-OFFSET; j++) {
			int los = rand() % 4; // losowanie stanu komorki
			if(los==1) cells->parentGeneration[i][j] = los; // przypisywanie stanu
		}
	}
	
	disp(cells); // wyswietlenie
}

void create() {
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(window); // pobranie polozenia kursora
	
	int i = floor(mousePos.x / BWIDTH) + OFFSET;  // ustalenie do ktorej komorki nalezy (os X)
	int j = floor(mousePos.y / BHEIGHT) + OFFSET; // ustalenie do ktorej komorki nalezy (os Y)

	if (i >= 0 && j >= 0 && i<COLS && j<ROWS) {   // sprawdzanie czy kursor jest w oknie programu

		if (cells->parentGeneration[i][j] == 0 || cells->Generation[i][j] == 0) {

			cells->parentGeneration[i][j] = 1;    // ozywienie komorki
//			cells->Generation[i][j] = 1;
			disp(cells);
		}
	}
	
}

void destroy() {
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
	
	int i = floor(mousePos.x / BWIDTH) + OFFSET;  // ustalenie do ktorej komorki nalezy (os X)
	int j = floor(mousePos.y / BHEIGHT) + OFFSET; // ustalenie do ktorej komorki nalezy (os Y)

	if (i >= 0 && j >= 0 && i<COLS && j<ROWS) {   // sprawdzanie czy kursor jest w oknie programu

		if (cells->parentGeneration[i][j] == 1 || cells->Generation[i][j] == 1) {

			cells->parentGeneration[i][j] = 0;	  // niszczczenie komorki
//			cells->Generation[i][j] = 0;
			disp(cells);
		}
	}
	
}

void clear() {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			cells->parentGeneration[i][j] = 0; // czyszczenie dwoch generacji
			cells->Generation[i][j] = 0;
		}
	}
	
	flag = 0;
	gencounter = 0;
	sfRenderWindow_clear(window, sfBlack); // czyszczenie ekranu
	disp(cells);
}

void generate() {
	for (int i = 1; i < COLS-1; i++) { // przechodzenie przez kazda komorke
		for (int j = 1; j < ROWS-1; j++)
		{
			int alive = 0;
			// ile sasiednich komorek zyje
			alive = cells->parentGeneration[i-1][j-1] + cells->parentGeneration[i][j-1] + cells->parentGeneration[i+1][j-1] + //gora
					cells->parentGeneration[i-1][j]   + cells->parentGeneration[i+1][j] +									   //srodek
					cells->parentGeneration[i-1][j+1] + cells->parentGeneration[i][j+1] + cells->parentGeneration[i+1][j+1];  // dol

			if (cells->parentGeneration[i][j] == 0) {
				if (alive == 3) { 	// jezeli ma dokladnie dwoch zyjacych sasiadow ozywa
					cells->Generation[i][j] = 1; // ozywianie komorki
				}
			}

			else {
				if (alive < 2) { 		 // jezeli nie ma dwoch zyjacych sasiadow umiera
					cells->Generation[i][j] = 0;
				} else if (alive > 3) {  // jezeli ma wiecej niz trzech zyjacych sasiadow umiera
					cells->Generation[i][j] = 0;
				} else { 				 // jezeli ma dwoch lub trzech zyjacych sasiadow to pozostaje zywa
					cells->Generation[i][j] = 1;
				}

			}
			
		}
	}
	// przepisanie tablic generacji
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			cells->parentGeneration[i][j] = cells->Generation[i][j];
		}
	}
	
	gencounter++; // dodawanie do licznika
	disp(cells);
}

int counter() {
    return gencounter; // zwraca licznik
}

int returnflag() {
	return flag;	   // zwraca flage
}

void switchflag() {    // zmienia wartosc flagi na przeciwna
	if(flag)
		flag = 0;
	else 
		flag = 1;
}