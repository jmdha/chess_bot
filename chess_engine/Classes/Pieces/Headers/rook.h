#ifndef Rook_H
#define Rook_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class Rook : public Piece
{
public:
    Rook(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    Move getMoveIfPossible(Board board, Point endPos);
    int getValue();
    int getIndex();
    bool checkIfPosPossible(Board board, Point pos);

private:
    
};

#endif