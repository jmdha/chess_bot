#include <cstdio>
#include <iostream>
#include "Classes/Headers/board.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/move.h"

int main(int argc, char *argv[])
{
    Board board = Board();
    Move move = getBestMove(&board, 3);
    printf("%s\n", move.getMoveAsString().c_str());
    return 0;
}