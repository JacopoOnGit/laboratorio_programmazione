
#ifndef LABORATORIO_PROGRAMMAZIONE_RESOURCE_LOADER_H
#define LABORATORIO_PROGRAMMAZIONE_RESOURCE_LOADER_H

#include <vector>
#include <string>
#include "observer.h"

class ResourceLoader {
public:
    void addObserver(IObserver* obs);
    void loadFiles(const std::vector<std::string>& filePaths);

private:
    std::vector<IObserver*> observers;
    void notify(float progress, const std::string& fileName);
};

#endif //LABORATORIO_PROGRAMMAZIONE_RESOURCE_LOADER_H