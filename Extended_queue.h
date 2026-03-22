#pragma once
#include "utility.h"
#include "Plane.h"

typedef Plane Queue_entry;

const int maxqueue = 6; 

class Queue {
public:
   Queue();
   bool empty() const;
   Error_code serve();
   Error_code append(const Queue_entry &item);
   Error_code retrieve(Queue_entry &item) const;

protected:
   int count;
   int front, rear;
   Queue_entry entry[maxqueue];
};


class Extended_queue: public Queue {
public:
	bool full() const;
	int size() const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);

	void print();
};