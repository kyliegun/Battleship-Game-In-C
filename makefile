SinkingShips: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o SinkingShips main.c game.c opponentAI.c

test_ai: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o test_ai --coverage main.c game.c opponentAI.c