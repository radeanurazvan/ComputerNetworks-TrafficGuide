#include "time.h"
#include "NewsJobs.h"

#include "Kernel/Jobs/Seconds.h"
#include "Kernel/Jobs/RecurrentJobs.h"
#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/Persistence/NewsRepository.h"
#include "Server/Infrastructure/Persistence/CarRepository.h"

void NewsJobs::Setup() {
    RecurrentJobs::Schedule([]() {
        auto news = NewsRepository::GetAll();
        auto cars = CarRepository::GetAll();
        srand (time(0));

        printf("\n");
        for(int i = 1; i <= 3; i++) {
            auto index = rand() % news.size();   
            auto message = news[index];

            printf("[server] Notifying news: %s\n", message->GetMessage().c_str());
            for(auto car: cars) {
                if(car->IsInterestedIn(message)) {
                    Server::WriteToClient(car->GetSocket(), Response::Notification(message->GetMessage()));
                }
            }
        }
    }, Seconds::FromMinutes(2));
}