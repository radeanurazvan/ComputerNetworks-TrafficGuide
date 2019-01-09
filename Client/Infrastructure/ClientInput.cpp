#include "ClientInput.h"
#include <cstring>

ClientInput::ClientInput(std::string resource, std::map<std::string, std::string> parameters) {
    this->resource = resource;
    this->parameters = parameters;
}

GenericResult<ClientInput*>* ClientInput::Create(std::string input) {
    const char* partSeparator = " ";
    const char* parameterSeparator = "; ";
    const char* valueSeparator = ":";

    auto spacePosition = input.find(partSeparator);
    auto resource = input.substr(0, spacePosition);
    std::map<std::string, std::string> parameters;

    auto parametersString = input.substr(spacePosition+1, input.size() -1);
    while(parametersString.size() > strlen(parameterSeparator)) {
        int delimiterPosition = parametersString.find(parameterSeparator);

        if(delimiterPosition == -1) {
            return GenericResult<ClientInput*>::Fail("Bad command format!");
        } 

        auto parameterGroup = parametersString.substr(0, delimiterPosition);
        auto valueDelimiterPosition = parameterGroup.find(valueSeparator);

        auto paramName = parameterGroup.substr(0, valueDelimiterPosition);
        auto paramValue = parameterGroup.substr(valueDelimiterPosition + strlen(valueSeparator), 
                            parameterGroup.size() - strlen(valueSeparator));
        
        parameters[paramName] = paramValue;        
        parametersString.erase(0, delimiterPosition + strlen(parameterSeparator));
    }

    return GenericResult<ClientInput*>::Ok(new ClientInput(resource, parameters));
}

std::string ClientInput::GetResource() {
    return this->resource;
}

std::map<std::string, std::string> ClientInput::GetParameters() {
    return this->parameters;
}