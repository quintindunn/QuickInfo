#include <string>

#include <imgui.h>

#include <Windows.h>
#include <thread>
#include <string>
#include <ctime>

#include <clipboardxx.hpp>

#include "render.h"

#include "machineInfo.h"
#include "gui.h"
#include "speedtesting.h"

void render_main(Machine usrMachine);
void render_date_info(void);
void render_ip_info(void);
void render_network_adapters(void);


void copy_to_clipboard_btn(std::string content, int uniqueId) {
	static clipboardxx::clipboard clipboard;

	ImGui::PushID(uniqueId);
	ImGui::SameLine();
	if (ImGui::Button("Copy")) {
		clipboard << content;
		ImGui::SameLine();
		ImGui::Text("Copied!");
	}
	ImGui::PopID();
}

void render_internet_speed() {
	ImGui::NewLine();

	if (!GUIState::running_speedtest) {
		if (ImGui::Button("Run Speed Test")) {
			runSpeedTest();
		}
	}
	else {
		ImGui::Text("Speed Test Running!");
	}


	int networkSpeedsHeight = GUIState::download_speed != -1 ? 27 : 0;
	networkSpeedsHeight += GUIState::upload_speed != -1 ? 27 : 0;

	if (networkSpeedsHeight != 0)
		ImGui::BeginChild("NetworkSpeeds", ImVec2(300, networkSpeedsHeight), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	if (GUIState::download_speed != -1)
		ImGui::Text("Download Speed: %fMbps", GUIState::download_speed);
	if (GUIState::upload_speed != -1)
		ImGui::Text("Upload Speed  : %fMbps", GUIState::upload_speed);

	if (networkSpeedsHeight != 0)
		ImGui::EndChild();

	ImGui::NewLine();
}


void render_main(Machine usrMachine) {
	GUIState::machine = &usrMachine;

	ImGui::Indent(10);
	render_date_info();
	render_ip_info();
	render_internet_speed();
	render_network_adapters();
}

void render_date_info() {
	std::time_t now = std::time(nullptr);
	const std::tm* time_out = std::localtime(&now);

	char buffer[64];
	std::strftime(buffer, sizeof(buffer), "%m/%d/%Y %I:%M:%S %p", time_out);

	ImGui::Text("Date: %s", buffer);
	ImGui::NewLine();
}

void render_ip_info() {
	ImGui::Text("Public IP Address : %s", GUIState::machine->getPublicIpAddress());
	copy_to_clipboard_btn(GUIState::machine->getPublicIpAddress(), 1);
	ImGui::Text("Private IP Address: %s", GUIState::machine->getPrivateIpAddress());
	copy_to_clipboard_btn(GUIState::machine->getPrivateIpAddress(), 2);

}

void render_network_adapters() {
	ImGui::Text("Adapter Count: %d", GUIState::machine->getNetworkAdapters().size());
	ImGui::Checkbox("Show Adapters", &GUIState::showAdapters);
	if (GUIState::showAdapters) {
		ImGui::BeginChild("NetworkAdapterScroll", ImVec2(300, 400), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		for (networkAdapter adapter : GUIState::machine->getNetworkAdapters()) {
			ImGui::BeginChild(adapter.adapterName.c_str(), ImVec2(0, 80), true, 0);
			ImGui::Text("NAME: %s", adapter.adapterName.c_str());
			ImGui::Text("DESC: %s", adapter.adapterDescription.c_str());
			ImGui::Text("ADDR: %s", adapter.adapterAddress.c_str());
			ImGui::Text("IP ADDR: %s", adapter.ipAddress.c_str());
			ImGui::Text("IP MASK: %s", adapter.ipMask.c_str());
			ImGui::Text("GATEWAY: %s", adapter.gateway.c_str());
			ImGui::Text("DHCP ON: %s", adapter.dhcp_enabled ? "TRUE" : "FALSE");

			ImGui::EndChild();

		}
		ImGui::EndChild();
	}

}