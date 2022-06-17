#pragma once
#include <cmath>
#include "fnode.hpp"

template <typename T>
class flist {
private:
    fnode<T>* head;
public:
    flist() {
        head = nullptr;
    }
    ~flist() {
        while (head) {
            fnode<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    fnode<T>* front() {
        return head;
    }
    void push_front(const T& data) {
        fnode<T>* tmp = new fnode<T>;
        tmp->data = data;
        tmp->next = head;
        head = tmp;
    }
    void pop_front() {
        fnode<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
    bool empty() {
        if (!head) return true;
        return false;
    }
    void remove(const T& data) {
        fnode<T>* cur = head;
        if (!cur) return;
        if (cur->data == data) {
            head = head->next;
            delete cur;
            return;
        }
        while (cur->next) {
            if (cur->next->data == data) {
                fnode<T>* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
                return;
            }
            else cur = cur->next;
        }
    }
    void clear() {
        fnode<T>* cur = head;
        while (cur) {
            fnode<T>* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        head = nullptr;
    }
    void swap(flist<T>& target) {
        fnode<T>* tmp = target.head;
        target.head = head;
        head = tmp;
    }
    //Remove duplicates, time complexity O(n^2).
    void unique() { 
        if (!head) return;
        fnode<T>* cur = head;
        fnode<T>* rest = nullptr;
        fnode<T>* dup = nullptr;
        while (cur && cur->next) {
            rest = cur;
            while (rest->next) {
                if (cur->data == rest->next->data) {
                    dup = rest->next;
                    rest->next = rest->next->next;
                    delete cur->next;
                }
                else rest = rest->next;
            }
            cur = cur->next;
        }
    }
    void join(flist& target) {
        //join another flist to the current one
        //the target flist will be empty afterward
        //time complexity O(n)
        fnode<T>* cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = target.head;
        target.head = nullptr;
    }
    fnode<T>* find(const T& data) {
        fnode<T>* cur = head;
        while (!cur) {
            if (cur->data == data) {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }
    void erase_after(fnode<T>* node) {
        if (!node) return;
        fnode<T>* tmp = node->next;
        if (!tmp) return;
        node->next = tmp->next;
        delete tmp;
    }
    void insert_after(fnode<T>* node, const T& data) {
        if (!node) return;
        fnode<T>* tmp = node->next;
        node->next = new fnode<T>*;
        node->next->data = data;
        node->next->next = tmp;
    }
};