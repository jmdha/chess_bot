#ifndef Board_H
#define Board_H

class Zobrist;
class Piece;
class Bishop;
class King;
class Knight;
class Pawn;
class Queen;
class Rook;
class Move;

#include <string>
#include <vector>
#include "piece.h"
#include "constants.h"
#include "move.h"
#include "zobrist.h"
#include "point.h"
#include "database.h"

// used for random taking move
#include <algorithm>
#include <random>



class Board
{
public:
	int turnNumber = 0;
	bool kingAlive[2] = { true, true };
	bool castlingValid[2][2] = { {true, true}, {true, true} };
	Zobrist* zobrist;
	int enPassant;
	Color turn = WHITE;

	Board();
	Board(Color turn);

	void setStartPos();
	void clearBoard();
	void importFEN(std::string FEN);
	void importPGN(std::string moves, bool exportMovePerHash, Database* database);
	void importFakePGN(std::string moves);
	void printBoard();
	bool isSquareEmpty(int x, int y);
	bool isSquareEnemy(Color color, int x, int y);
	void placePiece(Piece* piece);
	Piece* getPiece(int x, int y);
	int evaluateBoard();
	int evaluateBoard(Color side);

	void commitMove(Move* move);
	void doMove(Move* move);
	void switchTurn();
	std::string getFEN();
	void undoMove(Move* move);

private:
	Piece* board[WIDTH][HEIGHT];



	void setTurn(Color turn);

	void placePiece(Piece* piece, int x, int y);
	void placePiece(PieceChar piece, int x, int y);
	void removePiece(int x, int y);



	Piece* getPieceFromChar(PieceChar piece);
	PieceChar getPieceCharFromChar(char piece);
	PieceIndex getPieceIndexFromChar(char piece);

};

#endif