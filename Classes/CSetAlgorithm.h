//
//  CSetAlgorithm.h
//  SetGame
//
//  Created by Dowon Yi on 7/27/15.
//
//

#ifndef __SetGame__CSetAlgorithm__
#define __SetGame__CSetAlgorithm__

#include <math.h>
#include <time.h>
#include <memory>
#include <algorithm>
#include <string>

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

#endif /* defined(__SetGame__CSetAlgorithm__) */
