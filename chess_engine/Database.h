#ifndef Database_H
#define Database_H
#include "sqlite3.h"
class Database
{
	sqlite3* db;
	int rc;

	Database(const char *path);
};

#endif