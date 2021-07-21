#pragma once
#include "jdbc/mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>

#include "config_manager.h"

class api
{
public:
	api(std::string ip,
		std::string port,
		std::string username,
		std::string password,
		std::string schemaName,
		std::string tableName);
	bool incrementEntry(int hash, std::string move);

private:
	std::string ip;
	std::string port;
	std::string username;
	std::string password;
	std::string schemaName;
	std::string tableName;

	bool executeUpdateQuery(std::string query);
};

