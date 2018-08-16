#ifndef CONFIG_H
#define CONFIG_H

// kolor zywej komorki
#define RED1 0
#define GREEN1 120
#define BLUE1 215

//kolor martwej komorki
#define RED0 32
#define GREEN0 32
#define BLUE0 32

// wielkosc komorki
#define BWIDTH 10
#define BHEIGHT 10

// odleglosc miedzy komorkami
#define SPACING 1

// wielkosc okna
#define WIDTH 1000
#define HEIGHT 1000

// obliczanie ilosci komorek
#define OFFSET 10
#define COLS ((WIDTH/BWIDTH)+2*OFFSET)
#define ROWS ((HEIGHT/BHEIGHT)+2*OFFSET)

#endif