#ifndef Generic_Helper_Functions_H
#define Generic_Helper_Functions_H

#include <string>
#include "move.h"

bool isNumber(char charToCheck);

int getColumnAsNumber(char column);

int getRowAsNumber(char row);

bool isLowercase(char charToCheck);

std::string getStatString(Move move, int64_t duration, int depth, int pieceCount);

#endif