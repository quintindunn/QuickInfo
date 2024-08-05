#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 200

#define WINDOW_NAME L"Machine Information"
#define GUI_NAME "Machine Information"

#include <iostream>
#include <string>

#include <imgui.h>

#include <Windows.h>
#include <thread>
#include <string>

#include <clipboardxx.hpp>

#include "machineInfo.h"
#include "gui.h"
#include "render.h"
#include "config.h"

Machine* usrMachine;


INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE previousInstance, PSTR arguments, INT cmd_show) {
	#ifdef DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	#endif

	usrMachine = new Machine{};
	usrMachine->queryNetworkAdapters();
	usrMachine->queryPublicIpAddress();

	buildWindow(instance, previousInstance, arguments, cmd_show, *usrMachine);

}