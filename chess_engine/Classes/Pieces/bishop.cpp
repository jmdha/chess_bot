#include "Headers/bishop.h"

Bishop::Bishop(Color color) : Piece(color) {
	this->color = color;
}

PieceChar Bishop::getPieceChar() {
	if(this->color == WHITE)
		return BISHOPWHITE;
	else
		return BISHOPBLACK;
}

std::vector<Move> Bishop::getPossibleMoves(Board board) {
	std::vector<Move> moves;

	std::vector<Move>::iterator it;
	it = moves.begin();
	std::vector<Move> tempMoveList;

	for(int i = 0; i < 4; i++) {

		Direction dir = NORTHWEST;
		switch(i) {
			case 0:
			dir = NORTHEAST;
			break;

			case 1:
			dir = SOUTHWEST;
			break;

			case 2:
			dir = SOUTHEAST;
			break;
		}
		tempMoveList = this->getPossibleMovesInDirection(board, dir, 8);
		moves.insert(it, tempMoveList.begin(), tempMoveList.end());
		it = moves.begin();
	}


	return moves;
}

Move Bishop::getMoveIfPossible(Board board, Point endPos) {
	std::vector<Move> moves;

	for(int i = 0; i < 4; i++) {

		Direction dir = NORTHWEST;
		switch(i) {
			case 0:
			dir = NORTHEAST;
			break;

			case 1:
			dir = SOUTHWEST;
			break;

			case 2:
			dir = SOUTHEAST;
			break;
		}
		moves = this->getPossibleMovesInDirection(board, dir, 8);
		for(int i = 0; i < static_cast<int>(moves.size()); i++) {
			if(moves[i].endX == endPos.x && moves[i].endY == endPos.y)
				return moves[i];
		}
	}
	return Move(-1, -1, -1, -1);
}

int Bishop::getValue() {
	return VALUEBISHOP + VALUEBISHOPPOS[x][(this->color == WHITE) ? y : HEIGHT - 1];
}

int Bishop::getIndex() {
	return BISHOPINDEX;
}

bool Bishop::checkIfPosPossible(Board board, Point pos) {
	int xDir;
	int yDir;
	if(x > pos.x)
		xDir = -1;
	else if(x < pos.x)
		xDir = 1;
	else
		return false;
	if(y > pos.y)
		yDir = -1;
	else if(y < pos.y)
		yDir = 1;
	else
		return false;

	for(int i = 1; i < 8; i++) {
		int newX = x + i * xDir;
		int newY = y + i * yDir;
		if(pos.x == newX && pos.y == newY)
			return true;
		else if(board.getPiece(newX, newY) != NULL)
			return false;
	}


	return false;
}
