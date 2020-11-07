#ifndef Pawn_H
#define Pawn_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class Pawn : public Piece
{
public:
    Pawn(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    Move getMoveIfPossible(Board board, Point endPos);
    int getValue();
    int getIndex();
    bool checkIfPosPossible(Board board, Point pos);

private:
    
};

#endif