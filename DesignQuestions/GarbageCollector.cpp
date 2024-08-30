#include <iostream>
#include <vector>

using namespace std;

class GCObject {
    GCObject* ref;
    GarbageCollector* gcRef;
    bool isMarked;
public:
    GCObject() : ref(nullptr), isMarked(false), gcRef() {
        gcRef->addHeapObject(this);
    }

    void setRef(GCObject* refObj) { 
        this->ref = refObj;
    }

    GCObject* getRef() {
        return this->ref;
    }

    void mark(bool marker) {
        this->isMarked = marker;
    }

    bool marked() {
        return this->isMarked;
    }
};

class GarbageCollector {
    vector<GCObject*> heap, root;
public:
    GarbageCollector() {
    }

    void addHeapObject(GCObject* obj) {
        this->heap.push_back(obj);
    }

    void markRef(GCObject* obj) {
        if(obj->getRef() == nullptr) {
            return;
        }

        if(!(obj->getRef()->marked())) {
            obj->getRef()->mark(true);
            markRef(obj->getRef());
        }
    }

    void markAll() {
        for(auto obj: root) {
            if(!obj->marked()) {
                obj->mark(true);
                markRef(obj);
            }
        }
    }

    void sweep() {
        for(auto iter = heap.begin(); iter != heap.end();) {
            if(!((*iter)->marked())) {
                delete *iter;
                *iter = nullptr;
                iter = heap.erase(iter);
            } else {
                (*iter)->mark(false);
                iter++;
            }
        }
    }

    void collect() {
        markAll();
        sweep();
    }
};

int main() {
    //cout<<"hello";

    return 0;
}