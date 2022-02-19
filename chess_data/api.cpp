#include "api.h"

api::api(std::string ip,
	std::string port,
	std::string username,
	std::string password,
	std::string schemaName,
	std::string tableName) {
	this->ip = ip;
	this->port = port;
	this->username = username;
	this->password = password;
	this->schemaName = schemaName;
	this->tableName = tableName;
}

bool api::incrementEntry(int hash, std::string move) {
	std::string query = 
		"INSERT INTO `" + this->tableName + "` (hash, move, count)"
		"VALUES(" + std::to_string(hash) + ", '" + move + "', 1)"
		"ON DUPLICATE KEY UPDATE `count` = `count` + 1";
	return executeUpdateQuery(query);
}

bool api::executeUpdateQuery(std::string query) {
	/*
	try {
		
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		int rowsChanged = 0;

		driver = get_driver_instance();
		
		con = driver->connect("tcp://" + this->ip + ":" + this->port,
			this->username,
			this->password);

		con->setSchema(this->schemaName);

		stmt = con->createStatement();

		rowsChanged = stmt->executeUpdate(query);

		delete stmt;
		delete con;

		if (rowsChanged != 1)
			throw std::exception("Duplicate rows");
		else
			return true;
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
	catch (std::exception& e) {
		return false;
	}
	*/
}