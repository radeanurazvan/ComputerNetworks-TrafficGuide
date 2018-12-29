#include "ServerScaffolder.h"
#include "Server/Resources/Cars/CarsController.h"

std::map<std::string, ServerResource*> ServerScaffolder::GetServerResourcesMap() {
    std::map<std::string, ServerResource*> resourcesMap;

    resourcesMap["cars"] = new CarsController();

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

GenericResult<ControllerResourceAdapter*>* ServerScaffolder::MethodAdapterForRequest(ScaffoldingRequest request) {
    auto controllerResult = this->ControllerFor(request.GetController());
    auto method = request.GetMethod();

    return controllerResult->Map<ControllerResourceAdapter*>([&method](ServerResource* controller) {
        auto controllerAdaptersMap = controller->GetAdaptersMap();
        auto adapterInMap = controllerAdaptersMap.find(method);

        if(adapterInMap == controllerAdaptersMap.end()) {
            return GenericResult<ControllerResourceAdapter*>::Fail("Method not found");
        }

        auto adapter = controllerAdaptersMap[method];
        return GenericResult<ControllerResourceAdapter*>::Ok(adapter);
    });
}