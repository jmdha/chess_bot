#include "Database.h"

Database::Database(const char* path) {
	rc = sqlite3_open(path, &db);
}