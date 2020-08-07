#include "Headers/pawn.h"

Pawn::Pawn(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar Pawn::getPieceChar()
{
    if (this->color == WHITE)
        return PAWNWHITE;
    else
        return PAWNBLACK;
}

std::vector<Move> Pawn::getPossibleMoves(Board board)
{
    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    Direction dir = (this->color == WHITE) ? NORTH : SOUTH;

    // check move
    int moveLength = 1;
    if (this->color == WHITE && this->y == PAWNROWWHITE)
        moveLength = 2;
    else if (this->color == BLACK && this->y == PAWNROWBLACK)
        moveLength = 2;

    tempMoveList = this->getPossibleMovesInDirection(board, dir, moveLength, false);
    // look if there are two moves i.e. it can both move one square forth and two
    if (tempMoveList.size() == 2) {
        tempMoveList[1].pawnDoubleMove = true;
    }
    moves.insert(it, tempMoveList.begin(), tempMoveList.end());
    it = moves.begin();

    // check capture to the right
    tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHEAST : SOUTHEAST, 1, true);
    moves.insert(it, tempMoveList.begin(), tempMoveList.end());
    it = moves.begin();

    // check capture to the left
    tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHWEST : SOUTHWEST, 1, true);
    moves.insert(it, tempMoveList.begin(), tempMoveList.end());
    it = moves.begin();

    // get en passant move
    if (board.enPassant != -1) {
        if (board.enPassant == x - 1) {
            tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHWEST : SOUTHWEST, 1, false);
            if (tempMoveList.size() == 1)
                tempMoveList[0].enPassantTake = true;
            moves.insert(it, tempMoveList.begin(), tempMoveList.end());
            it = moves.begin();
        }
        else if (board.enPassant == x + 1) {
            tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHEAST : SOUTHEAST, 1, false);
            if (tempMoveList.size() == 1)
                tempMoveList[0].enPassantTake = true;
            moves.insert(it, tempMoveList.begin(), tempMoveList.end());
            it = moves.begin();
        }
    }
    return moves;
}

int Pawn::getValue() {
    return VALUEPAWN + VALUEPAWNPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Pawn::getIndex() {
    return PAWNINDEX;
}