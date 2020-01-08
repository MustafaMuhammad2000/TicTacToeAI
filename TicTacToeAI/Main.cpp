#include <iostream>
#include "function.h"
#include <algorithm>
#include <windows.h>
using namespace std;
char player = 'X';
char ai = 'O';
char board[3][3] = { '-','-','-','-','-','-','-','-','-' };

int main() {
	int checker;
	char key_pressed;
	int numericvalue;
	display();
	while (1) {
		key_pressed = getchar();
		numericvalue = key_pressed;
			if (numericvalue == 32){
				break;
		}
	}
	while (true) {
		drawboard(board);
		playerinput(board);
		if (outofspace(board)) {
			cout << "Tie, exiting program now";
			break;
		}
		checker = eval(board);
		if (checker == 10) {
			cout << "Ai wins you suck, exiting program now";
			break;
		}
		else if (checker == -10) {
			cout << "Well done you beat the bot, exiting program now";
			break;
		}
		drawboard(board);
		aiinput(board);
		if (outofspace(board)) {
			cout << "Tie";
			break;
		}
		checker = eval(board);
		if (checker == 10) {
			cout << "Ai wins you suck, exiting program now";
			break;
		}
		else if (checker == -10) {
			cout << "Well done you beat the bot, exiting program now";
			break;
		}
	}
	cout << "\n";
	drawboard(board);
	Sleep(3000);
}

void drawboard(char b[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << b[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void playerinput(char b[3][3]) {
	while (true) {
		location spot;
		cout << "Enter row to place \n";
		cin >> spot.row;
		cout << "Enter column to place \n";
		cin >> spot.column;
		if (!objectplaced(b, spot.row, spot.column)) {
			b[spot.row][spot.column] = player;
			return;
		}
		else {
			cout << "Invalid input entered, please select new spot";
		}
	}
}

bool objectplaced(char b[3][3], int row, int column) {
	if (b[row][column] == player || b[row][column] == ai) {
		return true;
	}
	else {
		return false;
	}
}

bool outofspace(char b[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] != player && b[i][j] != ai)
				return false;
		}
	}
	return true;
}


int eval(char b[3][3]) {

	for (int i = 0; i < 3; i++) {
		if ((b[i][0] == b[i][1]) && (b[i][1] == b[i][2])) {
			if (b[i][0] == ai) {
				return 10;
			}
			else if (b[i][0] == player) {
				return -10;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if ((b[0][i] == b[1][i]) && (b[1][i] == b[2][i])) {
			if (b[0][i] == ai) {
				return 10;
			}
			else if (b[0][i] == player) {
				return -10;
			}
		}
	}
	if ((b[0][0] == b[1][1]) && (b[1][1] == b[2][2])) {
		if (b[0][0] == ai) {
			return 10;
		}
		else if (b[0][0] == player) {
			return -10;
		}
	}
	if ((b[0][2] == b[1][1]) && (b[1][1] == b[2][0])) {
		if (b[0][2] == ai) {
			return 10;
		}
		else if (b[0][2] == player) {
			return -10;
		}
	}

	return 0;
}

int minimax(char b[3][3], int depth, bool AiTurn) {
	int result;
	result = eval(b);
	if (result == 10) {
		return result - depth;
	}
	if (result == -10) {
		return result + depth;
	}

	if (outofspace(b) == true) {
		return 0;
	}

	if (AiTurn)
	{
		int high = -1000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!objectplaced(b, i, j)) {
					b[i][j] = ai;
					high = max(high, minimax(b, depth + 1, false));
					b[i][j] = '-';
				}
			}
		}
		/* cout << "HIGH VALUE: " << high; */
		return high;
	}
	else if (!AiTurn)
	{
		int low = 1000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!objectplaced(b, i, j)) {
					b[i][j] = player;
					low = min(low, minimax(b, depth + 1, true));
					b[i][j] = '-';
				}
			}
		}
		return low;
	}
}

location bestmove(char b[3][3]) {
	location prime;
	prime.row = -1;
	prime.column = -1;
	int best = -1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (objectplaced(b, i, j) == false) {
				b[i][j] = ai;
				int otherbest = minimax(b, 0, false);
				b[i][j] = '-';
				if (otherbest > best) {
					best = otherbest;
					prime.row = i;
					prime.column = j;
				}
			}
		}
	}
	return prime;
}



void aiinput(char b[3][3]) {
	location goodmove;
	goodmove = bestmove(b);
	b[goodmove.row][goodmove.column] = ai;
}

void display() {
	cout << "  Welcome to my TicTacToe game. \n  Featuring an unbeatable bot.\n  Try your darndest to beat it!!!!" << endl;
	cout << "\n\n       Press SPACEBAR then ENTER to continue" << endl;
}