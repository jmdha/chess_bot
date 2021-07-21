#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <tuple>

#include "constants.h"
#include "pgn_parser.h"

class pgn_reader
{
public:
	void readFile(std::string path, void (*callbackOnMatch)(std::unordered_map<PGNLineInfo, std::string> matchInformation));
private:
	std::string path;
	pgn_parser parser;

};

