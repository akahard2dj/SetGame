//
//  CSetAlgorithm.cpp
//  SetGame
//
//  Created by Dowon Yi on 7/27/15.
//
//

#include "CSetAlgorithm.h"

#define DEBUG	1

CSetGame* CSetGame::createSetGame(int _numRow, int _colNum)
{
    CSetGame* p = new CSetGame(_numRow, _colNum);
    
    return p;
}

CSetGame::CSetGame()
{
    
}

CSetGame::CSetGame(int _rowNum, int _colNum)
{
    //Initialization of Random Class
    unsigned long init[4] = { (unsigned)time(NULL), (unsigned)time(NULL), (unsigned)time(NULL), (unsigned)time(NULL) };
    random = Random::createRandom(init, 4);
    
    rowNum = _rowNum;
    colNum = _colNum;
    
    m_pBoardArray = new int[rowNum*colNum];
    memset(m_pBoardArray, 0, sizeof(int)*rowNum*colNum);
    
    designBoardArray();
    if (DEBUG)
        printArray();
}

CSetGame::~CSetGame()
{
    delete[] m_pBoardArray;
}

void CSetGame::designBoardArray()
{
    m_pBoardArray[0] = random->getUniformRandomAB(0, NUM_SHAPE*NUM_COLOR*NUM_BACKCOL-1);
    int count = 1;
    while (count < rowNum*colNum) {
        int mFlag = 1;
        int number;
        number = random->getUniformRandomAB(0, NUM_SHAPE*NUM_COLOR*NUM_BACKCOL-1);
        for (int i = 0; i < count; i++)
            if (m_pBoardArray[i] == number)
                mFlag = 0;
        if (mFlag) {
            m_pBoardArray[count] = number;
            count++;
        }
    }
}

void CSetGame::shuffleBoard()
{
    designBoardArray();
}

bool CSetGame::isSet(int* answer)
{
    int bitCard1[3], bitCard2[3], bitCard3[3];
    getTernary(answer[0], bitCard1);
    getTernary(answer[1], bitCard2);
    getTernary(answer[2], bitCard3);
    
    printf("<< %d %d %d\n", answer[0], answer[1], answer[2]);
    printf("<<%d%d%d, %d%d%d, %d%d%d\n", bitCard1[0], bitCard1[1], bitCard1[2],
           bitCard2[0], bitCard2[1], bitCard2[2],
           bitCard3[0], bitCard3[1], bitCard3[2] );
    
    int sumBit[3];
    for (int i = 0; i < 3; i++)
        sumBit[i] = bitCard1[i] + bitCard2[i] + bitCard3[i];
    
    if (DEBUG) {
        printf("%d %d%d%d\n", answer[0], bitCard1[0], bitCard1[1], bitCard1[2]);
        printf("%d %d%d%d\n", answer[1], bitCard2[0], bitCard2[1], bitCard2[2]);
        printf("%d %d%d%d\n", answer[2], bitCard3[0], bitCard3[1], bitCard3[2]);
        printf("%d %d %d\n", sumBit[0], sumBit[1], sumBit[2]);
    }
    
    if ((sumBit[0] % 3 == 0) && (sumBit[1] % 3 == 0) && sumBit[2] % 3 == 0) {
        return true;
    }
    else {
        return false;
    }
    
}

bool CSetGame::isBoardSolution()
{
    std::string bitmask(3, 1);
    bitmask.resize(9, 0);
    int checkList[84][3];
    int checkListIdx[84][3];
    int idx = 0;
    
    do {
        int cnt = 0;
        for (int i = 0; i < 9; ++i) {
            if (bitmask[i]) {
                //	std::cout << " " << i;
                checkList[idx][cnt] = i;
                cnt = cnt + 1;
            }
        }
        idx = idx + 1;
        
        //std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    
    for (int i = 0; i < 84; i++) {
        checkListIdx[i][0] = m_pBoardArray[checkList[i][0]];
        checkListIdx[i][1] = m_pBoardArray[checkList[i][1]];
        checkListIdx[i][2] = m_pBoardArray[checkList[i][2]];
    }
    
    int numTotalSets = 0;
    for (int i = 0; i < 84; i++) {
        bool bCheck = isSet(checkListIdx[i]);
        if (bCheck) {
            numTotalSets += 1;
        }
    }
    
    m_numTotalSolution = numTotalSets;
    printf("## Total Solution : %d \n", numTotalSets);
    
    if (numTotalSets == 0) {
        return false;
    }
    else {
        return true;
    }
}

int* CSetGame::getBoard()
{
    return m_pBoardArray;
}

void CSetGame::getTernary(int num, int* output)
{
    int remainder;
    int nextNum;
    printf("getTernary<< %d\n", num);
    nextNum = num / 3;
    remainder = num % 3;
    output[0] = remainder;
    
    remainder = nextNum % 3;
    nextNum = nextNum / 3;
    output[1] = remainder;
    
    remainder = nextNum % 3;
    output[2] = remainder;
}

void CSetGame::printArray()
{
    int idx;
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum; j++) {
            idx = rowNum * i + j;
            printf("%d\t ", m_pBoardArray[idx]);
        }
        printf("\n");
    }
}
