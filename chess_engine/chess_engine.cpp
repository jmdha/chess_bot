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
#include "Classes/Headers/ai.h"

int getChessMove(int argc, char *argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();
    int depth;
    Board board(WHITE);
    if (argc < 2)
    {
        return 1;
    }
    else
    {
        depth = atoi(argv[1]);
    }

    if (argc > 3)
    {
        std::string moves = argv[3];
        moves.erase(
            remove(moves.begin(), moves.end(), '\"'),
            moves.end());
        if (isNumber(moves[0]))
            board.importPGN(moves, false);
        else
            board.importFakePGN(moves);
    }
    else if (argc > 2)
    {
        std::string fen = argv[2];
        fen.erase(
            remove(fen.begin(), fen.end(), '\"'),
            fen.end());
        board.importFEN(fen);
    }
    board.printBoard();

    Move bestMove = getBestMove(&board, depth);
    board.commitMove(&bestMove);

    printf("%s\n", bestMove.getMoveAsString().c_str());
    if (static_cast<int>(getAllMoves(board, board.turn).size()) == 0)
    {
        printf("draw\n");
    }
    else if (!board.kingAlive[WHITE] || !board.kingAlive[BLACK])
    {
        printf("checkmate\n");
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    return 0;
}

int getHash(int argc, char *argv[])
{
    Board board(WHITE);
    std::string moves = argv[1];
    bool printPerMove = true;
    moves.erase(
        remove(moves.begin(), moves.end(), '\"'),
        moves.end());
    if (isNumber(moves[0]))
        board.importPGN(moves, printPerMove);
    else
        board.importFakePGN(moves);
    if (!printPerMove)
        printf("%lu\n", board.zobrist->getHash());
    return 0;
}

int main(int argc, char *argv[]) {
    
    int returnValue;
    try {
        returnValue = getHash(argc, argv);
    } catch (const std::exception& e) {
        return -1;
    }
    
    return returnValue;

    /*
        Board board = Board();
        board.clearBoard();
        board.importFEN("8/8/8/8/1Pp5/8/8/8 w - - 0 1");
        board.enPassant = 1;
        board.turn = BLACK;
        std::vector<Move> moves = getAllMoves(board, board.turn);
        board.printBoard();
        printf("-----------------\n");
        board.doMove(&moves[0]);
        board.printBoard();

    
    return 0;
    */
}

