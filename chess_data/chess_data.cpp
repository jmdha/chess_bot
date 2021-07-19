#include "jdbc/mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

bool incrementEntry(int hash, std::string move);

int main()
{
	incrementEntry(2, "a");
}

bool incrementEntry(int hash, std::string move) {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		int rowsChanged = 0;

		driver = get_driver_instance();
		std::cout << "Hello World!\n";
		con = driver->connect("tcp://127.0.0.1:3306", "chess", "chess");

		con->setSchema("chess_data");

		stmt = con->createStatement();

		rowsChanged = stmt->executeUpdate(
			"INSERT INTO `move_frequency` (hash, move, count)" 
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
