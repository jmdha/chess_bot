#include <cstdio>
#include <iostream>
#include <ctime>
#include "Classes/Headers/board.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/move.h"

Move getChessMove(int depth, std::time_t time) {
    Board board = Board();
    return getBestMove(&board, depth);
}


int main()
{
    int x;
    Board board = Board();
    board.printBoard();
    std::cin >> x;
     
    return 0;
}