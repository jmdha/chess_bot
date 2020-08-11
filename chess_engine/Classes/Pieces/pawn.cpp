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
    } else if (tempMoveList.size() == 1) {
        if (tempMoveList[0].endY == ((this->color == WHITE) ? static_cast<int>(BACKROWBLACK) : static_cast<int>(BACKROWWHITE))) {
            Move tempMove = tempMoveList[0];
            for (int i = 0; i < 3; i++) {
                Move newMove = Move(tempMove.startX, tempMove.startY, tempMove.endX, tempMove.endY);
                tempMoveList.push_back(newMove);
            }

            for (int i = 0; i < static_cast<int>(tempMoveList.size()); i++) 
                tempMoveList[i].promotion = true;
                
            tempMoveList[0].promotionType = ROOKINDEX;
            tempMoveList[1].promotionType = KNIGHTINDEX;
            tempMoveList[2].promotionType = BISHOPINDEX;
            tempMoveList[3].promotionType = QUEENINDEX;
        }
    }
    moves.insert(it, tempMoveList.begin(), tempMoveList.end());
    it = moves.begin();

    // check capture to the right
    tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHEAST : SOUTHEAST, 1, true);
    if (tempMoveList.size() == 1) {
        if (tempMoveList[0].endY == ((this->color == WHITE) ? static_cast<int>(BACKROWBLACK) : static_cast<int>(BACKROWWHITE))) {
            Move tempMove = tempMoveList[0];
            for (int i = 0; i < 3; i++) {
                Move newMove = Move(tempMove.startX, tempMove.startY, tempMove.endX, tempMove.endY);
                tempMoveList.push_back(newMove);
            }

            for (int i = 0; i < static_cast<int>(tempMoveList.size()); i++) 
                tempMoveList[i].promotion = true;
                
            tempMoveList[0].promotionType = ROOKINDEX;
            tempMoveList[1].promotionType = KNIGHTINDEX;
            tempMoveList[2].promotionType = BISHOPINDEX;
            tempMoveList[3].promotionType = QUEENINDEX;
        }
    }
    moves.insert(it, tempMoveList.begin(), tempMoveList.end());
    it = moves.begin();

    // check capture to the left
    tempMoveList = this->getPossibleMovesInDirection(board, (dir == NORTH) ? NORTHWEST : SOUTHWEST, 1, true);
    if (tempMoveList.size() == 1) {
        if (tempMoveList[0].endY == ((this->color == WHITE) ? static_cast<int>(BACKROWBLACK) : static_cast<int>(BACKROWWHITE))) {
            Move tempMove = tempMoveList[0];
            for (int i = 0; i < 3; i++) {
                Move newMove = Move(tempMove.startX, tempMove.startY, tempMove.endX, tempMove.endY);
                tempMoveList.push_back(newMove);
            }

            for (int i = 0; i < static_cast<int>(tempMoveList.size()); i++) 
                tempMoveList[i].promotion = true;
                
            tempMoveList[0].promotionType = ROOKINDEX;
            tempMoveList[1].promotionType = KNIGHTINDEX;
            tempMoveList[2].promotionType = BISHOPINDEX;
            tempMoveList[3].promotionType = QUEENINDEX;
        }
    }
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