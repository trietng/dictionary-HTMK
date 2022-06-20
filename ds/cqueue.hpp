#pragma once
#include <vector>
#include "fnode.hpp"

template <typename T>
class cqueue {
private:
	fnode<T>* head;
	fnode<T>* tail;
	int counter;
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
        fnode<T>* cur;
        void erase_next() {
            if (cur->pnext) {
                fnode<T>* pdel = cur->pnext;
                cur->pnext = cur->pnext->pnext;
                delete pdel;
                pdel = nullptr;
            }
        }
        void erase_cur() {
            if (!cur) {
                return;
            }
            fnode<T>* tmp;
            tmp = cur->pnext;
            if (tmp) {
                *cur = *tmp;
                tmp->pnext = nullptr;
                delete tmp;
            }
            tmp = nullptr;
        }
    public:
        iterator() {
            cur = nullptr;
        }
        iterator(fnode<T>* ptr) {
            cur = ptr;
        }
        iterator& operator=(fnode<T>* ptr) {
            this->cur = ptr;
            return *this;
        }
        bool operator==(const iterator& it) const {
            return (this->cur == it.cur);
        }
        bool operator!=(const iterator& it) const {
            return (cur != it.cur);
        }
        iterator& operator++() {
            if (cur) {
                cur = cur->pnext;
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
            return cur->data;
        }
    };
    class const_iterator {
    private:
        fnode<T>* cur;
    public:
        const_iterator() {
            cur = nullptr;
        }
        const_iterator(fnode<T>* ptr) {
            cur = ptr;
        }
        const_iterator& operator=(fnode<T>* ptr) {
            this->cur = ptr;
            return *this;
        }
        bool operator==(const const_iterator& it) const {
            return (this->cur == it.cur);
        }
        bool operator!=(const const_iterator& it) const {
            return (cur != it.cur);
        }
        const_iterator& operator++() {
            if (cur) {
                cur = cur->next;
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
            return cur->data;
        }
    };
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(tail);
    }
    const_iterator cbegin() const {
        return const_iterator(head);
    }
    const_iterator cend() const {
        return const_iterator(tail);
    }
	//Check if the queue is empty.
	bool empty() {
		if (counter == 0) return true;
		return false;
	}
	//Return the number of node, time complexity O(1).
	int size() {
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
	T front() {
		return head->data;
	}
	//Return the last node's value.
	T back() {
		return tail->data;
	}
	//Return the entire queue as a vector, time complexity O(n).
	std::vector<T> vector() {
		std::vector<T> tmp;
		if (empty()) return tmp;
		tmp.resize(counter);
		fnode<T>* cur = head;
		while (cur) {
			tmp.push_back(cur->data);
			cur = cur->next;
		}
		return tmp;
	}
	//Return the entire queue as a C-array, time complexity O(n).
	T* c_array() {
		if (empty()) return nullptr;
		T* tmp = new T[counter];
		int i = 0;
		fnode<T>* cur = head;
		while (cur) {
			tmp[i] = cur->data;
			cur = cur->next;
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