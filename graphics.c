#include "graphics.h"

int initgraphics(struct Cells* cells) {
	sfVideoMode mode = {WIDTH, HEIGHT, 32}; 							// stworzenie ustawien ekranu
	window = sfRenderWindow_create(mode, "Gra w zycie", sfClose, NULL); // tworzenie okna 
	sfRenderWindow_setKeyRepeatEnabled(window, sfFalse); 				// wylaczanie powtarzania akcji przycisku (NIE DZIALA :C)
	sfRenderWindow_setFramerateLimit(window, 60); 						// ustawienie limitu FPS

	block = sfRectangleShape_create(); 			// tworzenie ksztaltu komorki
	sfVector2f size = {BWIDTH-SPACING*2, BHEIGHT-SPACING*2}; 	// ustalenie wielkosci
	sfRectangleShape_setSize(block, size); 	 	// ustalenie wielkosci komorki
	sfVector2f offset = {-SPACING, -SPACING};	// ustalenie przesuniecia wspolrzednych
	sfRectangleShape_setOrigin(block, offset);	// ustalenie przesuniecia wspolrzednych komorki

	aliveColor = sfColor_fromRGB(RED1, GREEN1, BLUE1); 	// ustalenie koloru zywej komorki
	deadColor = sfColor_fromRGB(RED0, GREEN0, BLUE0); 	// ustalenie koloru martwej komorki
	
	if(textinit()) { // jezeli brak fonta
		printf("Brak fonta\n"); 
		return 1;
	}
	else {
		return 0;
	}
}

void clean() {
	free(cells);
	sfText_destroy(text);
	sfFont_destroy(font);
	sfRectangleShape_destroy(block);
	sfRenderWindow_destroy(window);
}

int textinit() {
	font = sfFont_createFromFile("arial.ttf"); // ladowanie fonta

    if (!font)
        return 1;

    text = sfText_create();
    sfText_setFont(text, font); 		// ustalanie fonta
    sfText_setCharacterSize(text, 12);  // ustalanie wielkosci tekstu
	sfText_setColor(text, aliveColor);  // ustalanie koloru tekstu

	return 0;
}

void textdraw() {
	char gentext[20];
	int gencounter = counter();
	sprintf(gentext, "Generacja: %d", gencounter);  // zamiana "Generacja: licznik" na string 

	sfText_setString(text, gentext); 				// ustawienie tekstu
	sfRenderWindow_drawText(window, text, NULL); 	// rysowanie tekstu
}

void disp(struct Cells* cells) {
	sfRenderWindow_clear(window, sfBlack); // czyszczenie ekranu
	
	for (int i = OFFSET; i < COLS - OFFSET; i++) { // przechodzenie przez wszystkie komorki
		for (int j = OFFSET; j < ROWS - OFFSET; j++) {

			sfVector2f blockPos = {BWIDTH*(i - OFFSET), BHEIGHT*(j - OFFSET)};
			sfRectangleShape_setPosition(block, blockPos); 			// ustalenie pozycji komorki

			if (cells->parentGeneration[i][j] == 0)
				sfRectangleShape_setFillColor(block, deadColor); 	// ustalanie koloru komorki - komorka martwa
			if (cells->parentGeneration[i][j] == 1)
				sfRectangleShape_setFillColor(block, aliveColor); 	// ustalanie koloru komorki - komorka zywa

			sfRenderWindow_drawRectangleShape(window, block, NULL); // rysowanie komorki
		}
	}
	
	textdraw(); // wyswietlanie licznika generacji
	sfRenderWindow_display(window); // wyswietlenie bufora
}