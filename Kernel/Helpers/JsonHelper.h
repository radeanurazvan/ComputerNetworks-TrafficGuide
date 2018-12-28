#pragma once
#include <string>
#include "../3rdParties/json/single_include/nlohmann/json.hpp"

class JsonHelper
{
public:
	static bool IsValidJson(std::string text);

	template <class T>
	static std::string Serialize(T subject);
	template <class T>
	static T  Parse(std::string text);
	template <class T>	
	static bool  CanParse(std::string text);
};

template <class T>
std::string JsonHelper::Serialize(T subject) {
	nlohmann::json j = subject;
	return j.dump();
}

template<class T>
T JsonHelper::Parse(std::string text)
{
	auto json = nlohmann::json::parse(text);
	return json.get<T>();
}

template<class T>
bool JsonHelper::CanParse(std::string text)
{
	auto json = nlohmann::json::parse(text, nullptr, false);
	try {
		auto jsonAsType = json.get<T>();
		return true;
	} catch(...) {
		return false;
	}
}