#include "Headers/piece.h"
#include <iostream>

Piece::Piece(Color color) {
	this->color = color;
}

PieceChar Piece::getPieceChar() {
	return BLANK;
}

std::vector<Move> Piece::getPossibleMoves(Board board) {
	return {};
}

Move Piece::getMoveIfPossible(Board board, Point endPos) {
	return {};
}

int Piece::getValue() {
	return 0;
}

int Piece::getIndex() {
	return 0;
}

// This asssumes either empty square or enemy piece is a valid end square
std::vector<Move> Piece::getPossibleMovesInDirection(Board board, Direction direction, int length) {
	// Max moves is 7 as that is board width/height minus the piece
	std::vector<Move> moves;

	for(int i = 1; i <= length; i++)     {

		Point endPoint = getNewEndPoint(Point(this->x, this->y), direction, i);

		if(endPoint.x >= WIDTH || endPoint.x < 0 || endPoint.y >= HEIGHT || endPoint.y < 0)
			break;

		if(board.isSquareEmpty(endPoint.x, endPoint.y))         {
			moves.push_back(Move(this->x, this->y, endPoint.x, endPoint.y));
		}         else if(board.isSquareEnemy(this->color, endPoint.x, endPoint.y))         {
			moves.push_back(Move(this->x, this->y, endPoint.x, endPoint.y));
			break;
		}         else
			break;
	}
	return moves;
}

// This asssumes either enemy piece is a valid end square
std::vector<Move> Piece::getPossibleMovesInDirection(Board board, Direction direction, int length, bool onlyCapture) {
	// Max moves is 7 as that is board width/height minus the piece
	std::vector<Move> moves;

	for(int i = 1; i <= length; i++)     {

		Point endPoint = getNewEndPoint(Point(this->x, this->y), direction, i);

		if(endPoint.x >= WIDTH || endPoint.x < 0 || endPoint.y >= HEIGHT || endPoint.y < 0)
			break;

		if(!onlyCapture)         {
			if(board.isSquareEmpty(endPoint.x, endPoint.y))
				moves.push_back(Move(this->x, this->y, endPoint.x, endPoint.y));
			else
				break;
		}         else if(board.isSquareEnemy(this->color, endPoint.x, endPoint.y))         {
			moves.push_back(Move(this->x, this->y, endPoint.x, endPoint.y));
		}         else
			break;
	}
	return moves;
}

Point Piece::getNewEndPoint(Point priorPos, Direction direction, int moveLength) {
	switch(direction)     {
		case NORTH:
		return Point(priorPos.x, priorPos.y + moveLength);

		case SOUTH:
		return Point(priorPos.x, priorPos.y - moveLength);

		case EAST:
		return Point(priorPos.x + moveLength, priorPos.y);

		case WEST:
		return Point(priorPos.x - moveLength, priorPos.y);

		case NORTHEAST:
		return Point(priorPos.x + moveLength, priorPos.y + moveLength);

		case NORTHWEST:
		return Point(priorPos.x - moveLength, priorPos.y + moveLength);

		case SOUTHEAST:
		return Point(priorPos.x + moveLength, priorPos.y - moveLength);

		case SOUTHWEST:
		return Point(priorPos.x - moveLength, priorPos.y - moveLength);
		default:
		printf("Direction %i\n", (int) direction);
		throw std::invalid_argument("Invalid direction ");
	}
}

bool Piece::checkIfPosPossible(Board board, Point pos) {
	return false;
}
