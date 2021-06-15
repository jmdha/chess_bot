#include <cstdio>
#include <iostream>
#include "Classes/Headers/board.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/move.h"

int main(int argc, char *argv[])
{
    Board board = Board();

    //if (argc > 1)
   //board.importFakePGN(argv[1]);

    board.importFEN("1rb2r2/2bpn1kp/7p/1p3p1B/1Np1P3/P1P5/3K1QP1/5R2 b - - 1 35");
    board.turn = BLACK;
    for (int i = 0; i < 2; i++) {
        for (int ii = 0; ii < 2; ii++) {
            board.castlingValid[i][ii] = false;
        }
    }

    Move move = getBestMove(&board, 3);

    if (move.startX == -1 || move.startY == -1)
        printf("draw");
    else
        printf("%s", move.getMoveAsPlainString().c_str());
        
    return 0;
}