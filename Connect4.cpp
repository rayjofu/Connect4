#include "Connect4.h"
#include <iostream>

Connect4::Connect4() {
	setup();
	start();
}

Connect4::Connect4(int cols, int rows, int match, bool wrapAround) {
	board = new Board(cols, rows, match, wrapAround);
	start();
}

Connect4::~Connect4() {
	delete board;
}

void Connect4::setup() {
	int col;
	std::cout << "Please enter number of columns (7-10): ";
	std::cin >> col;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (!isBetween(col, colMin, colMax)) {
		std::cout << "Invalid input. Please enter number of columns (7-10): ";
		std::cin >> col;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	int row;
	std::cout << "Please enter number of rows (6-10): ";
	std::cin >> row;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (!isBetween(row, rowMin, rowMax)) {
		std::cout << "Invalid input. Please enter number of rows (6-10): ";
		std::cin >> row;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	int match;
	std::cout << "Please enter number of connects to win (4-6): ";
	std::cin >> match;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (!isBetween(match, matchMin, matchMax)) {
		std::cout << "Invalid input. Please enter number of connects to win (4-6): ";
		std::cin >> match;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	char c;
	bool wrapAround;
	std::cout << "Enable wraparound? (Y/N): ";
	std::cin >> c;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
		std::cout << "Invalid input. Enable wraparound? (Y/N): ";
		std::cin >> c;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	wrapAround = (c == 'Y' || c == 'y');

	board = new Board(col, row, match, wrapAround);
}

void Connect4::start() {
	bool retry = true;
	int result = -1;
	int col;
	char c;
	while (retry) {
		std::cout << std::endl << "Let's play Connect " << board->getMatch() << "!" << std::endl;

		while (result <= 0) {
			std::cout << std::endl;
			board->print();
			std::cout << std::endl << "Player " << board->getTurn() << "'s turn. Please choose a column: ";
			std::cin >> col;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			while (!board->isValidMove(col)) {
				std::cout << "Invalid input. Player " << board->getTurn() << "'s turn. Please choose a column: ";
				std::cin >> col;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			result = board->move(col);
		}
		std::cout << std::endl;
		board->print();

		// winner
		if (result == 1) {
			std::cout << std::endl << "Player " << board->getTurn() << " wins!" << std::endl;
		}

		// tie
		else if (result == 2) {
			std::cout << std::endl << "Game is tied!" << std::endl;
		}

		std::cout << "Play again? (Y/N): ";
		std::cin >> c;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
			std::cout << "Invalid input. Play again? (Y/N): ";
			std::cin >> c;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (c == 'Y' || c == 'y') {
			retry = true;
			board->reset();
			result = -1;
		}
	}
}

bool Connect4::isBetween(int n, int min, int max) {
	if (min > max && (n > min || n < max)) {
		return false;
	}
	if (min <= max && (n > max || n < min)) {
		return false;
	}
	return true;
}