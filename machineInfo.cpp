#include <string>
#include <curl/curl.h>
#include <iostream>

#include "machineInfo.h"
#include "networkAdapters.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string Machine::getPublicIpAddress() {
	return this->publicIpAddress;
}

std::string Machine::getPrivateIpAddress() {
	return this->privateIpAddress;
}

std::vector<networkAdapter> Machine::getNetworkAdapters() {
	return this->adapters;
}

void Machine::queryPublicIpAddress() {
	CURL* curl;
	CURLcode res;
	std::string readBuff;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org/");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuff);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	this->publicIpAddress = readBuff;
}

void Machine::queryNetworkAdapters() {
	std::vector<networkAdapter> adapters;
	adapters = networkAdapters();
	
	// Set adapters
	this->adapters = adapters;

	if (adapters.size() > 0) {
		// Set (assumed) private ip address
		networkAdapter mainAdapter = adapters.at(0);
		this->privateIpAddress = mainAdapter.ipAddress;
	}

}