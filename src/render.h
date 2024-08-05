#pragma once
#include "machineInfo.h"

namespace GUIState {
	inline bool showAdapters = false;
	inline Machine* machine;
	inline float download_speed = -1;
	inline float upload_speed = -1;
	inline bool running_speedtest = false;
};

void render_main(Machine usrMachine);