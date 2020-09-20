#ifndef Database_H
#define Database_H
#include "../../sqlite3.h"
#include <string>
class Database
{
public:
	Database(const char* path);
	void closeDatabase();
	void addEntry(unsigned long hash, const char * move);
private:
	sqlite3* db;
	int rc;
	
};

#endif