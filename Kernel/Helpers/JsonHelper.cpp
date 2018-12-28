#include "JsonHelper.h"
#include "../3rdParties/json/single_include/nlohmann/json.hpp"

bool JsonHelper::IsValidJson(std::string text)
{
	auto json = nlohmann::json::parse(text, nullptr, false);
	return !json.is_discarded();
}