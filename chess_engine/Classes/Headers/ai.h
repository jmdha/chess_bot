#ifndef Ai_H
#define Ai_H

#include "move.h"
#include "point.h"
#include "board.h"
#include <vector>

Move getValidMove(Board board, Point endPos);
Move getValidMove(Board board, Point endPos, PieceIndex promotionType);
Move getValidMove(Board board, Point endPos, char pieceChar);
Move getValidMove(Board board, Point endPos, char pieceChar, int column);
Move getValidMove(Board board, Point endPos, char pieceChar, int column, PieceIndex promotionType);
Move getValidMove(Board board, Point endPos, int row, char pieceChar);
Move getValidMove(Board board, Point endPos, int row, char pieceChar, int column);
std::vector<Move> getAllMoves(Board board, Color side);

Move minimax(Board *board, int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int *totalMoves);
Move getBestMove(Board * board, int depth);

#endif