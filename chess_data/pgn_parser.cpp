#include "pgn_parser.h"

std::tuple<PGNLineInfo, std::string> pgn_parser::parseLine(std::string line) {
	PGNLineType type = identifyLine(line);
	PGNLineInfo info = identifyLine(line, type);

	std::string value = evaluateLineValue(line, type);

	std::tuple<PGNLineInfo, std::string> parsedLine = std::tuple<PGNLineInfo, std::string>(info, value);
	return parsedLine;
}

PGNLineType pgn_parser::identifyLine(std::string line) {
	if (line.length() == 0)
		return PGNLineType::NONE;
	else if (line[0] == '[')
		return PGNLineType::INFO;
	else
		return PGNLineType::MOVES;
}

PGNLineInfo pgn_parser::identifyLine(std::string line, PGNLineType type) {
	switch (type)
	{
	case PGNLineType::NONE:
		return PGNLineInfo::NONE;
	case PGNLineType::INFO:
		return identifyLineInfo(line);
	case PGNLineType::MOVES:
		return PGNLineInfo::MOVES;
	default:
		break;
	}
}

PGNLineInfo pgn_parser::identifyLineInfo(std::string line) {
	switch (line[1])
	{
	case 'B':
		if (line[6] == ' ')
			return PGNLineInfo::BLACK;
		else if (line[6] == 'E')
			return PGNLineInfo::BLACKELO;
		else if (line[6] == 'R')
			return PGNLineInfo::BLACKRATINGDIFF;
		else
			return PGNLineInfo::BLACKTITLE;

	case 'D':
		return PGNLineInfo::DATE;

	case 'E':
		if (line[2] == 'v')
			return PGNLineInfo::EVENT;
		else
			return PGNLineInfo::ECO;

	case 'O':
		return PGNLineInfo::OPENING;

	case 'R':
		if (line[2] == 'o')
			return PGNLineInfo::ROUND;
		else
			return PGNLineInfo::RESULT;

	case 'S':
		return PGNLineInfo::SITE;
		break;

	case 'T':
		if (line[2] == 'i')
			return PGNLineInfo::TIMECONTROL;
		else
			return PGNLineInfo::TERMINATION;

	case 'U':
		if (line[4] == 'D')
			return PGNLineInfo::UTCDATE;
		else
			return PGNLineInfo::UTCTIME;

	case 'W':
		if (line[6] == ' ')
			return PGNLineInfo::WHITE;
		else if (line[6] == 'E')
			return PGNLineInfo::WHITEELO;
		else if (line[6] == 'R')
			return PGNLineInfo::WHITERATINGDIFF;
		else
			return PGNLineInfo::WHITETITLE;
	default:
		throw std::exception(("Unknown type: " + line).c_str());
		break;
	}

	
}

std::string pgn_parser::evaluateLineValue(std::string line, PGNLineType type) {
	std::string value = "";
	int i = 0;
	bool foundQuote = false;
	switch (type)
	{
	case PGNLineType::NONE:
		break;
	case PGNLineType::INFO:
		while (i < line.length() - 1) {
			if (line[i] == '\"')
				if (foundQuote)
					break;
				else
					foundQuote = true;
			else if (foundQuote)
				value += line[i];
			i++;
		}
		break;
	case PGNLineType::MOVES:
		value = line;
		break;
	default:
		throw std::exception(("Unknown type: " + line).c_str());
		break;
	}
	return value;
}