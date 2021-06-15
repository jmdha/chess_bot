#include <cstdio>
#include <iostream>
#include "Classes/Headers/board.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/move.h"

int main(int argc, char *argv[])
{
    Board board = Board();
    
    if (argc > 1)
        board.importFakePGN(argv[1]);

    Move move = getBestMove(&board, 3);

    if (move.startX == -1 || move.startY == -1)
        printf("draw");
    else
        printf("%s", move.getMoveAsPlainString().c_str());
    return 0;
}