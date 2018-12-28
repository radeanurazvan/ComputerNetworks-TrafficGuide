#include "ServerScaffolder.h"

#include "Server/Resources/Authentication/AuthenticationController.h"

std::map<std::string, ServerResource*> ServerScaffolder::GetServerResourcesMap() {
    std::map<std::string, ServerResource*> resourcesMap;

    resourcesMap["authenticate"] = new AuthenticationController;

    return resourcesMap;
}

GenericResult<ServerResource*>* ServerScaffolder::ControllerFor(std::string controller) {
    auto serverResourcesMap = this->GetServerResourcesMap();
    auto controllerInMap = serverResourcesMap.find(controller);
    if(controllerInMap == serverResourcesMap.end()) {
        return GenericResult<ServerResource*>::Fail("Controller not found");
    }

    return GenericResult<ServerResource*>::Ok(serverResourcesMap[controller]);
}

GenericResult<std::function<Response(ResourceRequest*)>>* ServerScaffolder::MethodForRequest(ScaffoldingRequest request) {
    auto controllerResult = this->ControllerFor(request.GetController());
    auto method = request.GetMethod();

    return controllerResult->Map<std::function<Response(ResourceRequest*)>>([&method](ServerResource* controller) {
        auto controllerResourceMap = controller->GetResourceMap();
        auto methodInMap = controllerResourceMap.find(method);

        if(methodInMap == controllerResourceMap.end()) {
            return GenericResult<std::function<Response(ResourceRequest*)>>::Fail("Method not found");
        }

        return GenericResult<std::function<Response(ResourceRequest*)>>::Ok(controllerResourceMap[method]);
    });
}