#pragma once
#include <tuple>
#include <string>

#include "constants.h"

class pgn_parser
{
public:
	std::tuple<PGNLineInfo, std::string> parseLine(std::string line);

private:
	PGNLineType identifyLine(std::string line);
	PGNLineInfo identifyLine(std::string line, PGNLineType type);
	PGNLineInfo identifyLineInfo(std::string line);
	std::string evaluateLineValue(std::string line, PGNLineType type);
};

