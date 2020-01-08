#pragma once
struct location {
	int row;
	int column;
};
bool outofspace(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: Checks to see if the board is out of space */
int eval(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: Checks to see if the AI or player has 3 in a row*/
int minimax(char b[3][3], int depth, bool AiTurn);
/* Requires: The board, a 3x3 array
   Promises: Minimax function*/
bool objectplaced(char b[3][3], int row, int column);
/* Requires: The board, a 3x3 array
   Promises: Checks to see if an object is placed at a certain location*/
location bestmove(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: Returns the best move for the AI*/
void playerinput(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: Allows the player to place an X */
void aiinput(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: The AI places an O */
void drawboard(char b[3][3]);
/* Requires: The board, a 3x3 array
   Promises: Draws the current state of the board*/
void display();
/* Requires: Nothing
   Promises: Displays opening messages */