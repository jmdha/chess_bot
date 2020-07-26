#ifndef Queen_H
#define Queen_H

#include "../../Headers/piece.h"
#include "../../Headers/move.h"

class Queen : public Piece
{
public:
    Queen(Color color);
    PieceChar getPieceChar();
    std::vector<Move> getPossibleMoves(Board board);
    int getValue();
    int getIndex();

private:
};

#endif