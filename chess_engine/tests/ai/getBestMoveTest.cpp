#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "./../../Classes/Headers/ai.h"
#include "./../../Classes/Headers/board.h"

// These test rely on import FEN working
int main(int argc, char* argv[]) {
    //throw std::logic_error(std::to_string(argc));
    try {
        Board board = Board();
        board.importFEN(argv[2]);
        for (int i = 0; i < 2; i++)
            for (int i2 = 0; i2 < 2; i2++)
                board.castlingValid[i][i2] = false;

        Move move = getBestMove(&board, std::atoi(argv[4]));

        if (move.getMoveAsPlainString() != argv[3]) {
            std::string error = "Incorrect move generated Expected: ";
            error.append(argv[3]);
            error.append(" | Generated: " + move.getMoveAsPlainString());
            error.append("\nPerceived value: " + std::to_string(move.value));
            throw std::logic_error(error);
        }
            


    } catch (const std::logic_error e) {
        if (!std::atoi(argv[1]))
            throw e;
        else
            exit(EXIT_SUCCESS);
    }
    if (std::atoi(argv[1]))
        throw std::logic_error("Expected an exception, yet test went through anyway.");
    else
        exit(EXIT_SUCCESS);
}