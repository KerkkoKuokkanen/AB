
#include "../../hdr/ab.h"
#include "../../hdr/global.h"
#include <thread>
#include <atomic>
#include <condition_variable>

std::atomic<bool> aiThreadRunning{false};
std::thread aiThread;
std::mutex aiMutex;
std::condition_variable aiCV;

void StartAiThread()
{
	if (!aiThreadRunning)
	{
		aiThreadRunning = true;
		aiThread = std::thread([]() {
			while (true)
			{
				AiManagerUpdate();
				{
					std::unique_lock<std::mutex> lock(aiMutex);
					if (!aiThreadRunning)
						break;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(2));
			}
		});
	}
}

void StopAiThread()
{
	if (aiThreadRunning)
	{
		{
			std::unique_lock<std::mutex> lock(aiMutex);
			aiThreadRunning = false;
		}
		aiCV.notify_one();
		if (aiThread.joinable())
			aiThread.join();
	}
}
