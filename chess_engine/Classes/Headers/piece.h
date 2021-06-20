#ifndef Piece_H
#define Piece_H

class Board;
class Move;

#include "constants.h"
#include "move.h"
#include "board.h"
#include "point.h"
#include "node.h"
#include <vector>


class Piece : Node
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
    virtual bool checkIfPosPossible(Board board, Point pos);
private:
    Point getNewEndPoint(Point priorPos, Direction direction, int moveLength);
    
    
    
};

#endif