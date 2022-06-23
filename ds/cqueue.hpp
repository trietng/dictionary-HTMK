#pragma once
#include <vector>
#include "fnode.hpp"

template <typename T>
class cqueue {
private:
	fnode<T>* head;
	fnode<T>* tail;
	unsigned int counter;
public:
	cqueue() {
		head = nullptr;
		tail = nullptr;
		counter = 0;
	}
	~cqueue() {
		while (head) {
			fnode<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
		counter = 0;
	}
    class iterator {
    private:
        friend cqueue;
        fnode<T>* ptr;
        void erase_next() {
            if (ptr->pnext) {
                fnode<T>* pdel = ptr->pnext;
                ptr->pnext = ptr->pnext->pnext;
                delete pdel;
                pdel = nullptr;
            }
        }
        void remove() {
            if (!ptr) return;
            fnode<T>* tmp = ptr->pnext;
            if (tmp) {
                *ptr = *tmp;
                tmp->pnext = nullptr;
                delete tmp;
            }
            tmp = nullptr;
        }
    public:
        iterator() {
            ptr = nullptr;
        }
        iterator(fnode<T>* ptr) {
            ptr = ptr;
        }
        iterator& operator=(fnode<T>* ptr) {
            this->ptr = ptr;
            return *this;
        }
        bool operator==(const iterator& it) const {
            return (this->ptr == it.ptr);
        }
        bool operator!=(const iterator& it) const {
            return (ptr != it.ptr);
        }
        iterator& operator++() {
            if (ptr) {
                ptr = ptr->pnext;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            operator++();
            return tmp;
        }
        iterator next() {
            iterator tmp(*this);
            ++tmp;
            return tmp;
        }
        T& operator*() {
            return ptr->data;
        }
    };
    class const_iterator {
    private:
        fnode<T>* ptr;
    public:
        const_iterator() {
            ptr = nullptr;
        }
        const_iterator(fnode<T>* ptr) {
            ptr = ptr;
        }
        const_iterator& operator=(fnode<T>* ptr) {
            this->ptr = ptr;
            return *this;
        }
        bool operator==(const const_iterator& it) const {
            return (this->ptr == it.ptr);
        }
        bool operator!=(const const_iterator& it) const {
            return (ptr != it.ptr);
        }
        const_iterator& operator++() {
            if (ptr) {
                ptr = ptr->next;
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            operator++();
            return tmp;
        }
        const_iterator next() {
            const_iterator tmp(*this);
            ++tmp;
            return tmp;
        }
        T& operator*() const {
            return ptr->data;
        }
    };
    //Return iterator to the front node.
    iterator begin() {
        return iterator(head);
    }
    //Return iterator to the back node.
    iterator end() {
        return iterator(tail);
    }
    //Return constant iterator to the front node.
    const_iterator cbegin() const {
        return const_iterator(head);
    }
    //Return constant iterator to the back node.
    const_iterator cend() const {
        return const_iterator(tail);
    }
	//Check if the queue is empty.
	bool empty() {
		if (counter == 0) return true;
		return false;
	}
	//Return the number of node, time complexity O(1).
	unsigned int size() {
		return counter;
	}
	//Insert a new node at the back.
	void push_back(T data) {
		if (!head) {
			head = new fnode<T>;
			tail = head;
		}
		else {
			tail->next = new fnode<T>;
			tail = tail->next;
		}
		tail->data = data;
		tail->next = nullptr;
		++counter;
	}
	//Delete the front node.
	void pop_front() {
		if (!empty()) {
			fnode<T>* tmp = head;
			head = head->next;
			delete tmp;
			--counter;
		}
	}
	//Return the front node's value.
	T& front() {
		return head->data;
	}
	//Return the last node's value.
	T& back() {
		return tail->data;
	}
    //Remove the a node from the list
    void remove(iterator& current) {
        if (current == end()) {
            iterator i = begin();
            if (i.next() != nullptr) {
                while (i.next() != end()) {
                    ++i;
                }
            }
            tail = i.ptr;
            if (counter == 1) {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else {
                delete tail->next;
                tail->next = nullptr;
            }
        }
        else {
            if (current.next() == end()) {
                tail = current.ptr;
            }
            current.remove();
        }
        --counter;
    }
    //Remove the next node from the list
    void erase_after(iterator& current) {
        if (current.next() == end()) {
            tail = current.ptr;
        }
        current.erase_next();
        --counter;
    }
	//Return the entire queue as a vector, time complexity O(n).
	std::vector<T> vector() {
		std::vector<T> tmp;
		if (empty()) return tmp;
		tmp.resize(counter);
		fnode<T>* ptr = head;
		while (ptr) {
			tmp.push_back(ptr->data);
			ptr = ptr->next;
		}
		return tmp;
	}
	//Return the entire queue as a C-array, time complexity O(n).
	T* c_array() {
		if (empty()) return nullptr;
		T* tmp = new T[counter];
		int i = 0;
		fnode<T>* ptr = head;
		while (ptr) {
			tmp[i] = ptr->data;
			ptr = ptr->next;
            ++i;
		}
		return tmp;
	}
	//Swap the contents of this queue with another
	void swap(cqueue<T>& source) {
		fnode<T>* tmp_head = head;
		fnode<T>* tmp_tail = tail;
		int tmp_counter = counter;
		head = source.head;
		tail = source.tail;
		counter = source.counter;
		source.head = tmp_head;
		source.tail = tmp_tail;
		source.counter = tmp_counter;
	}
};