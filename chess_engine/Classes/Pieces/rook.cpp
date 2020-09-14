#include "Headers/rook.h"

Rook::Rook(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar Rook::getPieceChar()
{
    if (this->color == WHITE)
        return ROOKWHITE;
    else
        return ROOKBLACK;
}

std::vector<Move> Rook::getPossibleMoves(Board board)
{
    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    for (int i = 0; i < 4; i++)
    {

        Direction dir = WEST;
        switch (i)
        {
        case 0:
            dir = NORTH;
            break;

        case 1:
            dir = EAST;
            break;

        case 2:
            dir = SOUTH;
            break;
        }
        tempMoveList = this->getPossibleMovesInDirection(board, dir, 8);
        moves.insert(it, tempMoveList.begin(), tempMoveList.end());
        it = moves.begin();
    }

    return moves;
}

// does not check for castling
Move Rook::getMoveIfPossible(Board board, Point endPos)
{
    std::vector<Move> moves;

    for (int i = 0; i < 4; i++)
    {

        Direction dir = WEST;
        switch (i)
        {
        case 0:
            dir = NORTH;
            break;

        case 1:
            dir = EAST;
            break;

        case 2:
            dir = SOUTH;
            break;
        }
        moves = this->getPossibleMovesInDirection(board, dir, 8);
        for (int i = 0; i < static_cast<int>(moves.size()); i++) {
            if (moves[i].endX == endPos.x && moves[i].endY == endPos.y)
                return moves[i];
        }
    }

    return Move(-1, -1, -1, -1);
}

int Rook::getValue()
{
    return VALUEROOK + VALUEROOKPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Rook::getIndex() {
    return ROOKINDEX;
}