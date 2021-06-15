// Contains base stuff an ai needs e.g generating possible moves and such
#include "Headers/ai.h"
#include <iostream>


Move getValidMove(Board board, Point endPos, PieceIndex promotionType, PieceChar pieceChar)
{
	std::vector<Move> moves = getAllMovesOfPieceChar(board, pieceChar);
	for (int i = 0; i < static_cast<int>(moves.size()); i++)
	{
		Piece* piece = board.getPiece(moves[i].startX, moves[i].startY);
		if (piece->color == board.turn && moves[i].startX == endPos.x && moves[i].endX == endPos.x && moves[i].endY == endPos.y && moves[i].promotionType == promotionType)
		{
			return moves[i];
		}
	}
	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar)
{
	Move move;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar)
			{
				move = board.getPiece(x, y)->getMoveIfPossible(board, endPos);
				if (move.endX != -1 && move.endY != -1)
					return move;
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column)
{
	Move move;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == column)
			{
				move = board.getPiece(x, y)->getMoveIfPossible(board, endPos);
				if (move.endX != -1 && move.endY != -1)
					return move;
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column, PieceIndex promotionType)
{
	std::vector<Move> moves;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == column)
			{
				moves = board.getPiece(x, y)->getPossibleMoves(board);
				for (int i = 0; i < static_cast<int>(moves.size()); i++) {
					if (moves[i].endX == endPos.x && moves[i].endY == endPos.y && moves[i].promotionType == promotionType)
						return moves[i];
				}
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar)
{
	Move move;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && y == row)
			{
				move = board.getPiece(x, y)->getMoveIfPossible(board, endPos);
				if (move.endX != -1 && move.endY != -1)
					return move;
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar, int column)
{
	Move move;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && y == row && x == column)
			{
				move = board.getPiece(x, y)->getMoveIfPossible(board, endPos);
				if (move.endX != -1 && move.endY != -1)
					return move;
			}
		}
	}
	throw std::invalid_argument("Found no move");
}

std::vector<Move> getAllMoves(Board board, Color side)
{

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->color == side)
			{
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar)
{

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar)
			{
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol)
{

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == startCol)
			{
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, int startRow, PieceChar pieceChar)
{

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && y == startRow)
			{
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol, int startRow)
{

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == startCol && y == startRow)
			{
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

Move getBestMove(Board* board, int depth)
{
	// If seen at -1 without knowing why, return to 0
	// -1 is used for debugging
	int totalMovesChecked = -1;
	Move move = minimax(board, depth, true, board->turn, -VALUEINFINITE, VALUEINFINITE, false, &totalMovesChecked);
	return move;
}



Move minimax(Board* board, int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int* totalMoves)
{
	(*totalMoves) += 1;
	Move bestMove;
	Color oppositeColor = ((currentTurn == WHITE) ? BLACK : WHITE);

	// check if the position has occured more than 2 times
	if (board->zobrist->priorInstanceCount.at(board->zobrist->getHash()) > 2)
	{
		int multiplier = ((currentTurn == board->turn) ? 1 : -1);
		bestMove.value = VALUEDRAW * multiplier;
		return bestMove;
	}

	if (isMax)
		bestMove.value = -VALUEINFINITE;
	else
		bestMove.value = VALUEINFINITE;
	if (depth == 0 || !board->kingAlive[currentTurn] || !board->kingAlive[oppositeColor])
	{
		bestMove.value = board->evaluateBoard(board->turn);
		return bestMove;
	}




	std::vector<Move> moves = getAllMoves(*board, currentTurn);

	for (int i = 0; i < static_cast<int>(moves.size()); i++)
		moves[i].moveSizeBatch = static_cast<int>(moves.size());


	if (static_cast<int>(moves.size()) == 0)
	{
		int multiplier = ((currentTurn == board->turn) ? 1 : -1);
		bestMove.value = VALUEDRAW;
		return bestMove;
	}
	for (int i = 0; i < static_cast<int>(moves.size()); i++)
	{
		Move move;
		bool castlingLegality[2][2] = { { false, false }, { false, false } };
		for (int j = 0; j < 2; j++)
			for (int j2 = 0; j2 < 2; j2++)
				castlingLegality[j][j2] = board->castlingValid[j][j2];


		//board->printBoard();
		//printf("\n");

		unsigned long int tempHash1 = board->zobrist->getHash();

		board->doMove(&(moves[i]));

		unsigned long int tempHash2 = board->zobrist->getHash();

		// get enpassant
		if (moves[i].pawnDoubleMove)
			board->enPassant = moves[i].startX;
		else
			board->enPassant = -1;

		// Go deeper
		if (depth == 1 && !doingHE && moves[i].target != NULL)
			move = minimax(board, 3, !isMax, oppositeColor, a, b, true, totalMoves);
		else {
			if (doingHE && moves[i].target == NULL)
				move = minimax(board, 0, !isMax, oppositeColor, a, b, doingHE, totalMoves);
			else
				move = minimax(board, depth - 1, !isMax, oppositeColor, a, b, doingHE, totalMoves);
		}

		unsigned long int tempHash3 = board->zobrist->getHash();

		board->undoMove(&(moves[i]));

		for (int j = 0; j < 2; j++)
			for (int j2 = 0; j2 < 2; j2++)
				board->castlingValid[j][j2] = castlingLegality[j][j2];
		// get enpassant


		if (isMax && move.value > bestMove.value)
		{
			bestMove = moves[i];
			bestMove.value = move.value;
		}
		else if (!isMax && move.value < bestMove.value)
		{
			bestMove = moves[i];
			bestMove.value = move.value;
		}


		if (isMax) {
			a = std::max(move.value, a);
			if (a >= b)
				break;
		}
		else {
			b = std::min(move.value, b);
			if (b <= a)
				break;
		}




	}
	bestMove.totalMoves = *totalMoves;
	return bestMove;
}