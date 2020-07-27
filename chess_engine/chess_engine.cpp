#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include "Classes/Headers/board.h"
#include "Classes/Headers/move.h"
#include "Classes/Pieces/Headers/knight.h"
#include "Classes/Headers/generic_helper_functions.h"


int main(int argc, char *argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();
    int depth;
    Board board(WHITE);
    if (argc < 2) {
        return 1;
    } else {
        depth = atoi(argv[1]);
    }
        
    
    if (argc > 3) {
        std::string moves = argv[3];
        moves.erase(
            remove(moves.begin(), moves.end(), '\"'),
            moves.end()
        );
        if (isNumber(moves[0]))
            board.importPGN(moves);
        else
            board.importFakePGN(moves);
    } else if (argc > 2) {
        std::string fen = argv[2];
        fen.erase(
            remove(fen.begin(), fen.end(), '\"'),
            fen.end()
        );
        board.importFEN(fen);
    }
    board.printBoard();
    
    
    Move bestMove = board.getBestMove(depth);
    board.doMove(&bestMove);

    printf("%s\n", bestMove.getMoveAsString().c_str());
    board.switchTurn();
    if (static_cast<int>(board.getAllMoves().size()) == 0) {
        printf("draw\n");
    } else if (!board.kingAlive[WHITE] || !board.kingAlive[BLACK]) {
        printf("checkmate\n");
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    return 0;
} 