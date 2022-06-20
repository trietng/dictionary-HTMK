#pragma once
#include <iostream>

//WARNING: sh_ptr does not support move operation
template <typename T>
class sh_ptr {
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
    sh_ptr() {
        raw = nullptr;
        counter = nullptr;
    }
    sh_ptr(T* ptr) {
        raw = ptr;
        if (raw) counter = new unsigned int(1);
        else counter = nullptr;
    }
    sh_ptr(const sh_ptr<T>& sh_ptr) {
        raw = sh_ptr.raw;
        counter = sh_ptr.counter;
        ++(*counter);
    }
    sh_ptr<T>& operator=(const sh_ptr<T>& sh_ptr) {
        clear();
        raw = sh_ptr.raw;
        counter = sh_ptr.counter;
        ++(*counter);
        return *this;
    }
    ~sh_ptr() {
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