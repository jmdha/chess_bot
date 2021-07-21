#include "Headers/board.h"
#include "Pieces/Headers/pawn.h"
#include "Pieces/Headers/rook.h"
#include "Pieces/Headers/knight.h"
#include "Pieces/Headers/bishop.h"
#include "Pieces/Headers/king.h"
#include "Pieces/Headers/queen.h"
#include <iostream>
#include "Headers/ai.h"

// used for minimax
#include <cstdlib>
#include <time.h>

// used in importFEN
#include <ctype.h>

// used for random moves
#include <chrono>

// used for import of PGN
#include "Headers/utilities.h"

Board::Board()
{
	setStartPos();
}

// assumes correct FEN string
void Board::importFEN(std::string FEN)
{
	clearBoard();
	this->turnNumber = 1;

	// import position

	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		int remainingSquares = WIDTH;
		while (remainingSquares > 0)
		{
			char currentChar = FEN[0];
			if (isdigit(currentChar))
			{
				remainingSquares -= (int)currentChar - 48;
			}
			else
			{
				placePiece(getPieceCharFromChar(currentChar), WIDTH - remainingSquares, y);
				remainingSquares--;
			}
			FEN.erase(0, 1);
		}
		FEN.erase(0, 1);
	}

	this->zobrist->incrementCurrentHash();
	//this->zobrist->initializeHash();

	if (FEN.length() == 0)
		return;
	// import turn
	if (FEN[0] == 'w')
		setTurn(WHITE);
	else
		setTurn(BLACK);
	FEN.erase(0, 2);

	// import king availibity

	// import en-passant

	// import half move

	// import full move
}

std::string Board::getFEN()
{
	std::string FEN = "";

	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		int blankCounter = 0;
		for (int x = 0; x < WIDTH; x++)
		{
			Piece* piece = getPiece(x, y);
			if (piece == NULL)
				blankCounter++;
			else
			{
				if (blankCounter != 0)
					FEN.append(1, blankCounter + '0');
				FEN.append(1, piece->getPieceChar());
				blankCounter = 0;
			}
			if (x == 7 && piece == NULL && blankCounter != 0)
			{
				FEN.append(1, blankCounter + '0');
			}
		}
		if (y != 0)
			FEN.append(1, '/');
	}

	FEN.append(1, ' ');
	if (turn == WHITE)
		FEN.append(1, 'w');
	else
		FEN.append(1, 'b');

	return FEN;
}

void Board::importPGN(std::string moves, bool exportMovePerHash)
{
	this->turnNumber = 1;
	this->zobrist->priorInstanceCount.clear();
	this->zobrist->incrementCurrentHash();
	Move move;
	std::string moveString;
	enPassant = -1;
	bool inComment = false;
	bool nestedComment = false;
	for (int i = 0; i < static_cast<int>(moves.length()); i++)
	{
		if (moves[i] == ' ') {
			// da(you know... like char da -> charda -> charmander? I don't know man) is used for debugging | remove when finished
			if (moves[i + 1] == '{' || moves[i + 1] == '(') {
				if (inComment)
					nestedComment = true;
				else
					inComment = true;
			}

			if (moves[i - 1] == '}' || moves[i - 1] == ')') {
				if (nestedComment)
					nestedComment = false;
				else
					inComment = false;
			}


			if (inComment)
				continue;

			if (moves[i + 1] != '.' && !isNumber(moves[i + 1]) && (moves[i - 1] == '.' || ((isNumber(moves[i - 1]) || moves[i - 1] == 'O' || moves[i - 1] == '+' || moves[i - 1] == '#' || moves[i - 1] == '}' || moves[i - 1] == 'R' || moves[i - 1] == 'N' || moves[i - 1] == 'B' || moves[i - 1] == 'Q'))))
			{

				// get move
				if (!isNumber(moves[i + 2])


					|| (!isLowercase(moves[i + 1]) && isNumber(moves[i + 2])))
				{
					if (moves[i + 1] != 'O')
					{
						// Normal move
						char tempPieceChar = moves[i + 1];
						if (isLowercase(tempPieceChar))
							tempPieceChar = ((turn == WHITE) ? PAWNWHITE : PAWNBLACK);
						else if (turn == BLACK)
							tempPieceChar += 32;
						PieceChar pieceChar = static_cast<PieceChar>(tempPieceChar);
						if (moves[i + 4] != ' ' && moves[i + 4] != '+' && moves[i + 4] != '#' && moves[i + 4] != '?' && moves[i + 4] != '!' && moves.length() != i + 4)
						{
							if (moves[i + 5] == ' ' || moves[i + 5] == '+' || moves[i + 5] == '#' || moves[i + 5] == '?' || moves[i + 5] == '!')
							{
								if (moves[i + 2] == 'x')
								{
									// if pawn take
									if (isLowercase(moves[i + 1]))
										move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 1]));
									else
										move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar);
								}
								else if (isNumber(moves[i + 2])) {
									move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), getRowAsNumber(moves[i + 2]), pieceChar);
								}
								else
									move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 2]));
							}
							else if (isNumber(moves[i + 2]))
							{
								move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 4]), moves[i + 5] - 49), getRowAsNumber(moves[i + 2]), pieceChar);
							}
							else {
								// if pawn-promotion-capture(... a little unwieldly)
								if (moves[i + 5] == '=')
									move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 1]), getPieceIndexFromChar(moves[i + 6]));
								else {
									// this case happens when two pieces of the same type, can capture the same piece
									if (moves[i + 3] == 'x')
										move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 4]), moves[i + 5] - 49), pieceChar, getColumnAsNumber(moves[i + 2]));
									else {
										if (moves[i + 4] == 'x')
											move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 5]), moves[i + 6] - 49), getRowAsNumber(moves[i + 3]), pieceChar, getColumnAsNumber(moves[i + 2]));
										else
											move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 4]), moves[i + 5] - 49), getRowAsNumber(moves[i + 3]), pieceChar, getColumnAsNumber(moves[i + 2]));
									}

								}

							}
						}
						else {
							if (moves[i + 5] == '=')
								move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), getPieceIndexFromChar(moves[i + 6]), pieceChar);
							else
								move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 2]), moves[i + 3] - 49), pieceChar);
						}

					}

					else
					{
						//castle
						int y = ((turn == WHITE) ? BACKROWWHITE : BACKROWBLACK);
						int startX = 4;
						int endX;
						if (moves[i + 4] != '-')
							endX = 6;
						else
							endX = 2;
						move = Move(startX, y, endX, y);
						move.castling = true;
					}
				}
				else
				{
					PieceChar pieceChar = ((turn == WHITE) ? PAWNWHITE : PAWNBLACK);
					// pawn move (not take)
					if (moves[i + 3] == ' ' || moves[i + 3] == '+' || moves[i + 3] == '#' || moves[i + 3] == '?' || moves[i + 3] == '!' || moves.length() <= i + 3) {
						int col = getColumnAsNumber(moves[i + 1]);
						move = getValidMove(*this, Point(col, moves[i + 2] - 49), pieceChar, col);
					}

					// same but with promotion
					else
						move = getValidMove(*this, Point(getColumnAsNumber(moves[i + 1]), moves[i + 2] - 49), getPieceIndexFromChar(moves[i + 4]), pieceChar);
				}

				if (exportMovePerHash)
				{
					// get move as string
					moveString = "";
					int i2 = 1;
					while (moves[i + i2] != ' ' && moves[i + i2] != '+' && moves[i + i2] != '?' && moves[i + i2] != '!')
					{
						moveString += moves[i + i2];
						i2++;
					};
					printf("%lu %s\n", this->zobrist->getHash(), moveString.c_str());
				}

				// commit move
				commitMove(&move);
				if (move.pawnDoubleMove)
					enPassant = move.startX;
				else
					enPassant = -1;
				//printBoard();
				if (isNumber(moves[i + 1]) && (moves[i + 2] == '/' || moves[i + 2] == '-'))
					break;
			}
			else if (isNumber(moves[i + 1])) {
				// if the following is a turn number
				int t = i;
				std::string turnString = "";
				while (isNumber(moves[t += 1])) {
					turnString += moves[t];
				}
				int turnStringAsNumber = atoi(turnString.c_str());
				if (turnStringAsNumber != turnNumber && turnStringAsNumber != turnNumber + 1)
					break;
			}
		}

	}
}

void Board::importFakePGN(std::string moves)
{
	this->turnNumber = 1;
	this->zobrist->priorInstanceCount.clear();
	this->zobrist->incrementCurrentHash();
	std::string move = "";
	for (int i = 0; i < static_cast<int>(moves.length()); i++)
	{
		if (moves[i] != ' ')
		{
			move.push_back(moves[i]);
		}
		if (moves[i] == ' ' || i == static_cast<int>(moves.length()) - 1)
		{
			Move* newMove = new Move(move);
			if (getPiece(newMove->startX, newMove->startY)->getIndex() == KINGINDEX)
				if (move == "e1g1" || move == "e1c1" || move == "e8g8" || move == "e8c8")
					newMove->castling = true;

			// check pawn "stuff"
			if (getPiece(newMove->startX, newMove->startY)->getIndex() == PAWNINDEX) {
				// if promotion
				if (newMove->endY == BACKROWWHITE || newMove->endY == BACKROWBLACK) {
					// if promotion to something else
					PieceIndex type = QUEENINDEX;
					if (move.length() == 5) {
						switch (move[4])
						{
						case 'r':
							type = ROOKINDEX;
							break;
						case 'n':
							type = KNIGHTINDEX;
							break;
						case 'b':
							type = BISHOPINDEX;
							break;
						}
					}
					newMove->promotionType = type;
					newMove->promotion = true;
				}

				// if double move
				else if (abs(newMove->endY - newMove->startY) == 2)
					newMove->pawnDoubleMove = true;
				// en passant take
				else if (newMove->startX != newMove->endX && isSquareEmpty(newMove->endX, newMove->endY))
					newMove->enPassantTake = true;
			}


			commitMove(newMove);
			if (newMove->pawnDoubleMove)
				enPassant = newMove->startX;
			else
				enPassant = -1;
			move = "";
		}
	}
}

void Board::printBoard()
{
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (isSquareEmpty(x, y))
				printf(".");
			else
				printf("%c", getPiece(x, y)->getPieceChar());
		}
		printf("\n");
	}
}

bool Board::isSquareEmpty(int x, int y)
{
	return getPiece(x, y) == NULL;
}

bool Board::isSquareEnemy(Color color, int x, int y)
{
	if (isSquareEmpty(x, y))
		return false;
	return getPiece(x, y)->color == ((color == WHITE) ? BLACK : WHITE);
}

void Board::setStartPos()
{
	clearBoard();
	for (int x = 0; x < WIDTH; x++) {
		placePiece(PAWNBLACK, x, PAWNROWBLACK);
		placePiece(PAWNWHITE, x, PAWNROWWHITE);
	}
	placePiece(ROOKWHITE, 0, BACKROWWHITE);
	placePiece(ROOKWHITE, 7, BACKROWWHITE);
	placePiece(ROOKBLACK, 0, BACKROWBLACK);
	placePiece(ROOKBLACK, 7, BACKROWBLACK);
	placePiece(KNIGHTWHITE, 1, BACKROWWHITE);
	placePiece(KNIGHTWHITE, 6, BACKROWWHITE);
	placePiece(KNIGHTBLACK, 1, BACKROWBLACK);
	placePiece(KNIGHTBLACK, 6, BACKROWBLACK);
	placePiece(BISHOPWHITE, 2, BACKROWWHITE);
	placePiece(BISHOPWHITE, 5, BACKROWWHITE);
	placePiece(BISHOPBLACK, 2, BACKROWBLACK);
	placePiece(BISHOPBLACK, 5, BACKROWBLACK);
	placePiece(KINGWHITE, 4, BACKROWWHITE);
	placePiece(KINGBLACK, 4, BACKROWBLACK);
	placePiece(QUEENWHITE, 3, BACKROWWHITE);
	placePiece(QUEENBLACK, 3, BACKROWBLACK);
	zobrist->incrementCurrentHash();
}

void Board::clearBoard()
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			this->board[x][y] = NULL;
	this->zobrist = new Zobrist(this);
	pieceCount[0] = 0, pieceCount[1] = 0, pieceCount[2] = 0;
	for (int x = 0; x < WIDTH; x++)
		pawnsOnFile[x] = 0;
}

void Board::setTurn(Color turn)
{
	this->turn = turn;
}

void Board::switchTurn()
{
	if (turn == WHITE)
		turn = BLACK;
	else {
		turn = WHITE;
		this->turnNumber++;
	}
}

void Board::placePiece(Piece* piece, int x, int y)
{
	board[x][y] = piece;
	piece->x = x;
	piece->y = y;
	this->zobrist->flipSquare(x, y, piece->getIndex(), static_cast<int>(piece->color));
	pieceCount[0]++;
	pieceCount[1 + piece->color]++;
	if (piece->getIndex() == PAWNINDEX)
		pawnsOnFile[x]++;
	else if (piece->getIndex() == KINGINDEX)
		kingPos[piece->color] = Point(piece->x, piece->y);
}

void Board::placePiece(PieceChar piece, int x, int y)
{
	placePiece(getPieceFromChar(piece), x, y);
}

void Board::removePiece(int x, int y)
{
	Piece* piece = this->getPiece(x, y);

	if (piece != NULL)
	{
		int index = piece->getIndex();
		int color = static_cast<int>(piece->color);
		this->zobrist->flipSquare(x, y, index, color);
		pieceCount[0]--;
		pieceCount[1 + color]--;
		if (piece->getIndex() == PAWNINDEX)
			pawnsOnFile[x]--;
	}

	board[x][y] = NULL;
}

Piece* Board::getPiece(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return nullptr;
	return board[x][y];
}

Piece* Board::getPieceFromChar(PieceChar piece)
{
	switch (piece)
	{
	case PAWNWHITE:
		return new Pawn(WHITE);

	case PAWNBLACK:
		return new Pawn(BLACK);

	case ROOKWHITE:
		return new Rook(WHITE);

	case ROOKBLACK:
		return new Rook(BLACK);

	case KNIGHTWHITE:
		return new Knight(WHITE);

	case KNIGHTBLACK:
		return new Knight(BLACK);

	case BISHOPWHITE:
		return new Bishop(WHITE);

	case BISHOPBLACK:
		return new Bishop(BLACK);

	case QUEENWHITE:
		return new Queen(WHITE);

	case QUEENBLACK:
		return new Queen(BLACK);

	case KINGWHITE:
		return new King(WHITE);

	case KINGBLACK:
		return new King(BLACK);

	default:
		throw std::invalid_argument("Invalid direction " + (int)piece);
	}
}

PieceChar Board::getPieceCharFromChar(char piece)
{
	switch (piece)
	{
	case 'P':
		return PAWNWHITE;

	case 'p':
		return PAWNBLACK;

	case 'R':
		return ROOKWHITE;

	case 'r':
		return ROOKBLACK;

	case 'N':
		return KNIGHTWHITE;

	case 'n':
		return KNIGHTBLACK;

	case 'B':
		return BISHOPWHITE;

	case 'b':
		return BISHOPBLACK;

	case 'Q':
		return QUEENWHITE;

	case 'q':
		return QUEENBLACK;

	case 'K':
		return KINGWHITE;

	case 'k':
		return KINGBLACK;

	default:
		return BLANK;
	}
}

PieceIndex Board::getPieceIndexFromChar(char piece)
{
	switch (piece)
	{
	case 'P':
	case 'p':
		return PAWNINDEX;

	case 'R':
	case 'r':
		return ROOKINDEX;

	case 'N':
	case 'n':
		return KNIGHTINDEX;

	case 'B':
	case 'b':
		return BISHOPINDEX;

	case 'Q':
	case 'q':
		return QUEENINDEX;

	case 'K':
	case 'k':
		return KINGINDEX;

	default:
		return NONEINDEX;
	}
}

int Board::GetPieceCount() {
	int count = 0;
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			if (!isSquareEmpty(x, y))
				count++;
		}
	}
	return count;
}


void Board::commitMove(Move* move)
{
	doMove(move);
	switchTurn();
}

// assumed valid move
void Board::doMove(Move* move)
{
	move->setTarget(getPiece(move->endX, move->endY));
	// Used for hashing
	if (move->target != NULL)
	{
		removePiece(move->endX, move->endY);
		PieceChar capturedPiece = move->target->getPieceChar();

		if (capturedPiece == KINGWHITE)
			kingAlive[WHITE] = false;
		else if (capturedPiece == KINGBLACK)
			kingAlive[BLACK] = false;
	}
	Piece* piece = getPiece(move->startX, move->startY);
	if (piece->getIndex() == KINGINDEX)
	{
		int side = static_cast<int>(piece->color);

		for (int i = 0; i < 2; i++) {
			if (castlingValid[side][i]) {
				move->disallowedCastling[i] = true;
				castlingValid[side][i] = false;
			}
		}

		if (move->castling)
		{
			int rookStartX;
			int rookEndX;
			if (move->endX == 2)
			{
				rookStartX = 0;
				rookEndX = 3;
			}
			else
			{
				rookStartX = 7;
				rookEndX = 5;
			}

			if (getPiece(rookStartX, piece->y) == NULL)
				move->castling = false;
			else
				doMove(new Move(rookStartX, piece->y, rookEndX, piece->y));


		}
	}
	else if (piece->getIndex() == ROOKINDEX)
	{
		int side = static_cast<int>(piece->color);
		if (piece->x == 0 && castlingValid[side][0]) {
			move->disallowedCastling[0] = true;
			castlingValid[side][0] = false;
		}

		else if (piece->x == 7 && castlingValid[side][1]) {
			move->disallowedCastling[1] = true;
			castlingValid[side][1] = false;
		}
	}
	else if (piece->getIndex() == PAWNINDEX)
	{
		if (move->promotion)
		{
			switch (move->promotionType) {
			case ROOKINDEX:
				piece = new Rook(piece->color);
				break;
			case KNIGHTINDEX:
				piece = new Knight(piece->color);
				break;
			case BISHOPINDEX:
				piece = new Bishop(piece->color);
				break;
			case QUEENINDEX:
			default:
				piece = new Queen(piece->color);
				break;
			}
			piece->x = move->endX;
			piece->y = move->endY;
		}
		else if (move->enPassantTake) {
			int passedPawnYPosition = ((piece->color == WHITE) ? 4 : 3);
			move->setTarget(getPiece(move->endX, passedPawnYPosition));
			removePiece(move->endX, passedPawnYPosition);
		}

		move->priorEnPassant = enPassant;

		if (move->pawnDoubleMove)
			enPassant = move->startX;
		else
			enPassant = -1;
	}

	if (!piece->hasMoved) {
		piece->hasMoved = true;
		move->firstMove = true;
	}

	removePiece(move->startX, move->startY);
	placePiece(piece, move->endX, move->endY);
	this->zobrist->incrementCurrentHash();
}

// assumes valid move
void Board::undoMove(Move* move)
{
	this->zobrist->decrementCurrentHash();
	Piece* piece = getPiece(move->endX, move->endY);

	int side = static_cast<int>(piece->color);
	for (int i = 0; i < 2; i++)
		if (move->disallowedCastling[i])
			castlingValid[side][i] = true;

	if (move->firstMove)
		piece->hasMoved = false;

	if (move->promotion)
	{
		piece = new Pawn(piece->color);
		piece->x = move->startX;
		piece->y = move->startX;
	}
	removePiece(move->endX, move->endY);
	placePiece(piece, move->startX, move->startY);
	if (move->target != NULL)
	{
		placePiece(move->target, move->target->x, move->target->y);
		move->setTarget(NULL);
		for (int i = 0; i < 2; i++)
			kingAlive[i] = true;
	}
	else if (move->castling)
	{
		int rookStartX;
		int rookEndX;
		if (move->endX == 2)
		{
			rookStartX = 0;
			rookEndX = 3;
		}
		else
		{
			rookStartX = 7;
			rookEndX = 5;
		}

		undoMove(new Move(rookStartX, piece->y, rookEndX, piece->y));
	}
	enPassant = move->priorEnPassant;
}

bool Board::isKingVulnerable(Color side) {
	// See if enemy can attack
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (isSquareEnemy(side, x, y))
			{
				if (getPiece(x, y)->checkIfPosPossible(*(this), kingPos[side]))
					return true;
			}
		}
	}

	return false;
}


int Board::evaluateBoard()
{
	return evaluateBoard(this->turn);
}

int Board::evaluateBoard(Color side)
{
	int value = 0;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!isSquareEmpty(x, y))
			{
				Piece* piece = getPiece(x, y);
				int multiplier = ((piece->color == side) ? 1 : -1);
				value += piece->getValue() * multiplier;
			}
		}
	}

	return value;
}