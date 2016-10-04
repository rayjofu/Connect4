#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	char **board;
	int *top;
	int rows;
	int cols;
	int turns;
	int match;
	bool wrapAround;
	bool hasWinner(int r, int c);
public:
	Board(int x, int y, int m, bool w);
	~Board();
	void print();
	int move(int c);
	char getTurn();
	int getColumnSize();
	int getMatch();
	bool isValidMove(int c);
	void reset();
};

#endif