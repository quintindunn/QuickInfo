#pragma once

#include <string>
#include <vector>
#include "networkAdapters.h"

class Machine {
private:
	std::string publicIpAddress = "N/A";
	std::string privateIpAddress = "N/A";
	
	std::vector<networkAdapter> adapters;
public:
	std::string getPublicIpAddress(void);
	std::string getPrivateIpAddress(void);
	std::vector<networkAdapter> getNetworkAdapters(void);
	

	void queryPublicIpAddress(void);
	void queryNetworkAdapters(void);
};
