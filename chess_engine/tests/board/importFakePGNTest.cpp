#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "./../../Classes/Headers/board.h"

// These test rely on import FEN working
int main(int argc, char* argv[]) {
    //throw std::logic_error(std::to_string(argc));
    try {
        Board board = Board();

		board.importFakePGN(argv[2]);

        Board board2 = Board();
        board2.importFEN(argv[3]);
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                Piece *fakePGNChar = board.getPiece(x, y);
                Piece *fenChar = board2.getPiece(x, y);
                if (fakePGNChar == nullptr || fenChar == nullptr) {
                    if (fakePGNChar != fenChar)
                        throw std::logic_error("Mismatch char | One null, other not");
                } else if (fakePGNChar->getPieceChar() != fenChar->getPieceChar())
                    throw std::logic_error("Mismatch char | different chars");
                    
            }
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