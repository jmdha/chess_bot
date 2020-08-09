#include "Headers/board.h"
#include "Pieces/Headers/pawn.h"
#include "Pieces/Headers/rook.h"
#include "Pieces/Headers/knight.h"
#include "Pieces/Headers/bishop.h"
#include "Pieces/Headers/king.h"
#include "Pieces/Headers/queen.h"
#include <iostream>

// used for minimax
#include <algorithm>
#include <cstdlib>
#include <time.h>

// used in importFEN
#include <ctype.h>

// used for random moves
#include <chrono>

// used for import of PGN
#include "Headers/generic_helper_functions.h"

Board::Board()
{
}

Board::Board(Color turn)
{
    this->zobrist = new Zobrist(this);
    setStartPos();
}

// assumes correct FEN string
void Board::importFEN(std::string FEN)
{
    clearBoard();
    this->turnNumber = 1;

    // import position

    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        int remainingSquares = WIDTH;
        while (remainingSquares > 0)
        {
            char currentChar = FEN[0];
            if (isdigit(currentChar))
            {
                remainingSquares -= (int)currentChar - 48;
            }
            else
            {
                placePiece(getPieceCharFromChar(currentChar), WIDTH - remainingSquares, y);
                remainingSquares--;
            }
            FEN.erase(0, 1);
        }
        FEN.erase(0, 1);
    }

    this->zobrist->priorInstanceCount.clear();
    this->zobrist->incrementCurrentHash();
    //this->zobrist->initializeHash();

    if (FEN.length() == 0)
        return;
    // import turn
    if (FEN[0] == 'w')
        setTurn(WHITE);
    else
        setTurn(BLACK);
    FEN.erase(0, 2);

    // import king availibity

    // import en-passant

    // import half move

    // import full move
}

std::string Board::getFEN()
{
    std::string FEN = "";

    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        int blankCounter = 0;
        for (int x = 0; x < WIDTH; x++)
        {
            Piece *piece = getPiece(x, y);
            if (piece == NULL)
                blankCounter++;
            else
            {
                if (blankCounter != 0)
                    FEN.append(1, blankCounter + '0');
                FEN.append(1, piece->getPieceChar());
                blankCounter = 0;
            }
            if (x == 7 && piece == NULL && blankCounter != 0)
            {
                FEN.append(1, blankCounter + '0');
            }
        }
        if (y != 0)
            FEN.append(1, '/');
    }

    FEN.append(1, ' ');
    if (turn == WHITE)
        FEN.append(1, 'w');
    else
        FEN.append(1, 'b');

    return FEN;
}

void Board::importPGN(std::string moves, bool exportMovePerHash)
{
    this->turnNumber = 1;
    this->zobrist->priorInstanceCount.clear();
    this->zobrist->incrementCurrentHash();
    Move move;
    std::string moveString;
    enPassant = -1;
    bool inComment = false;
    bool nestedComment = false;
    for (int i = 0; i < static_cast<int>(moves.length()); i++)
    {
        if (moves[i] == ' ') {
            // da(you know... like char da -> charda -> charmander? I don't know man) is used for debugging | remove when finished
            char da[7];
            if (i > 3)
            {
                da[0] = moves[i - 3];
                da[1] = moves[i - 2];
                da[2] = moves[i - 1];
                da[3] = moves[i + 0];
                da[4] = moves[i + 1];
                da[5] = moves[i + 2];
                da[6] = moves[i + 3];
            }
            if (moves[i + 1] == '{' || moves[i + 1] == '(') {
                if (inComment)
                    nestedComment = true;
                else
                    inComment = true;
            }

            if (moves[i - 1] == '}' || moves[i - 1] == ')') {
                if (nestedComment)
                    nestedComment = false;
                else
                    inComment = false;
            }


            if (inComment)
                continue;

            if (moves[i + 1] != '.' && !isNumber(moves[i + 1]) && (moves[i - 1] == '.' || ((isNumber(moves[i - 1]) || moves[i - 1] == 'O' || moves[i - 1] == '+' || moves[i - 1] == '#' || moves[i - 1] == '}' || moves[i - 1] == 'R' || moves[i - 1] == 'K' || moves[i - 1] == 'B' || moves[i - 1] == 'Q'))))
            {

                if (da[6] == '?') {
                    printf("wa\n");
                }

                // get move
                if (!isNumber(moves[i + 2])


                    || (!isLowercase(moves[i + 1]) && isNumber(moves[i + 2])))
                {
                    if (moves[i + 1] != 'O')
                    {
                        // Normal move
                        char pieceChar = moves[i + 1];
                        if (isLowercase(pieceChar))
                            pieceChar = ((turn == WHITE) ? PAWNWHITE : PAWNBLACK);
                        else if (turn == BLACK)
                            pieceChar += 32;
                        if (moves[i + 4] != ' ' && moves[i + 4] != '+' && moves[i + 4] != '#' && moves[i + 4] != '?' && moves[i + 4] != '!')
                        {
                            if (moves[i + 5] == ' ' || moves[i + 5] == '+' || moves[i + 5] == '#' || moves[i + 5] == '?' || moves[i + 5] == '!')
                            {
                                if (moves[i + 2] == 'x')
                                {
                                    // if pawn take
                                    if (isLowercase(moves[i + 1]))
                                        move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 1]));
                                    else
                                        move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar);
                                }
                                else if (isNumber(moves[i + 2])) {
                                    move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), getRowAsNumber(moves[i + 2]), pieceChar);
                                }
                                else
                                    move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 2]));
                            }
                            else if (isNumber(moves[i + 2]))
                            {
                                move = getValidMove(Point(getColumnAsNumber(moves[i + 4]), moves[i + 5] - 49), getRowAsNumber(moves[i + 2]), pieceChar);
                            }
                            else {
                                // if pawn-promotion-capture(... a little unwieldly)
                                if (moves[i + 5] == '=') 
                                    move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), pieceChar, getColumnAsNumber(moves[i + 1]), getPieceIndexFromChar(moves[i + 6]));
                                else
                                move = getValidMove(Point(getColumnAsNumber(moves[i + 4]), moves[i + 5] - 49), pieceChar, getColumnAsNumber(moves[i + 2]));
                            }
                        }
                        else {
                            if (moves[i + 5] == '=')
                                move = getValidMove(Point(getColumnAsNumber(moves[i + 3]), moves[i + 4] - 49), getPieceIndexFromChar(moves[i + 6]));
                            else 
                                move = getValidMove(Point(getColumnAsNumber(moves[i + 2]), moves[i + 3] - 49), pieceChar);
                        }
                            
                    }

                    else
                    {
                        //castle
                        int y = ((turn == WHITE) ? BACKROWWHITE : BACKROWBLACK);
                        int startX = 4;
                        int endX;
                        if (moves[i + 4] == ' ')
                            endX = 6;
                        else
                            endX = 2;
                        move = Move(startX, y, endX, y);
                        move.castling = true;
                    }
                }
                else
                {
                    // pawn move (not take)
                    if (moves[i + 3] == ' ' || moves[i + 3] == '+' || moves[i + 3] == '#' || moves[i + 3] == '?' || moves[i + 3] == '!')
                        move = getValidMove(Point(getColumnAsNumber(moves[i + 1]), moves[i + 2] - 49));

                    // same but with promotion
                    else 
                        move = getValidMove(Point(getColumnAsNumber(moves[i + 1]), moves[i + 2] - 49), getPieceIndexFromChar(moves[i + 4]));
                }

                if (exportMovePerHash)
                {
                    // get move as string
                    moveString = "";
                    int i2 = 1;
                    while (moves[i + i2] != ' ')
                    {
                        moveString += moves[i + i2];
                        i2++;
                    };
                    //printf("%lu %s\n", this->zobrist->getHash(), moveString.c_str());
                    printf("%lu %s\n", this->zobrist->getHash(), moveString.c_str());
                }


                // commit move
                commitMove(&move);
                if (move.pawnDoubleMove)
                    enPassant = move.startX;
                else
                    enPassant = -1;
                //printBoard();
                if (isNumber(moves[i + 1]) && (moves[i + 2] == '/' || moves[i + 2] == '-'))
                    break;
            }
        }

    }
}

void Board::importFakePGN(std::string moves)
{
    this->turnNumber = 1;
    this->zobrist->priorInstanceCount.clear();
    this->zobrist->incrementCurrentHash();
    std::string move = "";
    for (int i = 0; i < static_cast<int>(moves.length()); i++)
    {
        if (moves[i] != ' ')
        {
            move.push_back(moves[i]);
        }
        if (moves[i] == ' ' || i == static_cast<int>(moves.length()) - 1)
        {
            Move *newMove;
            if (move == "O-O" || move == "O-O-O")
            {
                int y = ((turn == WHITE) ? BACKROWWHITE : BACKROWBLACK);
                int startX = 4;
                int endX;
                if (move == "O-O")
                    endX = 6;
                else
                    endX = 2;
                newMove = new Move(startX, y, endX, y);
            }
            else
                newMove = new Move(move);
            doMove(newMove);
            switchTurn();
            move = "";
        }
    }
}

void Board::printBoard()
{
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (isSquareEmpty(x, y))
                printf(".");
            else
                printf("%c", getPiece(x, y)->getPieceChar());
        }
        printf("\n");
    }
}

bool Board::isSquareEmpty(int x, int y)
{
    return getPiece(x, y) == NULL;
}

bool Board::isSquareEnemy(Color color, int x, int y)
{
    if (isSquareEmpty(x, y))
        return false;
    return getPiece(x, y)->color == ((color == WHITE) ? BLACK : WHITE);
}

void Board::setStartPos()
{
    importFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::clearBoard()
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            this->board[x][y] = NULL;
    this->zobrist = new Zobrist(this);
}


void Board::setTurn(Color turn)
{
    this->turn = turn;
}

void Board::switchTurn()
{
    if (turn == WHITE)
        turn = BLACK;
    else {
        turn = WHITE;
        this->turnNumber++;
    }
}

void Board::placePiece(Piece *piece)
{
    board[piece->x][piece->y] = piece;
    if (piece != NULL)
        this->zobrist->flipSquare(piece->x, piece->y, piece->getIndex(), static_cast<int>(piece->color));
}

void Board::placePiece(Piece *piece, int x, int y)
{
    board[x][y] = piece;
    piece->x = x;
    piece->y = y;
    this->zobrist->flipSquare(x, y, piece->getIndex(), static_cast<int>(piece->color));
}

void Board::placePiece(PieceChar piece, int x, int y)
{
    board[x][y] = getPieceFromChar(piece);
    getPiece(x, y)->x = x;
    getPiece(x, y)->y = y;
    Piece *newPiece = this->getPiece(x, y);
    this->zobrist->flipSquare(x, y, newPiece->getIndex(), static_cast<int>(newPiece->color));
}

void Board::removePiece(int x, int y)
{
    Piece *piece = this->getPiece(x, y);

    if (piece != NULL)
    {
        int index = piece->getIndex();
        int color = static_cast<int>(piece->color);
        this->zobrist->flipSquare(x, y, index, color);
    }

    board[x][y] = NULL;
}

Piece *Board::getPiece(int x, int y)
{
    return board[x][y];
}

Piece *Board::getPieceFromChar(PieceChar piece)
{
    switch (piece)
    {
    case PAWNWHITE:
        return new Pawn(WHITE);

    case PAWNBLACK:
        return new Pawn(BLACK);

    case ROOKWHITE:
        return new Rook(WHITE);

    case ROOKBLACK:
        return new Rook(BLACK);

    case KNIGHTWHITE:
        return new Knight(WHITE);

    case KNIGHTBLACK:
        return new Knight(BLACK);

    case BISHOPWHITE:
        return new Bishop(WHITE);

    case BISHOPBLACK:
        return new Bishop(BLACK);

    case QUEENWHITE:
        return new Queen(WHITE);

    case QUEENBLACK:
        return new Queen(BLACK);

    case KINGWHITE:
        return new King(WHITE);

    case KINGBLACK:
        return new King(BLACK);

    default:
        throw std::invalid_argument("Invalid direction " + (int)piece);
    }
}

PieceChar Board::getPieceCharFromChar(char piece)
{
    switch (piece)
    {
    case 'P':
        return PAWNWHITE;

    case 'p':
        return PAWNBLACK;

    case 'R':
        return ROOKWHITE;

    case 'r':
        return ROOKBLACK;

    case 'N':
        return KNIGHTWHITE;

    case 'n':
        return KNIGHTBLACK;

    case 'B':
        return BISHOPWHITE;

    case 'b':
        return BISHOPBLACK;

    case 'Q':
        return QUEENWHITE;

    case 'q':
        return QUEENBLACK;

    case 'K':
        return KINGWHITE;

    case 'k':
        return KINGBLACK;

    default:
        return BLANK;
    }
}

PieceIndex Board::getPieceIndexFromChar(char piece)
{
    switch (piece)
    {
    case 'P':
    case 'p':
        return PAWNINDEX;

    case 'R':
    case 'r':
        return ROOKINDEX;

    case 'N':
    case 'n':
        return KNIGHTINDEX;

    case 'B':
    case 'b':
        return BISHOPINDEX;

    case 'Q':
    case 'q':
        return QUEENINDEX;

    case 'K':
    case 'k':
        return KINGINDEX;

    default:
        return NONEINDEX;
    }
}

Move Board::getValidMove(Point endPos)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        if (piece->getIndex() == PAWNINDEX)
        {
            if (piece->color == turn && moves[i].startX == endPos.x && moves[i].endX == endPos.x && moves[i].endY == endPos.y)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

Move Board::getValidMove(Point endPos, PieceIndex promotionType)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        if (piece->getIndex() == PAWNINDEX)
        {
            if (piece->color == turn && moves[i].startX == endPos.x && moves[i].endX == endPos.x && moves[i].endY == endPos.y && moves[i].promotionType == promotionType)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

Move Board::getValidMove(Point endPos, char pieceChar)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        char piecePieceChar = piece->getPieceChar();
        if (piecePieceChar == pieceChar)
        {
            if (moves[i].endX == endPos.x && moves[i].endY == endPos.y)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

Move Board::getValidMove(Point endPos, char pieceChar, int column)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        char piecePieceChar = piece->getPieceChar();
        if (piecePieceChar == pieceChar)
        {
            if (moves[i].endX == endPos.x && moves[i].endY == endPos.y && piece->x == column)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

Move Board::getValidMove(Point endPos, char pieceChar, int column, PieceIndex promotionType)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        char piecePieceChar = piece->getPieceChar();
        if (piecePieceChar == pieceChar)
        {
            if (moves[i].endX == endPos.x && moves[i].endY == endPos.y && piece->x == column && moves[i].promotionType == promotionType)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

Move Board::getValidMove(Point endPos, int row, char pieceChar)
{
    std::vector<Move> moves = getAllMoves(turn);
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Piece *piece = getPiece(moves[i].startX, moves[i].startY);
        char piecePieceChar = piece->getPieceChar();
        if (piecePieceChar == pieceChar)
        {
            if (moves[i].endX == endPos.x && moves[i].endY == endPos.y && piece->y == row)
            {
                return moves[i];
            }
        }
    }
    throw std::invalid_argument("Found no move");
}

std::vector<Move> Board::getAllMoves(Color side)
{

    std::vector<Move> moves;

    std::vector<Move>::iterator it;
    it = moves.begin();
    std::vector<Move> tempMoveList;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (!isSquareEmpty(x, y) && getPiece(x, y)->color == side)
            {
                tempMoveList = getPiece(x, y)->getPossibleMoves(*this);
                moves.insert(it, tempMoveList.begin(), tempMoveList.end());
                it = moves.begin();
            }
        }
    }

    return moves;
}

void Board::commitMove(Move *move)
{
    doMove(move);
    switchTurn();
}

// assumed valid move
void Board::doMove(Move *move)
{
    move->setTarget(getPiece(move->endX, move->endY));
    // Used for hashing
    if (move->target != NULL)
    {
        removePiece(move->endX, move->endY);
        PieceChar capturedPiece = move->target->getPieceChar();

        if (capturedPiece == KINGWHITE)
            kingAlive[WHITE] = false;
        else if (capturedPiece == KINGBLACK)
            kingAlive[BLACK] = false;
    }
    Piece *piece = getPiece(move->startX, move->startY);
    if (piece->getIndex() == KINGINDEX)
    {
        int side = static_cast<int>(piece->color);
        for (int i = 0; i < 2; i++)
            castlingValid[side][i] = false;

        if (move->castling)
        {
            int rookStartX;
            int rookEndX;
            if (move->endX == 2)
            {
                rookStartX = 0;
                rookEndX = 3;
            }
            else
            {
                rookStartX = 7;
                rookEndX = 5;
            }

            if (getPiece(rookStartX, piece->y) == NULL)
                move->castling = false;
            else

                doMove(
                    new Move(rookStartX, piece->y, rookEndX, piece->y));
        }
    }
    else if (piece->getIndex() == ROOKINDEX)
    {
        int side = static_cast<int>(piece->color);
        if (piece->x == 0)
            castlingValid[side][0] = false;
        else if (piece->x == 7)
            castlingValid[side][1] = false;
    }
    else if (piece->getIndex() == PAWNINDEX)
    {
        if (move->promotion)
        {
            switch (move->promotionType) {
            case ROOKINDEX:
                piece = new Rook(piece->color);
                break;
            case KNIGHTINDEX:
                piece = new Knight(piece->color);
                break;
            case BISHOPINDEX:
                piece = new Bishop(piece->color);
                break;
            case QUEENINDEX:
            default:
                piece = new Queen(piece->color);
                break;
            }
            piece = new Queen(piece->color);
            piece->x = move->endX;
            piece->y = move->endY;
        }
        else if (move->enPassantTake) {
            int passedPawnYPosition = ((piece->color == WHITE) ? 4 : 3);
            removePiece(move->endX, passedPawnYPosition);
        }
    }
    placePiece(piece, move->endX, move->endY);
    removePiece(move->startX, move->startY);
    this->zobrist->incrementCurrentHash();
}

// assumes valid move
void Board::undoMove(Move *move)
{
    this->zobrist->decrementCurrentHash();
    Piece *piece = getPiece(move->endX, move->endY);
    if (move->promotion)
    {
        piece = new Pawn(piece->color);
        piece->x = move->startX;
        piece->y = move->startX;
    }
    placePiece(piece, move->startX, move->startY);
    removePiece(move->endX, move->endY);
    if (move->target != NULL)
    {
        placePiece(move->target);
        move->setTarget(NULL);
        for (int i = 0; i < 2; i++)
            kingAlive[i] = true;
    }
    else if (move->castling)
    {
        int rookStartX;
        int rookEndX;
        if (move->endX == 2)
        {
            rookStartX = 0;
            rookEndX = 3;
        }
        else
        {
            rookStartX = 7;
            rookEndX = 5;
        }

        undoMove(
            new Move(rookStartX, piece->y, rookEndX, piece->y));
    }
}

Move Board::getBestMove(int depth)
{
    int totalMovesChecked = 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    Move move = minimax(depth, true, turn, -VALUEINFINITE, VALUEINFINITE, false, &totalMovesChecked, e);
    printf("%d\n", totalMovesChecked);
    return move;
}

int Board::evaluateBoard()
{
    return evaluateBoard(this->turn);
}

int Board::evaluateBoard(Color side)
{
    int value = 0;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (!isSquareEmpty(x, y))
            {
                Piece *piece = getPiece(x, y);
                int multiplier = ((piece->color == side) ? 1 : -1);
                value += piece->getValue() * multiplier;
            }
        }
    }

    return value;
}

Move Board::minimax(int depth, bool isMax, Color currentTurn, int a, int b, bool doingHE, int *totalMoves, std::default_random_engine e)
{
    (*totalMoves) += 1;
    Move bestMove;
    Color oppositeColor = ((currentTurn == WHITE) ? BLACK : WHITE);

    // check if the position has occured more than 2 times
    if (this->zobrist->priorInstanceCount.at(this->zobrist->getHash()) >= 3)
    {
        int multiplier = ((currentTurn == turn) ? 1 : -1);
        bestMove.value = VALUEDRAW * multiplier;
        return bestMove;
    }

    if (isMax)
        bestMove.value = -VALUEINFINITE;
    else
        bestMove.value = VALUEINFINITE;
    if (depth == 0 || !kingAlive[currentTurn] || !kingAlive[oppositeColor])
    {

        bestMove.value = evaluateBoard(turn);
        return bestMove;
    }




    std::vector<Move> moves = getAllMoves(currentTurn);
    std::shuffle(moves.begin(), moves.end(), e);

    if (static_cast<int>(moves.size()) == 0)
    {
        int multiplier = ((currentTurn == turn) ? 1 : -1);
        bestMove.value = VALUEDRAW * multiplier;
        return bestMove;
    }
    for (int i = 0; i < static_cast<int>(moves.size()); i++)
    {
        Move move;
        bool castlingLegality[2][2] ={ { false, false }, { false, false } };
        for (int j = 0; j < 2; j++)
            for (int j2 = 0; j2 < 2; j2++)
                castlingLegality[j][j2] = castlingValid[j][j2];

        doMove(&(moves[i]));
        // get enpassant
        if (move.pawnDoubleMove)
            enPassant = move.startX;

        if (depth == 1 && !doingHE && moves[i].target != NULL)
        {
            move = minimax(4, !isMax, oppositeColor, a, b, true, totalMoves, e);
        }
        else
        {
            if (doingHE)
            {
                if (moves[i].target != NULL)
                    move = minimax(depth - 1, !isMax, oppositeColor, a, b, true, totalMoves, e);
                else
                {
                    undoMove(&(moves[i]));
                    continue;
                }
            }
            else
                move = minimax(depth - 1, !isMax, oppositeColor, a, b, false, totalMoves, e);
        }
        undoMove(&(moves[i]));

        for (int j = 0; j < 2; j++)
            for (int j2 = 0; j2 < 2; j2++)
                castlingValid[j][j2] = castlingLegality[j][j2];

        if (isMax && move.value > bestMove.value)
        {
            bestMove = moves[i];
            bestMove.value = move.value;
        }
        else if (!isMax && move.value < bestMove.value)
        {
            bestMove = moves[i];
            bestMove.value = move.value;
        }

        if (isMax)
            a = std::max(bestMove.value, a);
        else
            b = std::min(bestMove.value, b);

        if (a >= b)
            break;
    }
    return bestMove;
}
