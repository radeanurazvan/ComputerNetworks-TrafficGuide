#include "RecurrentJobs.h"

#include <thread>

void RecurrentJobs::Schedule(std::function<void()> jobHandler, int seconds) {
    auto handlingThread = std::thread([jobHandler, seconds]() {
        while(true) {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            jobHandler();
        }
    });
    handlingThread.detach();
}