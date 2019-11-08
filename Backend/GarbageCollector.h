#pragma once

#include "../MiddleEnd/Object.h"

class GarbageCollector {
private:
    Object *first = nullptr;
    Object *last = nullptr;
public:
    void add(Object *obj);
    void clean(Object *obj);
    void cleanAll();
};
