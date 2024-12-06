SinkingShips: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -o SinkingShips main.c game.c opponentAI.c

test: testing.c game.h game.c opponentAI.c opponentAI.h
	gcc -D DEBUG -o test --coverage testing.c game.c opponentAI.c

debug: main.c game.h game.c opponentAI.h opponentAI.c
	gcc -D DEBUG -o debug --coverage main.c game.c opponentAI.c