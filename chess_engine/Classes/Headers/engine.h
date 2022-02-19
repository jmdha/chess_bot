#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <chrono>
#include "ai.h"
#include "move.h"
#include "utilities.h"

void RunDefaultEngine(int depth, std::string importArg = "") {
    Board board = Board();

	if(importArg.length() != 0)
		board.importFakePGN(importArg);

	auto start = std::chrono::high_resolution_clock::now();
	Move move = getBestMove(&board, depth);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	if(move.startX == -1 || move.startY == -1) {
		switch (move.value)
		{
		case static_cast<int>(Value::Draw):
			printf("draw\n%s\n", getStatString(move, duration.count(), depth, board.pieceCount[0]).c_str());
			break;
		case static_cast<int>(Value::Mate):
			printf("win\n%s\n", getStatString(move, duration.count(), depth, board.pieceCount[0]).c_str());
			break;
		case -static_cast<int>(Value::Mate):
			printf("loss\n%s\n", getStatString(move, duration.count(), depth, board.pieceCount[0]).c_str());
			break;
		}
	} else
		printf("%s\n%s\n", move.getMoveAsPlainString().c_str(), getStatString(move, duration.count(), depth, board.pieceCount[0]).c_str());
}

#endif