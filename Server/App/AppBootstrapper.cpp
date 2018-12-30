#include "AppBootstrapper.h"

#include "Server/Domain/News/Jobs/NewsJobs.h"

void AppBootstrapper::Bootstrap() {
    NewsJobs::Setup();
}