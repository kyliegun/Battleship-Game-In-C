SinkingShips: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o ShinkingShips main.c game.c opponentAI.c

test: testing.c game.h game.c
	gcc -o test --coverage testing.c game.c 