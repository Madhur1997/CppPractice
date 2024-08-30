#include<iostream>
#include<memory>

using namespace std;

template<typename T>
class UniquePtr {
    T* ptr;
    void reset() {
        if(!this->ptr) {
            delete this->ptr;
        }
        this->ptr = nullptr;
    }
public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T* obj) {
        this->ptr = obj;
    }

    UniquePtr(const UniquePtr&) = delete;
    void operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& cPtr) {
        this->reset();
        this->ptr = cPtr.ptr;
        cPtr.ptr = nullptr;
    }

    void operator=(UniquePtr&& cPtr) {
        this->reset();
        this->ptr = cPtr.ptr;
        cPtr.ptr = nullptr;
    }

    T& operator*() {
        return *(this->ptr);
    }

    T* operator->() {
        return this->ptr;
    }

    T* get() {
        return this->ptr;
    }

    ~UniquePtr() {
        this->reset();
    }
};

template<typename T>
class UniquePtr<T[]> {
    T* ptr;
    size_t size_;
public:
    UniquePtr(T* dPtr) {
        ptr = dPtr;
    }

    UniquePtr() : ptr(nullptr) {}

    UniquePtr(const UniquePtr& cPtr) = delete;
    void operator=(const UniquePtr& cPtr) = delete;

    UniquePtr(UniquePtr&& cPtr) {
        this->reset();
        this->ptr = cPtr.ptr;
        cPtr.ptr = nullptr;
    }

    void operator=(UniquePtr&& cPtr) {
        this->reset();
        this->ptr = cPtr.ptr;
        cPtr.ptr = nullptr;
    }

    T* get() {
        return this->ptr;
    }

    T& operator*() {
        if(this->ptr != nullptr) {
            return *(this->ptr);
        }
    }

    T* operator->() {
        return this->ptr;
    }

    T& operator[](int idx) {
        if(idx >= 0) {
            return this->ptr[idx];
        }

        throw std::runtime_error("Invalid idx: Out of bounds");
    } 

    ~UniquePtr() {
        this->reset();
    }

    void reset() {
        if(!this->ptr) {
            delete []this->ptr;
        }

        this->ptr = nullptr;
    }
};

template<typename T>
class SharedPtr {
    T* ptr_;
    int *mCounter;
public:
    SharedPtr() : ptr_(nullptr) {
        cout<<"Default constructor invoked"<<endl;
        mCounter = new int(0);
    }

    SharedPtr(T* ptr) : ptr_(ptr) {
        cout<<"Parameterized constructor invoked"<<endl;
        this->mCounter = new int(1);
    }

    SharedPtr(const SharedPtr& cPtr) {
        cout<<"Copy constructor invoked"<<endl;
        this->ptr_ = cPtr.ptr_;
        this->mCounter = cPtr.mCounter;
        (*this->mCounter)++;
    }

    SharedPtr(SharedPtr<T>&& cPtr) {
        cout << "Move constructor invoked" << endl;
        this->ptr_ = cPtr.ptr_;
        cPtr.ptr_ = nullptr;
        this->mCounter = cPtr.mCounter;
        cPtr.mCounter = nullptr;
    }

    void operator=(const SharedPtr& cPtr) {
        cout<<"Assignment operator invoked"<<endl;
        this->mCounter = cPtr.mCounter;
        (*this->mCounter)++;
        this->ptr_ = cPtr.ptr_;
    }

    void operator=(SharedPtr&& cPtr) {
        cout << "Move assignment operator invoked" << endl;
        this->reset();
        this->ptr_ = cPtr.ptr_;
        cPtr.ptr_ = nullptr;
        this->mCounter = cPtr.mCounter;
        cPtr.mCounter = nullptr;
    }

    void reset() {
        if(this->mCounter != nullptr) {
            (*this->mCounter)--;
            if((*this->mCounter) == 0) {
                delete this->ptr_;
                this->ptr_ = nullptr;
                delete this->mCounter;
                this->mCounter = nullptr;
            }
        }
    }

    T* operator->() {
        return this->ptr_;
    }

    T& operator*() {
        return (*this->ptr_);
    }

    T* lock() {
        return this->ptr_;
    }

    unsigned int use_count() {
        if(this->mCounter) {
            return (*this->mCounter);
        }
        return 0;
    }

    ~SharedPtr() {
        cout<<"Destructor invoked" << endl;
        this->reset();
    }
};

int main() {

    Unique pointer individual objects
    UniquePtr<int> ptr(new int(5));
    cout<<*ptr<<endl;
    *ptr=4;
    cout<<*ptr<<endl;
    UniquePtr<int> ptr2 = std::move(ptr);
    cout<<*ptr2<<endl;
    UniquePtr<int> ptr3;
    ptr3 = move(ptr2);
    cout<<ptr.get()<<endl;

    Unique pointer array
    UniquePtr<int[]> ptr4(new int[6]);
    ptr4[0] = 1;
    ptr4[1] = 2;
    cout<<ptr4[0] << " "<< ptr4[1] <<endl;
    UniquePtr<int[]> ptr5;
    ptr5.reset();


    // Shared pointer individual objects
    SharedPtr<int> sPtr(new int(5));
    cout << sPtr.use_count()<<endl;
    sPtr.reset();
    SharedPtr<int> sPtr2;
    SharedPtr<int> sPtr3 (new int(7));
    sPtr2 = sPtr3;
    sPtr = sPtr2;
    cout << sPtr2.use_count()<<endl;
    cout << sPtr3.use_count()<<endl;
    sPtr.reset();
    cout << sPtr3.use_count()<<endl;
    return 0;
}