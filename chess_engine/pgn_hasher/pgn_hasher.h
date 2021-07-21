// MathLibrary.h - Contains declarations of math functions
#pragma once

#include <string>

#include "Headers/board.h"

#ifdef PGNHASHER_EXPORTS
#define PGNHASHER_API __declspec(dllexport)
#else
#define PGNHASHER_API __declspec(dllimport)
#endif

extern "C" PGNHASHER_API void hashMoves(std::string moves);