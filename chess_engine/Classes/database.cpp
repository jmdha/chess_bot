#include "Headers/database.h"
#include <stdio.h>

sqlite3* tempdb;

Database::Database(const char* path) {
    // open database
	rc = sqlite3_open(path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    tempdb = db;

    // create table if it doesn't exist
    char* errMsg = 0;
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS move_count(hash UNSIGNED INTEGER, move TEXT, count UNSIGNED INTEGER, PRIMARY KEY(hash, move))", nullptr, 0, &errMsg);
}

void Database::closeDatabase() {
    sqlite3_close(db);
}

std::string tempHash;
const char* tempMove;

void Database::addEntry(unsigned long hash, const char * move) {
    char* errMsg = 0;
    std::string stringHash = std::to_string(hash);
    tempHash = stringHash;
    tempMove = move;
    
    

    std::string sql = "INSERT INTO move_count(hash, move, count) "
        "VALUES(" + stringHash + ", '" + move + "', 1) "
        "ON CONFLICT(hash, move) WHERE true "
        "DO UPDATE SET count = excluded.count + 1";

    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);

}

long timeDiff;

static int callback(void* data, int argc, char** argv, char** azColName) {
    printf("Time taken: %lu\n", timeDiff);
    printf("Entry rate: %lu\n", std::stoi(argv[0]) / timeDiff);
    return 0;
}

void Database::printProgress() {
    char* errMsg = 0;
    std::string sql = "SELECT SUM(count) from move_count";
    timeDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000000 / 1000;
    sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
}