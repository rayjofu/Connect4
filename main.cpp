#include <iostream>
using namespace std;

bool isBetween(int input, int a, int b);
int* createColumnChecker();
char** createGrid();
void destroyGrid();
void destroyArray();
void printGrid();
bool isValidInput(int input);
int handleInput(int input);
bool checkWinner(int row, int col, char player);
bool checkHorizontal(int row, int col, char player);
bool checkVertical(int row, int col, char player);
bool checkDiagonal(int row, int col, char player);

int const rowMin = 6;
int const rowMax = 10;
int const colMin = 7;
int const colMax = 10;
int const connectMin = 4;
int const connectMax = 6;
int rows;
int cols;
int turns;
int connects;
bool wrapSides = false;
int *columnIndexes;
char **grid;

int main() {
	cout << "Let's play Connect 4-6!" << endl;
	while (1) {
		int input;
		char c;

		while (1) {
			cout << endl << "Please enter number of rows (6-10): ";
			cin >> input;
			if (isBetween(input, rowMin, rowMax)) {
				rows = input;
				break;
			}
			cout << "Invalid number. ";
		}
		while (1) {
			cout << "Please enter number of columns (7-10): ";
			cin >> input;
			if (isBetween(input, colMin, colMax)) {
				cols = input;
				break;
			}
			cout << "Invalid number. ";
		}
		while (1) {
			cout << "Please enter number of connects to win (4-6): ";
			cin >> input;
			if (isBetween(input, connectMin, connectMax)) {
				connects = input;
				break;
			}
			cout << "Invalid number. ";
		}
		while (1) {
			cout << "Enable winning from wrapping around sides (y/n)? ";
			cin >> c;
			if (c == 'y' || c == 'Y') {
				wrapSides = true;
				break;
			} else if (c == 'n' || c == 'N') {
				wrapSides = false;
				break;
			}
			cout << "Invalid input. ";
		}

		turns = 0;
		columnIndexes = createColumnChecker();
		grid = createGrid();

		while (1) {
			printGrid();
			while (1) {
				cout << "Player " << ((turns % 2 == 0) ? 'X' : 'O') << "\'s turn! Type a column number to insert a piece: ";
				cin >> input;
				if (isBetween(input, 0, cols) && isValidInput(input)) {
					break;
				}
				cout << "Invald column number. ";
			}
			if (handleInput(input) > 0) {
				printGrid();
				cout << endl << "Player " << ((turns % 2 == 0) ? 'X' : 'O') << " wins!" << endl;
				break;
			}
			if (++turns >= rows*cols) {
				cout << endl << "Game is tied!" << endl;
				break;
			}
		}

		destroyGrid();
		destroyArray();

		while (1) {
			cout << endl << "Play again (y\\n)? ";
			cin >> c;
			if (c == 'y' || c == 'n' || c == 'Y' || c == 'N') {
				break;
			}
			cout << "Invalid input. ";
		}

		if (c == 'n' || c == 'N') {
			break;
		}
	}
}

bool isBetween(int input, int a, int b) {
	if (a <= b && (input < a || input > b )) {
		return false;
	}
	if (a > b && (input > a || input < b)) {
		return false;
	}
	return true;
}

int* createColumnChecker() {
	int *arr = new int[cols];
	for (int x = 0; x < cols; x++) {
		arr[x] = rows;
	}
	return arr;
}

char** createGrid() {
	char **grid = new char*[rows];
	for (int y = 0; y < rows; y++) {
		grid[y] = new char[cols];
		for (int x = 0; x < cols; x++) {
			grid[y][x] = '.';
		}
	}
	return grid;
}

void destroyGrid() {
	for (int y = 0; y < rows; y++) {
		delete [] grid[y];
	}
	delete [] grid;
}

void destroyArray() {
	delete[] columnIndexes;
}

void printGrid() {
	cout << endl;

	int x, y;
	for (x = 0; x < cols; x++) {
		cout << " " << x + 1;
	}
	cout << endl;

	for (y = 0; y < rows; y++) {
		for (x = 0; x < cols; x++) {
			cout << " " << grid[y][x];
		}
		cout << endl;
	}
	cout << endl;
}

bool isValidInput(int input) {
	if (columnIndexes[input - 1] == 0) {
		return false;
	}
	columnIndexes[input - 1]--;
	return true;
}

int handleInput(int input) {
	int row = columnIndexes[input - 1];
	int col = input - 1;
	char player = (turns % 2 == 0) ? 'X' : 'O';
	grid[row][col] = player;
	if (turns >= 2 * (connects - 1) && checkWinner(row, col, player)) {
		return 1;
	}
	return 0;
}

bool checkWinner(int row, int col, char player) {
	return checkHorizontal(row, col, player) ||
		   checkVertical(row, col, player) ||
		   checkDiagonal(row, col, player);
}

bool checkHorizontal(int row, int col, char player) {
	int count = 1;
	int x = col - 1;
	while (1) {
		if (x < 0) {
			x = cols - 1;
		}
		if (grid[row][x] != player) {
			break;
		}
		x--;
		count++;
	}
	if (count >= connects) {
		return true;
	}

	x = col + 1;
	while (1) {
		if (x > cols) {
			x = 0;
		}
		if (grid[row][x] != player) {
			break;
		}
		x++;
		count++;
	}
	if (count >= connects) {
		return true;
	}
	return false;
}

bool checkVertical(int row, int col, char player) {
	int count = 1;
	int y = row + 1;
	while (y < rows) {
		if (grid[y][col] != player) {
			break;
		}
		y++;
		count++;
	}
	if (count >= connects) {
		return true;
	}
	return false;
}

bool checkDiagonal(int row, int col, char player) {
	// checking '\'
	int count = 1;
	int x = col + 1;
	int y = row + 1;
	while (1) {
		if (x >= cols) {
			x = 0;
		}
		if (y >= rows) {
			break;
		}
		if (grid[y][x] != player) {
			break;
		}
		x++;
		y++;
		count++;
	}
	if (count >= connects) {
		return true;
	}

	x = col - 1;
	y = row - 1;
	while (1) {
		if (x < 0) {
			x = cols - 1;
		}
		if (y < 0) {
			break;
		}
		if (grid[y][x] != player) {
			break;
		}
		x--;
		y--;
		count++;
	}
	if (count >= connects) {
		return true;
	}

	// checking '/'
	count = 1;
	x = col - 1;
	y = row + 1;
	while (1) {
		if (x < 0) {
			x = cols - 1;
		}
		if (y >= rows) {
			break;
		}
		if (grid[y][x] != player) {
			break;
		}
		x--;
		y++;
		count++;
	}
	if (count >= connects) {
		return true;
	}

	x = col + 1;
	y = row - 1;
	while (1) {
		if (x >= cols) {
			x = 0;
		}
		if (y < 0) {
			break;
		}
		if (grid[y][x] != player) {
			break;
		}
		x++;
		y--;
		count++;
	}
	if (count >= connects) {
		return true;
	}
	return false;
}