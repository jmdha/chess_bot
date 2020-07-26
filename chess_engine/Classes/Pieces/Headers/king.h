#ifndef King_H
#define King_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class King : public Piece
{
public:
    King(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    int getValue();
    int getIndex();

private:
};

#endif