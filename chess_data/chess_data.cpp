
#include <iostream>

#include "config_manager.h"
#include "api.h"

int main()
{
	config_manager cManager = config_manager("config.txt");
	cManager.read();
	api API = api(
		cManager.getValue("IP"), 
		cManager.getValue("PORT"), 
		cManager.getValue("USER_NAME"), 
		cManager.getValue("USER_PASSWORD"),
		cManager.getValue("SCHEMA_NAME"),
		cManager.getValue("TABLE_NAME"));
	API.incrementEntry(cManager, 46, "a2a4");
}