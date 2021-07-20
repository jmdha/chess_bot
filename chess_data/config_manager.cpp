#include "config_manager.h"

config_manager::config_manager(std::string path) {
	this->path = path;
}

void config_manager::read() {
	std::fstream configFile;
	configFile.open(this->path, std::ios::in);
	if (configFile.is_open()) {
		std::string line;
		while (std::getline(configFile, line)) {
			handleLine(line);
		}
		configFile.close();
	}
}

std::string config_manager::getValue(std::string key) {
	return readValues[key];
}

void config_manager::handleLine(std::string line) {
	// If comment or empty line
	if (line.length() == 0 || line[0] == '#')
		return;

	std::string key = "";
	std::string value = "";
	int i = 0;
	bool foundEq = false;
	while (i < line.length()) {
		if (line[i] == '=')
			foundEq = true;
		else if (!foundEq)
			key += line[i];
		else
			value += line[i];
		i++;
	}
	readValues.emplace(key, value);
}