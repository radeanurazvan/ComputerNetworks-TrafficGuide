#include "JsonHelper.h"
#include "Kernel/3rdParties/json.hpp"

bool JsonHelper::IsValidJson(std::string text)
{
	auto json = nlohmann::json::parse(text, nullptr, false);
	return !json.is_discarded();
}