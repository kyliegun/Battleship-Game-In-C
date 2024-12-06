# the-team-assignment-team-19

## SINKING SHIPS

**Built with:** C, ASCII, Bash

Sinking Ships is a strategic battleship game designed for single or multiplayer use. Users can play against AI and select the level of difficulty. The ships are arranged on a grid and the users take turns to locate and sink the opponent’s ships. 

**How to Play & Rules**
1. This is a terminal-based game. 
2. User can compile the game by running:
			gcc -o battleship main.c game.c opponentAI.c
3. User can start the game by running:
	./battleship
Or        ./battleship --help
4. This is intended to be a two-player game. The user can play against an AI.
5. The user can choose the difficulty level with the AI.
6. The player will be prompted to place 5 ships. They select the coordinate at which the ship starts and extend it vertically or horizontally.
7. The player cannot overlap the ships.
8. The game begins as each player takes turns choosing the coordinates they want to shoot at.
9. The game will end once all of a player's ships have been sunk.

**Example Usage**
