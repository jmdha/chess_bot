#ifndef Database_H
#define Database_H
#include "../../sqlite3.h"
#include <string>
#include <chrono>

class Database
{
public:
	sqlite3* db;
	Database(const char* path);
	void closeDatabase();
	void addEntry(unsigned long hash, const char * move);
	void printProgress();
private:
	int rc;
	std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
};

#endif