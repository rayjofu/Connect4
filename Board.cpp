#include "Board.h"
#include <iostream>

// board[0][0]				== bottom left
// board[0][rows-1]			== top left
// board[cols-1][rows-1]	== top right
// board[cols-1][0]			== bottom right
Board::Board(int c, int r, int m, bool w) {
	cols = c;
	rows = r;
	match = m;
	wrapAround = w;
	board = new char*[cols];
	top = new int[cols];
	for (int x = 0; x < cols; ++x) {
		top[x] = 0;
		board[x] = new char[rows];
		for (int y = 0; y < rows; ++y) {
			board[x][y] = '.';
		}
	}
	turns = 0;
}

Board::~Board() {
	for (int i = 0; i < rows; ++i) {
		delete[] board[i];
	}
	delete[] board;
	delete[] top;
}

void Board::print() {
	for (int i = 0; i < cols; ++i) {
		std::cout << " " << i;
	}
	std::cout << std::endl;

	for (int y = rows - 1; y >= 0; --y) {
		for (int x = 0; x < cols; ++x) {
			std::cout << " " << board[x][y];
		}
		std::cout << std::endl;
	}
}

bool Board::isValidMove(int c) {
	if (c < 0 || c >= cols) {
		return false;
	}
	return top[c] != rows;
}

int Board::move(int c) {
	// invald
	if (!isValidMove(c)) {
		return -1;
	}

	char player = getTurn();
	board[c][top[c]] = player;

	// win
	if (turns >= (2 * match - 2) && hasWinner(c, top[c])) {
		return 1;
	}

	// tie
	if (turns == (cols * rows - 1)) {
		return 2;
	}

	++top[c];
	++turns;
	return 0;
}

bool Board::hasWinner(int c, int r) {
	int x;
	int y;
	int count;
	char player = getTurn();

	//check left
	x = (wrapAround)? (c - 1) % cols : c - 1;
	y = r;
	count = 1;
	while (x >= 0 && board[x][y] == player) {
		++count;
		--x;
		if (wrapAround) {
			x = (x + cols) % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	// check right
	x = (wrapAround) ? (c + 1) % cols : c + 1;
	while (x < cols && board[x][y] == player) {
		++count;
		++x;
		if (wrapAround) {
			x = x % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	// check down
	x = c;
	y = r - 1;
	count = 1;
	while (y >= 0 && board[x][y] == player) {
		++count;
		--y;
	}
	if (count >= match) {
		return true;
	}

	// check bottom right diagonal
	x = (wrapAround) ? (c + 1) % cols : c + 1;
	y = r - 1;
	count = 1;
	while (x < cols && y >= 0 && board[x][y] == player) {
		++count;
		++x;
		--y;
		if (wrapAround) {
			x = x % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	// check top left diagonal
	x = (wrapAround) ? (c - 1) % cols : c - 1;
	y = r + 1;
	while (x >= 0 && y < rows && board[x][y] == player) {
		++count;
		--x;
		++y;
		if (wrapAround) {
			x = (x + cols) % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	// check bottom left diagonal
	x = (wrapAround) ? (c - 1) % cols : c - 1;
	y = r - 1;
	count = 1;
	while (x >= 0 && y >= 0 && board[x][y] == player) {
		++count;
		--x;
		--y;
		if (wrapAround) {
			x = (x + cols) % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	// check top right diagonal
	x = (wrapAround) ? (c + 1) % cols : c + 1;
	y = r + 1;
	while (x < cols && y < rows && board[x][y] == player) {
		++count;
		++x;
		++y;
		if (wrapAround) {
			x = x % cols;
		}
	}
	if (count >= match) {
		return true;
	}

	return false;
}

char Board::getTurn() {
	return (turns % 2) ? 'X' : 'O';
}

int Board::getColumnSize() {
	return cols;
}

int Board::getMatch() {
	return match;
}

void Board::reset() {
	for (int x = 0; x < cols; ++x) {
		top[x] = 0;
		for (int y = 0; y < rows; ++y) {
			board[x][y] = '.';
		}
	}
	turns = 0;
}