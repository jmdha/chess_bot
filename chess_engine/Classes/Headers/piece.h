#ifndef Piece_H
#define Piece_H

class Board;
class Move;

#include "constants.h"
#include "move.h"
#include "board.h"
#include "point.h"
#include <vector>


class Piece
{

public:
    Color color;
    int x;
    int y;

    Piece(Color color);
    virtual PieceChar getPieceChar();
    virtual std::vector<Move> getPossibleMoves(Board board);
    virtual Move getMoveIfPossible(Board board, Point endPos);
    virtual int getValue();
    virtual int getIndex();
    std::vector<Move> getPossibleMovesInDirection(Board board, Direction direction, int length);
    std::vector<Move> getPossibleMovesInDirection(Board board, Direction direction, int length, bool onlyCapture);
private:
    Point getNewEndPoint(Point priorPos, Direction direction, int moveLength);
    
    
};

#endif