#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class config_manager
{
public:
	config_manager(std::string path);
	void read();
	std::string getValue(std::string key);

private:
	std::string path;
	std::unordered_map<std::string, std::string> readValues;

	void handleLine(std::string line);

};

