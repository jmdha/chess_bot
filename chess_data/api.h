#pragma once
#include "jdbc/mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "config_manager.h"

class api
{
public:
	bool incrementEntry(config_manager cManager, int hash, std::string move);
};

