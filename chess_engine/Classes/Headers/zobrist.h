#ifndef Zobrist_H
#define Zobrist_H

class Board;

#include <unordered_map>
#include "constants.h"
#include "board.h"

class Zobrist
{

public:
    std::unordered_map<unsigned long int, int> priorInstanceCount;
    Zobrist(Board *board);
    unsigned long int getHash();
    void initializeHash();
    void flipSquare(int x, int y, int index, int color);
    void incrementCurrentHash();
    void decrementCurrentHash();
    

private:
    unsigned long int valueBoard[WIDTH][HEIGHT][6][2] = {0};
    unsigned long int currentHash;
    Board *board;

    
};

#endif