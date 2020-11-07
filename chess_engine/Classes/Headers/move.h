#ifndef Move_H
#define Move_H

class Piece;

#include <string>
#include "piece.h"



class Move
{

public:
    int startX;
    int startY;
    int endX;
    int endY;
    int value = 0;
    Piece *target;
    bool castling = false;
    bool promotion = false;
    PieceIndex promotionType;
    bool pawnDoubleMove = false;
    bool enPassantTake = false;
    Move();
    Move(int startX, int startY, int endX, int endY);
    Move(std::string move);
    std::string getMoveAsString();
    std::string getMoveAsPlainString();
    void setTarget(Piece *target);
private:
};

#endif