#include "pgn_hasher.h"

void hashMoves(std::string moves) {
	Board board = Board();
	board.importPGN(moves, true);
}