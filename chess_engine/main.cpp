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
    //std::vector<Move> moves = board.getPiece(4, 4)->getPossibleMoves(board);



    Move move = getBestMove(&board, 3);
    printf("%s\n", move.getMoveAsPlainString().c_str());
    return 0;
}