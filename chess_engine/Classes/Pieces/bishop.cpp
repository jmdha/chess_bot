#include "Headers/bishop.h"

Bishop::Bishop(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar Bishop::getPieceChar()
{
    if (this->color == WHITE)
        return BISHOPWHITE;
    else
        return BISHOPBLACK;
}

std::vector<Move> Bishop::getPossibleMoves(Board board) {
    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    for (int i = 0; i < 4; i++)
    {
        
        Direction dir = NORTHWEST;
        switch (i)
        {
        case 0:
            dir = NORTHEAST;
            break;

        case 1:
            dir = SOUTHWEST;
            break;

        case 2:
            dir = SOUTHEAST;
            break;
        }
        tempMoveList = this->getPossibleMovesInDirection(board, dir, 8);
        moves.insert(it, tempMoveList.begin(), tempMoveList.end());
        it = moves.begin();
    }


    return moves;
}

int Bishop::getValue() {
    return VALUEBISHOP + VALUEBISHOPPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Bishop::getIndex() {
    return BISHOPINDEX;
}