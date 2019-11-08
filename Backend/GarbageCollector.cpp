#include "GarbageCollector.h"

void GarbageCollector::add(Object *obj) {
    //  no Objects
    if(first == nullptr) {
        first = obj;
        return;
    }
    //  one Object
    if(last == nullptr) {
        last = obj;
        first->next = obj;
        obj->prev = first;
        return;
    }
    //  more than one Object
    last->next = obj;
    obj->prev = last;
    last = obj;
}
void GarbageCollector::clean(Object *obj) {
    //  object in middle somewhere
    if(obj->next != nullptr && obj->prev != nullptr) {
        obj->next->prev = obj->prev;
        obj->prev->next = obj->next;
    }
    //  object is first
    if(obj->next != nullptr) {
        obj->next->prev = nullptr;
        first = obj->next;
    }
    //  object is last
    if(obj->prev != nullptr) {
        obj->prev->next = nullptr;
        last = obj->prev;
    }

    delete obj;
}
void GarbageCollector::cleanAll() {
    Object *curr = first;
    if(curr == nullptr)
        return;
    while(curr->next != nullptr) {
        curr = curr->next;
        delete curr->prev;
    }
}