#include "Headers/king.h"

King::King(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar King::getPieceChar()
{
    if (this->color == WHITE)
        return KINGWHITE;
    else
        return KINGBLACK;
}

std::vector<Move> King::getPossibleMoves(Board board)
{
    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    for (int i = 1; i <= 9; i++)
    {
        if (i == 5)
            continue;
        tempMoveList = this->getPossibleMovesInDirection(board, static_cast<Direction>(i), 1);
        moves.insert(it, tempMoveList.begin(), tempMoveList.end());
        it = moves.begin();
    }

    if (board.castlingValid[this->color][0]) {
        bool valid = true;
        for (int i = this->x - 1; i > 0; i--) {
            if (board.getPiece(i, this->y) != NULL) {
                valid = false;
                break;
            }
        }
        if (valid) {
            Move move = Move(this->x, this->y, 2, this->y);
            move.castling = true;
            moves.push_back(move);
        }
    }
    if (board.castlingValid[this->color][1]) {
        bool valid = true;
        for (int i = this->x + 1; i < 7; i++) {
            if (board.getPiece(i, this->y) != NULL) {
                valid = false;
                break;
            }
        }
        if (valid) {
            Move move = Move(this->x, this->y, 6, this->y);
            move.castling = true;
            moves.push_back(move);
        }
    }

    return moves;
}

int King::getValue()
{
    return VALUEMATE + VALUEKINGPOSMID[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int King::getIndex() {
    return KINGINDEX;
}