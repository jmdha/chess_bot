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
    int getValue();
    int getIndex();

private:
};

#endif