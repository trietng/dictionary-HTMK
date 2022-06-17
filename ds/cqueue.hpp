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
		if (head) {
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