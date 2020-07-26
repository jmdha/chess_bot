#include "Headers/knight.h"

Knight::Knight(Color color) : Piece(color)
{
    this->color = color;
}

PieceChar Knight::getPieceChar()
{
    if (this->color == WHITE)
        return KNIGHTWHITE;
    else
        return KNIGHTBLACK;
}

std::vector<Move> Knight::getPossibleMoves(Board board)
{
    std::vector<Move> moves;

    for (int i = 0; i < 2; i++)
    {
        for (int i2 = -1; i2 <= 1; i2 += 2)
        {
            for (int i3 = -2; i3 <= 2; i3 += 4)
            {
                Point endPoint(this->x, this->y);
                if (i == 0)
                {
                    endPoint.x += i3;
                    endPoint.y += i2;
                }
                else
                {
                    endPoint.x += i2;
                    endPoint.y += i3;
                }

                if (endPoint.x >= WIDTH || endPoint.x < 0 || endPoint.y >= HEIGHT || endPoint.y < 0)
                    continue;
                if (board.isSquareEmpty(endPoint.x, endPoint.y) || board.isSquareEnemy(this->color, endPoint.x, endPoint.y))
                {
                    moves.push_back(Move(this->x, this->y, endPoint.x, endPoint.y));
                }
            }
        }
    }

    return moves;
}

int Knight::getValue() {
    return VALUEKNIGHT + VALUEKNIGHTPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Knight::getIndex() {
    return KNIGHTINDEX;
}