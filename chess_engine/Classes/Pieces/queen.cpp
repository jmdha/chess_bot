#include "Headers/queen.h"

Queen::Queen(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar Queen::getPieceChar()
{
    if (this->color == WHITE)
        return QUEENWHITE;
    else
        return QUEENBLACK;
}

std::vector<Move> Queen::getPossibleMoves(Board board)
{
    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    for (int i = 1; i <= 9; i++)
    {
        if (i == 5)
            continue;
        tempMoveList = this->getPossibleMovesInDirection(board, static_cast<Direction>(i), 8);
        moves.insert(it, tempMoveList.begin(), tempMoveList.end());
        it = moves.begin();
    }

    return moves;
}

int Queen::getValue()
{
    return VALUEQUEEN + VALUEQUEENPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Queen::getIndex() {
    return QUEENINDEX;
}