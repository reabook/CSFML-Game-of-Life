all: clean gameoflife
	
gameoflife: gameoflife.c
	@gcc -O3 gameoflife.c gamelogic.c graphics.c -o gameoflife -lm -lcsfml-graphics -lcsfml-window -lcsfml-system

	@echo "Buduje =)"

clean:
	@rm -f gameoflife
