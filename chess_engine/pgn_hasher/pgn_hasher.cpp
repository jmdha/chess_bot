// pgn_hasher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <iostream>
#include <chrono>
#include "Headers/board.h"
#include "Headers/ai.h"
#include "Headers/move.h"


int main(int argc, char* argv[])
{
    Board board = Board();

    if (argc > 1)
        board.importPGN(argv[1], true);

    return 0;
}