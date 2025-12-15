//
// Created by Jacopo Cutrignelli on 15/12/25.
//

#ifndef LABORATORIO_PROGRAMMAZIONE_OBSERVER_H
#define LABORATORIO_PROGRAMMAZIONE_OBSERVER_H

#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onProgressUpdate(float progress,
                                  const std::string& currentFile) = 0;
};

#endif //LABORATORIO_PROGRAMMAZIONE_OBSERVER_H