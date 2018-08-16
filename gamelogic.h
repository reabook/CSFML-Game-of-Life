#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "graphics.h"


struct Cells {
    int Generation[COLS][ROWS];			// nowa generacja
    int parentGeneration[COLS][ROWS];	// stara generacja
};

static struct Cells* cells;     // zmienna strukturalna ze stanami komorek

static int gencounter; 			// licznik generacji
static int flag;                // flaga tworzenia

int init();         // inicjalizacja
void create();		// tworzenie komorki myszka
void destroy(); 	// niszczenie komorki myszka
void clear(); 		// czyszczenie generacji, ekranu
void randomize(); 	// generowanie losowego ukladu
void generate(); 	// generowanie nastepnej generacji
int counter(); // zwraca numer generacji
int returnflag();  // zwraca wartosc flagi
void switchflag();  // zmiana wartosci flagi

#endif