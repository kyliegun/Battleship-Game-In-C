battleship: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o battleship main.c game.c opponentAI.c

test_ai: main2.c game.h game.c opponentAI.h opponentAI.c
	gcc -o test_ai main2.c game.c opponentAI.c