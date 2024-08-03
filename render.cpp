#include <string>

#include <imgui.h>

#include <Windows.h>
#include <thread>
#include <string>

#include <clipboardxx.hpp>

#include "machineInfo.h"
#include "gui.h"

void render_main(Machine usrMachine);
void render_ip_info(void);
void render_network_adapters(void);

namespace GUIState {
	bool showAdapters = false;
	Machine* machine;
};

void copy_to_clipboard_btn(std::string content, int uniqueId) {
	static clipboardxx::clipboard clipboard;

	ImGui::PushID(uniqueId);
	ImGui::SameLine();
	if (ImGui::Button("Copy")) {
		clipboard << content;
	}
	ImGui::PopID();
}

void render_main(Machine usrMachine) {
	GUIState::machine = &usrMachine;

	ImGui::Indent(10);
	render_ip_info();
	render_network_adapters();
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