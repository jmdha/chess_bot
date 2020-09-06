#ifndef Ai_H
#define Ai_H

#include "move.h"
#include "point.h"
#include "board.h"
#include <vector>
#include "constants.h"

Move getValidMove(Board board, Point endPos, PieceIndex promotionType, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column, PieceIndex promotionType);
Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar, int column);
std::vector<Move> getAllMoves(Board board, Color side);
std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar);

Move minimax(Board *board, int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int *totalMoves);
Move getBestMove(Board * board, int depth);

#endif