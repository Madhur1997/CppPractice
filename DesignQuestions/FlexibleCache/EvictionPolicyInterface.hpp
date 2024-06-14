using namespace std;

class EvictionPolicyInterface {
public:
    virtual int getEvictionKey() = 0;
    virtual void processkeyOnAdd(int key) = 0;
    virtual void processKeyOnUpdate(int key) = 0;
    virtual void processKeyOnDelete(int key) = 0;
};