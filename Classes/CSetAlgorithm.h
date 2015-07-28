#ifndef SetGame_H
#define SetGame_H

#include <math.h>
#include <time.h>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

#include "CRandom.h"

#define NUM_SHAPE	3
#define NUM_COLOR	3
#define NUM_BACKCOL	3

class CSetGame
{
public:
	CSetGame();
	CSetGame(int _rowNum, int _colNum);
	~CSetGame();

public:
	static CSetGame* createSetGame(int _rowNum, int _colNum);	
	bool isSet(int* answer);
	bool isBoardSolution();
	void shuffleBoard();
	int* getBoard();
	void setBoard(int* input);
	void redesignBoard();
private:
	void designBoardArray();
	void getTernary(int number, int* ternay);


public:
	Random* random;
	int rowNum, colNum;
	int *m_pBoardArray;
	int m_numTotalSolution;

private:
	void printArray();
	
};

#endif
