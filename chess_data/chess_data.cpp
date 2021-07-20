#include "jdbc/mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

#include "config_manager.h"

bool incrementEntry(config_manager cManager, int hash, std::string move);

int main()
{
	config_manager cManager = config_manager("config.txt");
	cManager.read();
	incrementEntry(cManager, 45, "a2a4");
}

bool incrementEntry(config_manager cManager, int hash, std::string move) {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		int rowsChanged = 0;

		driver = get_driver_instance();
		std::cout << "Hello World!\n";
		con = driver->connect("tcp://" + cManager.getValue("IP") + ":" + cManager.getValue("PORT"), 
			cManager.getValue("USER_NAME"), 
			cManager.getValue("USER_PASSWORD"));

		con->setSchema(cManager.getValue("SCHEMA_NAME"));

		stmt = con->createStatement();

		rowsChanged = stmt->executeUpdate(
			"INSERT INTO `" + cManager.getValue("TABLE_NAME") + "` (hash, move, count)" 
			"VALUES(" + std::to_string(hash) +", '" + move + "', 1)" 
			"ON DUPLICATE KEY UPDATE `count` = `count` + 1"
		);

		delete stmt;
		delete con;

		if (rowsChanged != 1)
			throw std::exception("Duplicate rows");
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	catch (std::exception& e) {

	}
}
