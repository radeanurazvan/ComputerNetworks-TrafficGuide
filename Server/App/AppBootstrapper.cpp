#include "AppBootstrapper.h"

#include "Server/Domain/News/Jobs/NewsJobs.h"
#include "Server/Domain/Car/CarEvents.h"

void AppBootstrapper::Bootstrap() {
    CarEvents::Setup();

    NewsJobs::Setup();
}