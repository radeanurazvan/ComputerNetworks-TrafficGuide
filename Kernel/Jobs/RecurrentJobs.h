#pragma once
#include <functional>

class RecurrentJobs {
    private:
        RecurrentJobs();
    public:
        static void Schedule(std::function<void()> jobHandler, int seconds);
};