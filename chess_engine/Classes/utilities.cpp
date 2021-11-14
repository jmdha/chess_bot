#include "Headers/utilities.h"

bool isNumber(char charToCheck) {
	if(int(charToCheck) > 47 && int(charToCheck) < 58)
		return true;
	else
		return false;
}

int getColumnAsNumber(char column) {
	if(isLowercase(column))
		return int(column) - 97;
	else
		return int(column) - 65;
}

int getRowAsNumber(char row) {
	return int(row) - 49;
}

bool isLowercase(char charToCheck) {
	if(int(charToCheck) > 64 && int(charToCheck) < 91)
		return false;
	else
		return true;
}

std::string getStatString(Move move, int64_t duration, int depth, int pieceCount) {
	std::string statString = "";
	statString.append("Search depth: " + std::to_string(depth) + "\n");
	statString.append("Piece count: " + std::to_string(pieceCount) + "\n");
	statString.append("Time (ms): " + std::to_string(duration) + "\n");
	statString.append("Total moves: " + std::to_string(move.totalMoves));

	return statString;
}