// Contains base stuff an ai needs e.g generating possible moves and such
#include "Headers/ai.h"
#include <iostream>
#include <algorithm>
#include <random>


Move getValidMove(Board board, Point endPos, PieceIndex promotionType, PieceChar pieceChar) {
	std::vector<Move> moves = getAllMovesOfPieceChar(board, pieceChar);
	for(int i = 0; i < (int) moves.size(); i++) {
		Piece* piece = board.getPiece(moves[i].startX, moves[i].startY);
		if(piece->color == board.turn && moves[i].startX == endPos.x && moves[i].endX == endPos.x && moves[i].endY == endPos.y && moves[i].promotionType == promotionType) {
			bool valid = false;
			board.doMove(&moves[i]);
			if(!board.isKingVulnerable(piece->color))
				valid = true;
			board.undoMove(&moves[i]);
			if(valid)
				return moves[i];
		}
	}
	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar) {
	Move move;
	int amountOfMatchingPieces = 0;
	Piece* matchingPieces[8] = {nullptr};
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar) {
				matchingPieces[amountOfMatchingPieces] = board.getPiece(x, y);
				amountOfMatchingPieces++;
			}
		}
	}

	// if multiple pieces can move to end square, take the one that hasn't moved
	for(int i = 0; i < amountOfMatchingPieces; i++) {
		if(!matchingPieces[i]->hasMoved) {
			move = matchingPieces[i]->getMoveIfPossible(board, endPos);
			if(move.endX != -1 && move.endY != -1) {
				bool valid = false;
				board.doMove(&move);
				if(!board.isKingVulnerable(matchingPieces[i]->color))
					valid = true;
				board.undoMove(&move);
				if(valid)
					return move;
			}
		}
	}
	for(int i = 0; i < amountOfMatchingPieces; i++) {
		if(matchingPieces[i]->hasMoved) {
			move = matchingPieces[i]->getMoveIfPossible(board, endPos);
			if(move.endX != -1 && move.endY != -1) {
				bool valid = false;
				board.doMove(&move);
				if(!board.isKingVulnerable(matchingPieces[i]->color))
					valid = true;
				board.undoMove(&move);
				if(valid)
					return move;
			}
		}
	}


	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column) {
	Move move;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y)) {
				Piece* piece = board.getPiece(x, y);
				if(piece->getPieceChar() == pieceChar && x == column) {
					move = piece->getMoveIfPossible(board, endPos);
					if(move.endX != -1 && move.endY != -1) {
						bool valid = false;
						board.doMove(&move);
						if(!board.isKingVulnerable(piece->color))
							valid = true;
						board.undoMove(&move);
						if(valid)
							return move;
					}
				}
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, PieceChar pieceChar, int column, PieceIndex promotionType) {
	std::vector<Move> moves;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y)) {
				Piece* piece = board.getPiece(x, y);
				if(piece->getPieceChar() == pieceChar && x == column) {
					moves = piece->getPossibleMoves(board);
					for(int i = 0; i < (int) moves.size(); i++) {
						if(moves[i].endX == endPos.x && moves[i].endY == endPos.y && moves[i].promotionType == promotionType) {
							bool valid = false;
							board.doMove(&moves[i]);
							if(!board.isKingVulnerable(piece->color))
								valid = true;
							board.undoMove(&moves[i]);
							if(valid)
								return moves[i];
						}
					}
				}
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar) {
	Move move;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y)) {
				Piece* piece = board.getPiece(x, y);
				if(piece->getPieceChar() == pieceChar && y == row) {
					move = piece->getMoveIfPossible(board, endPos);
					if(move.endX != -1 && move.endY != -1) {
						bool valid = false;
						board.doMove(&move);
						if(!board.isKingVulnerable(piece->color))
							valid = true;
						board.undoMove(&move);
						if(valid)
							return move;
					}
				}
			}
		}
	}

	throw std::invalid_argument("Found no move");
}

Move getValidMove(Board board, Point endPos, int row, PieceChar pieceChar, int column) {
	Move move;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y)) {
				Piece* piece = board.getPiece(x, y);
				if(piece->getPieceChar() == pieceChar && y == row && x == column) {
					move = piece->getMoveIfPossible(board, endPos);
					if(move.endX != -1 && move.endY != -1) {
						bool valid = false;
						board.doMove(&move);
						if(!board.isKingVulnerable(piece->color))
							valid = true;
						board.undoMove(&move);
						if(valid)
							return move;
					}
				}
			}
		}
	}
	throw std::invalid_argument("Found no move");
}

std::vector<Move> getAllMoves(Board board, Color side) {

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y)) {
				Piece* piece = board.getPiece(x, y);
				if(piece->color == side) {
					tempMoveList = piece->getPossibleMoves(board);
					// Go through moves
					for(int i = 0; i < tempMoveList.size(); i++) {
						board.doMove(&tempMoveList[i]);
						if(!board.isKingVulnerable(side))
							moves.push_back(tempMoveList[i]);
						board.undoMove(&tempMoveList[i]);
					}
				}
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar) {

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar) {
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol) {

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == startCol) {
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, int startRow, PieceChar pieceChar) {

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && y == startRow) {
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

std::vector<Move> getAllMovesOfPieceChar(Board board, PieceChar pieceChar, int startCol, int startRow) {

	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(!board.isSquareEmpty(x, y) && board.getPiece(x, y)->getPieceChar() == pieceChar && x == startCol && y == startRow) {
				tempMoveList = board.getPiece(x, y)->getPossibleMoves(board);
				moves.insert(it, tempMoveList.begin(), tempMoveList.end());
				it = moves.begin();
			}
		}
	}

	return moves;
}

Move getBestMove(Board* board, int maxTime) {
	int totalMovesChecked = 0;
	board->startTurn = board->turn;

	auto startTime = std::chrono::high_resolution_clock::now();
	long long accTime = 0;

	Move move;

	for (int i = 1; i <= MAXDEPTH; i++) {
		startTime = std::chrono::high_resolution_clock::now();
		move = minimax(board, i, true, board->turn, -((int)Value::Infinite), (int)Value::Infinite, false, &totalMovesChecked, 0);

		auto currentTime = std::chrono::high_resolution_clock::now();
		auto timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
		accTime += timeSpent;
		auto estimatedTimeForNextMove = timeSpent * 20;
		if (accTime + estimatedTimeForNextMove > maxTime / std::max(1, (20 - (32 - board->pieceCount[0]) ) ) )
			break;
	}

	return move;

}

Move generateMove(Board* board, int depth, int& totalMoves)
{
	return minimax(board, depth, true, board->turn, -((int)Value::Infinite), (int)Value::Infinite, false, &totalMoves, 0);
}

std::random_device rd;
std::mt19937 g(rd());

Move minimax(Board* board, int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int* totalMoves, int accDepth) {
	(*totalMoves) += 1;
	Move bestMove;
	Color oppositeColor = ((currentTurn == Color::White) ? Color::Black : Color::White);

	// check if the position has occured more than 2 times
	// this is to check for draw
	if(board->zobrist->GetCurrentInstanceCount() > 2) {
		int multiplier = ((currentTurn == board->turn) ? 1 : -1);
		bestMove.value = (int) Value::Draw * multiplier;
		bestMove.moveDepth = accDepth;
		return bestMove;
	}

	if(isMax)
		bestMove.value = -((int) Value::Infinite);
	else
		bestMove.value = (int) Value::Infinite;
	if(depth == 0 || !board->kingAlive[(int) currentTurn] || !board->kingAlive[(int) oppositeColor]) {
		bestMove.value = board->evaluateBoard(board->turn);
		bestMove.moveDepth = accDepth;
		return bestMove;
	}

	std::vector<Move> moves = getAllMoves(*board, currentTurn);

	for(int i = 0; i < (int) moves.size(); i++)
		moves[i].moveSizeBatch = (int) moves.size();
		
	//std::shuffle(moves.begin(), moves.end(), g);

	if((int) moves.size() == 0) {
		if(board->isKingVulnerable(currentTurn))
			if(board->turn != currentTurn)
				bestMove.value = (int) Value::Mate;
			else
				bestMove.value = -((int) Value::Mate);
		else
			bestMove.value = (int) Value::Draw;
		bestMove.moveDepth = accDepth;
		return bestMove;
	}
	for(int i = 0; i < (int) moves.size(); i++) {
		Move move;

		board->doMove(&(moves[i]));

		// If the position has not already been evaluated
		if (!board->zobrist->GetValue(depth, move.value)) {
			// Go deeper
			if (depth == 1 && !doingHE &&
				(moves[i].target != NULL ||
					board->isKingVulnerable(currentTurn) ||
					board->isKingVulnerable(oppositeColor) ||
					board->pieceCount[0] < 8))
				move = minimax(board, HEDEPTH, !isMax, oppositeColor, a, b, true, totalMoves, accDepth + 1);
			else {
				if (doingHE && moves[i].target == NULL)
					move = minimax(board, 0, !isMax, oppositeColor, a, b, doingHE, totalMoves, accDepth + 1);
				else
					move = minimax(board, depth - 1, !isMax, oppositeColor, a, b, doingHE, totalMoves, accDepth + 1);
			}

			 board->zobrist->StoreEval(depth, move.value);
		}

		board->undoMove(&(moves[i]));


		if(isMax && move.value > bestMove.value) {
			bestMove = moves[i];
			bestMove.value = move.value;
			bestMove.moveDepth = move.moveDepth;
		} else if(!isMax && move.value < bestMove.value) {
			bestMove = moves[i];
			bestMove.value = move.value;
			bestMove.moveDepth = move.moveDepth;
		} else if(move.value == bestMove.value && move.moveDepth < bestMove.moveDepth) {
			bestMove = moves[i];
			bestMove.value = move.value;
			bestMove.moveDepth = move.moveDepth;
		}

		
		if(isMax) {
			a = std::max(move.value, a);
			if(a >= b)
				break;
		} else {
			b = std::min(move.value, b);
			if(b <= a)
				break;
		}
		
		




	}
	bestMove.totalMoves = *totalMoves;
	return bestMove;
}
