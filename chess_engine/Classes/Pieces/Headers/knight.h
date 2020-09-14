#ifndef Knight_H
#define Knight_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class Knight : public Piece
{
public:
    Knight(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    Move getMoveIfPossible(Board board, Point endPos);
    int getValue();
    int getIndex();

private:
};

#endif