#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "gamelogic.h"
#include "graphics.h"


int main() {

	if(init())
		return 0;

	while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event)) // nasluchiwanie zdarzen
        {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
				clean(); // czyszczenie z pozostalosci
				return 0;
			}

// 			debugowanie zdarzen
//			printf("event %d %d\n", event.type, sfKeyboard_isKeyPressed(sfKeyR));

			// event.type - typ zdarzenia, NIE DZIALA poprawnie w przypadku nacisniecia pojedynczego przycisku
			// uzywam delaya, by z grubsza wyeliminowac powtarzanie akcji
			if(sfKeyboard_isKeyPressed(sfKeyR)) {randomize(); usleep(500000);} // R - generowanie losowego ukladu
			if(sfKeyboard_isKeyPressed(sfKeyC)) clear(); // C - czyszczenie
			if(sfKeyboard_isKeyPressed(sfKeySpace)) { // Spacja - start/stop
				switchflag();
				usleep(200000);
			}

			if(sfMouse_isButtonPressed(sfMouseLeft)) create(); 		// tworzenie komorki myszka
			if(sfMouse_isButtonPressed(sfMouseRight)) destroy(); 	// niszczenie komorki myszka
        }

		if (returnflag()) { // uruchamianie generowania matryc
			generate(); 
//			switchflag();
		}

    }

	return 0;
}