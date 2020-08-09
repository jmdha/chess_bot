#ifndef Constants_H
#define Constants_H

#define WIDTH 8
#define HEIGHT 8

// Colors has to be in the range 0-1 (used in zobrist init)
enum Color
{
    WHITE,
    BLACK
};

enum PawnRow
{
    PAWNROWWHITE = 1,
    PAWNROWBLACK = 6
};

enum BackRow
{
    BACKROWWHITE = 0,
    BACKROWBLACK = 7
};

enum File : char {
    FILEA = 'a',
    FILEB = 'b',
    FILEC = 'c',
    FILED = 'd',
    FILEE = 'e',
    FILEF = 'f',
    FILEG = 'g',
    FILEH = 'h'
};

enum PieceChar
{
    PAWNWHITE = 'P',
    PAWNBLACK = 'p',
    ROOKWHITE = 'R',
    ROOKBLACK = 'r',
    KNIGHTWHITE = 'N',
    KNIGHTBLACK = 'n',
    BISHOPWHITE = 'B',
    BISHOPBLACK = 'b',
    QUEENWHITE = 'Q',
    QUEENBLACK = 'q',
    KINGWHITE = 'K',
    KINGBLACK = 'k',
    BLANK = ' '
};

enum PieceIndex {
    PAWNINDEX,
    ROOKINDEX,
    KNIGHTINDEX,
    BISHOPINDEX,
    QUEENINDEX,
    KINGINDEX,
    NONEINDEX
};

// Must be 1-9 - as the king/queen getpossiblemoves is dependent on it
enum Direction
{
    NORTH = 8,
    SOUTH = 2,
    EAST = 6,
    WEST = 4,
    NORTHEAST = 9,
    NORTHWEST = 7,
    SOUTHEAST = 3,
    SOUTHWEST = 1

};

enum Value : int
{
    VALUEDRAW = 10000,
    VALUEMATE = 32000,
    VALUEINFINITE = 64000,

    VALUEPAWN = 100,
    VALUEKNIGHT = 320,
    VALUEBISHOP = 330,
    VALUEROOK = 500,
    VALUEQUEEN = 900,

    VALUELIMITMID = 8 * VALUEPAWN + 2 * VALUEKNIGHT + 2 * VALUEBISHOP + 2 * VALUEROOK + 1 * VALUEQUEEN
};

const int VALUEPAWNPOS[WIDTH][HEIGHT] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5, 5, 10, 25, 25, 10, 5, 5},
    {0, 0, 0, 20, 20, 0, 0, 0},
    {5, -5, -10, 0, 0, -10, -5, 5},
    {5, 10, 10, -20, -20, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0},
};

const int VALUEKNIGHTPOS[WIDTH][HEIGHT] = {
    {-50, -40,-30,-30,-30,-30,-40,-50},
    {-40,-20,0,0,0,0,-20,-40},
    {-30,0,10,15,15,10,0,-30},
    {-30,5,15,20,20,15,5,-30},
    {-30,0,15,20,20,15,0,-30},
    {-30,5,10,15,15,10,5,-30},
    {-40,-20,0,5,5,0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

const int VALUEBISHOPPOS[WIDTH][HEIGHT] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,0,0,0,0,0,0,-10},
    {-10,0,5,10,10,5,0,-10},
    {-10,5,5,10,10,5,5,-10},
    {-10,0,10,10,10,10,0,-10},
    {-10,10,10,10,10,10,10,-10},
    {-10,5,0,0,0,0,5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

const int VALUEROOKPOS[WIDTH][HEIGHT] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {5, 10, 10, 10, 10, 10, 10, 5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {0, 0, 0, 5, 5, 0, 0, 0}
};

const int VALUEQUEENPOS[WIDTH][HEIGHT] = {
    {-20,-10,-10,-5,-5,-10,-10,-20},
    {-10,0,0,0,0,0,0,-10},
    {-10,0,5,5,5,5,0,-10},
    {-5,0,5,5,5,5,0,-10},
    {0,0,5,5,5,5,0,-5},
    {-10,5,5,5,5,5,0,-10},
    {-10,0,5,0,0,0,0,-10},
    {-20,-10,-10,-5,-5,-10,-10,-20}
};

const int VALUEKINGPOSMID[WIDTH][HEIGHT] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-20,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20,20,0,0,0,0,20,20},
    {20,30,0,0,0,0,30,20}
};

const int VALUEKINGPOSEND[WIDTH][HEIGHT] = {
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,0,0,-10,-20,-30},
    {-30,-10,20,30,30,20,-10,-30},
    {-30,-10,30,40,40,30,-10,-30},
    {-30,-10,30,40,40,30,-10,-30},
    {-30,-10,20,30,30,20,-10,-30},
    {-30,-30,0,0,0,0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
};

#endif