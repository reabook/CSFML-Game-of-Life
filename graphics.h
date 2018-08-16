#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "gamelogic.h"

// SFML
sfRenderWindow* window;                // okno
sfEvent event;                         // zdarzenia

static sfRectangleShape* block;        // ksztalt komorki

static sfFont* font;                   // font
static sfText* text;                   // tekst
static sfColor aliveColor, deadColor;  // kolory komorek

struct Cells;

int initgraphics();         // inicjalizacja biblioteki graficznej
void clean();               // czyszczenie niepotrzebnych rzeczy po biblitece graficznej
int textinit();             // inicjalizacja tekstu
void textdraw();            // rysowanie tekstu
void disp(struct Cells*);   // wyswietlanie matrycy i licznika generacji

#endif