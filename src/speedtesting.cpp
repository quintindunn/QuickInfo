#include <thread>

#include "render.h"
#include "external/InternetSpeedTest/speedtester.h"

void speedTestWorker() {
	GUIState::running_speedtest = true;
	float* results = speedtest();
	GUIState::download_speed = results[0];
	GUIState::upload_speed = results[1];
	GUIState::running_speedtest = false;

}

void runSpeedTest() {
	std::thread t(speedTestWorker);
	t.detach();
}