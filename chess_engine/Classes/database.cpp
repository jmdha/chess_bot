#include "Headers/database.h"
#include <stdio.h>

Database::Database(const char* path) {
    // open database
	rc = sqlite3_open(path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // create table if it doesn't exist
    char* errMsg = 0;
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS move_count(hash UNSIGNED INTEGER, move TEXT, count UNSIGNED INTEGER, PRIMARY KEY(hash, move))", nullptr, 0, &errMsg);
}

void Database::closeDatabase() {
    sqlite3_close(db);
}

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void Database::addEntry(unsigned long hash, const char * move) {
    char* errMsg = 0;
    
    std::string stringHash = std::to_string(hash);

    std::string sql =
        "INSERT INTO move_count(hash, move, count)"
        "VALUES(" + stringHash + ", '" + move + "', 1)";

    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);

    if (rc != SQLITE_OK) {
        sql =
            "UPDATE move_count "
            "SET count = count + 1 "
            "WHERE hash = " + stringHash + " AND move = '" + move +"'";

        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
    }

}