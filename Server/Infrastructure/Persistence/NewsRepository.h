#pragma once

#include <vector>
#include "Server/Domain/News/NewsMessage.h"

class NewsRepository {
    private:
        NewsRepository();
    public:
        static std::vector<NewsMessage*> GetAll();
};