#pragma once
#include <iostream>

template <typename T>
class shptr {
private:
	T* raw;
    unsigned int* counter;
    void clear() {
        if (!counter) return;
        --(*counter);
        if (*counter == 0) {
            delete raw;
            delete counter;
        }
    }
public:
    shptr() {
        raw = nullptr;
        counter = nullptr;
    }
    shptr(T* ptr) {
        raw = ptr;
        if (raw) counter = new unsigned int(1);
        else counter = nullptr;
    }
    shptr(const shptr<T>& shptr) {
        raw = shptr.raw;
        counter = shptr.counter;
        ++(*counter);
    }
    shptr<T>& operator=(const shptr<T>& shptr) {
        clear();
        raw = shptr.raw;
        counter = shptr.counter;
        ++(*counter);
        return *this;
    }
    shptr(shptr&& shptr) {
        raw = shptr.raw; 
        counter = shptr.counter;
        shptr.raw = shptr.counter = nullptr;
    }
    shptr<T>& operator=(shptr<T>&& shptr) {
        clear();
        raw = shptr.raw;
        counter = shptr.counter;
        shptr.raw = shptr.counter = nullptr;
    }
    ~shptr() {
        clear();
    }
    unsigned int use_count() const {
        return (counter) ? (*counter) : 0;
    }
    T* get() const {
        return raw;
    }
    T& operator*() const {
        return *raw;
    }
    T* operator->() const {
        return raw;
    }
};