
#include <iostream>

#include "config_manager.h"
#include "api.h"

int main()
{
	config_manager cManager = config_manager("config.txt");
	cManager.read();
	api API = api();
	API.incrementEntry(cManager, 45, "a2a4");
}