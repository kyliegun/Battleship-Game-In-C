make battleship: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o battle main.c game.c opponentAI.c
