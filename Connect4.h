#ifndef CONNECT4_H
#define CONNECT4_H
#include "Board.h"

class Connect4 {
private:
	const int colMin = 7;
	const int colMax = 10;
	const int rowMin = 6;
	const int rowMax = 10;
	const int matchMin = 4;
	const int matchMax = 6;
	Board *board;
	void setup();
	bool isBetween(int n, int min, int max);
	void start();
public:
	Connect4();
	Connect4(int cols, int rows, int match, bool wrapAround);
	~Connect4();
	
};

#endif