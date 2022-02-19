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

// used for random taking move
#include <algorithm>
#include <random>



class Board {
public:
	int turnNumber = 0;
	bool kingAlive[2] = {true, true};
	Point kingPos[2] = {Point(0, 0), Point(0,0)};
	bool castlingValid[2][2] = {{true, true}, {true, true}};
	// First number is total, second is white, then black
	int pieceCount[3] = {32, 16, 16};
	int pawnsOnFile[8] = {2};
	Zobrist* zobrist;
	int enPassant;
	Color turn = Color::White;
	Color startTurn;

	Board();

	void setStartPos();
	void clearBoard();
	void importFEN(std::string FEN);
	void importPGN(std::string moves, bool exportMovePerHash);
	void importFakePGN(std::string moves);
	void printBoard();
	bool isSquareEmpty(int x, int y);
	bool isSquareEnemy(Color color, int x, int y);
	Piece* getPiece(int x, int y);
	int evaluateBoard();
	int evaluateBoard(Color side);
	int GetPieceCount();
	void commitMove(Move* move);
	void doMove(Move* move);
	void switchTurn();
	std::string getFEN();
	void undoMove(Move* move);
	bool isKingVulnerable(Color side);

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