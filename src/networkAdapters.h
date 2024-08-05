#pragma once
#include <string>
#include <vector>

using std::string;


class networkAdapter {
public:
	string adapterName;
	string adapterDescription;
	string adapterAddress;
	string ipAddress;
	string ipMask;
	string gateway;
	bool dhcp_enabled;
};

std::vector<networkAdapter> networkAdapters(void);