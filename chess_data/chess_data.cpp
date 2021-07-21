
#include <iostream>
#include <unordered_map>
#include <sstream>

#include "api.h"
#include "config_manager.h"
#include "constants.h"
#include "pgn_reader.h"
#include "pgn_hasher.h"

api* API;

void callbackOnMatch(std::unordered_map<PGNLineInfo, std::string> matchInformation) {
	std::stringstream ss;

	auto old_buf = std::cout.rdbuf(ss.rdbuf());

	hashMoves(matchInformation[PGNLineInfo::MOVES]);

	std::cout.rdbuf(old_buf);

	std::string result = ss.str();

	std::string hash = "";
	std::string move = "";

	bool foundSpace = false;
	
	for (int i = 0; i < result.length(); i++) {
		if (result[i] == '\n') {
			API->incrementEntry(std::atoi(hash.c_str()), move);
			hash = "";
			move = "";
			foundSpace = false;
		}
		else if (result[i] == ' ')
			foundSpace = true;
		else if (foundSpace) {
			move += result[i];
		}
		else {
			hash += result[i];
		}

	}
}

int main()
{
	config_manager cfgManager = config_manager("config.txt");
	cfgManager.read();
	API = new api(
		cfgManager.getValue("IP"),
		cfgManager.getValue("PORT"),
		cfgManager.getValue("USER_NAME"),
		cfgManager.getValue("USER_PASSWORD"),
		cfgManager.getValue("SCHEMA_NAME"),
		cfgManager.getValue("TABLE_NAME")
	);
	pgn_reader reader = pgn_reader();
	reader.readFile("F:/Chess Data/lichess_db_standard_rated_2021-06.pgn", &callbackOnMatch);
}