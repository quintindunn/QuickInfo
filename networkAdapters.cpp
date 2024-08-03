#include "networkAdapters.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

std::vector<networkAdapter> networkAdapters() {
	std::vector<networkAdapter> adapters;

	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	std::cout << 0 << std::endl;

	if (GetAdaptersInfo(NULL, &dwSize) == ERROR_BUFFER_OVERFLOW) {
		PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(dwSize);
		std::cout << 1 << std::endl;


		if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &dwSize)) == NO_ERROR) {
			PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
			std::cout << 2 << std::endl;

			while (pAdapter) {
				std::cout << 3 << std::endl;
				networkAdapter adapter;

				std::ostringstream adapterAddr;

				for (UINT i = 0; i < pAdapter->AddressLength; i++) {
					if (i > 0) {
						adapterAddr << "-";
					}
					adapterAddr << std::setw(2) << std::setfill('0') << std::hex << (int)pAdapter->Address[i];
				}

				adapter.adapterName = pAdapter->AdapterName;
				adapter.adapterDescription = pAdapter->Description;
				adapter.adapterAddress = adapterAddr.str();

				if (pAdapter->IpAddressList.IpAddress.String[0] != '\0') {
					adapter.ipAddress = pAdapter->IpAddressList.IpAddress.String;
				}
				else {
					adapter.ipAddress = "N/A";
				}

				// Get IP mask
				if (pAdapter->IpAddressList.IpMask.String[0] != '\0') {
					adapter.ipMask = pAdapter->IpAddressList.IpMask.String;
				}
				else {
					adapter.ipMask = "N/A";
				}

				// Get Gateway
				if (pAdapter->GatewayList.IpAddress.String[0] != '\0') {
					adapter.gateway = pAdapter->GatewayList.IpAddress.String;
				}
				else {
					adapter.gateway = "N/A";
				}

				adapter.dhcp_enabled = pAdapter->DhcpEnabled;

				adapters.push_back(adapter);

				pAdapter = pAdapter->Next;
			}
		}

	}

	std::cout << "Completed!" << std::endl;
	return adapters;
}


