#ifndef Ai_H
#define Ai_H

#include <vector>
#include <chrono>
#include <math.h>

#include "move.h"
#include "point.h"
#include "board.h"
#include "constants.h"

Move getValidMove(Board board, Point endPos, PieceIndex promotionType, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column);
Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column, PieceIndex promotionType);
Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar);
Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar, int column);
std::vector<Move> getAllMoves(Board board, Color side);
std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar);
std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol);
std::vector<Move> getAllMovesOfPieceChar(Board board, int startRow, PieceChar pieceChar);
std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol, int startRow);

Move getBestMove(Board* board, int maxTime);
Move generateMove(Board* board, int depth, int& totalMoves);
Move minimax(Board* board, int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int* totalMoves, int accDepth);

#endif