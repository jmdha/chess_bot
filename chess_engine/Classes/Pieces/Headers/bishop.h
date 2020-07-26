#ifndef Bishop_H
#define Bishop_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class Bishop : public Piece
{
public:
    Bishop(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    int getValue();
    int getIndex();

private:
};

#endif