#include <cstdio>
#include <iostream>
#include <chrono>
#include "Classes/Headers/board.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/move.h"

std::string getStatString(Move move, int64_t duration, int depth, int pieceCount);

int main(int argc, char *argv[])
{
    Board board = Board();

    if (argc > 1)
        board.importFakePGN(argv[1]);

    int depth;
    if (board.pieceCount < 5)
        depth = 8;
    else if (board.pieceCount < 7)
        depth = 7;
    else if (board.pieceCount < 12)
        depth = 6;
    else if (board.pieceCount < 20)
        depth = 5;
    else
        depth = 4;


    auto start = std::chrono::high_resolution_clock::now();
    Move move = getBestMove(&board, depth);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    if (move.startX == -1 || move.startY == -1)
        printf("draw\n%s", getStatString(move, duration.count(), depth, board.pieceCount));
    else
        printf("%s\n%s", move.getMoveAsPlainString().c_str(), getStatString(move, duration.count(), depth, board.pieceCount).c_str());
        
    return 0;
}

std::string getStatString(Move move, int64_t duration, int depth, int pieceCount) {
    std::string statString = "";
    statString.append("Search depth: " + std::to_string(depth) + "\n");
    statString.append("Piece count: " + std::to_string(pieceCount) + "\n");
    statString.append("Time (ms): " + std::to_string(duration) + "\n");
    statString.append("Total moves: " + std::to_string(move.totalMoves));

    return statString;
}