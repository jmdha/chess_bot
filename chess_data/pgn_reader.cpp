#include "pgn_reader.h"

void pgn_reader::readFile(std::string path, void (*callbackOnMatch)(std::unordered_map<PGNLineInfo, std::string> matchInformation)) {
	std::fstream PGNFile;
	PGNFile.open(path, std::ios::in);
	if (PGNFile.is_open()) {
		std::unordered_map<PGNLineInfo, std::string> matchInfo;
		std::string line;
		bool foundMoves = false;
		while (std::getline(PGNFile, line)) {
			std::tuple<PGNLineInfo, std::string> parsedLine = parser.parseLine(line);
			if (std::get<0>(parsedLine) == PGNLineInfo::NONE && foundMoves) {
				callbackOnMatch(matchInfo);
				matchInfo.clear();
				foundMoves = false;
				continue;
			}
			else if (std::get<0>(parsedLine) == PGNLineInfo::MOVES)
				foundMoves = true;

			if (std::get<0>(parsedLine) != PGNLineInfo::NONE)
				matchInfo.emplace(std::get<0>(parsedLine), std::get<1>(parsedLine));
		}
		PGNFile.close();
	}
}