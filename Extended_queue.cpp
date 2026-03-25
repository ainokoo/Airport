
#include "Extended_queue.h"
#include "Plane.h"
#include "utility.h"
#include <iostream>

using namespace std;

Queue::Queue() {
   count = 0;
   rear = maxqueue - 1;
   front = 0;
}

bool Queue::empty() const {
   return count == 0;
}

Error_code Queue::append(const Queue_entry &item) {
   if (count >= maxqueue) return overflow;
   count++;
   rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
   entry[rear] = item;
   return success;
}

Error_code Queue::retrieve(Queue_entry &item) const {
   if (count <= 0) return underflow;
   item = entry[front];
   return success;
}

Error_code Queue::serve() {
    if (count <= 0) return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

int Extended_queue::size() const {
   return Queue::count;
}

bool Extended_queue::full() const {
	return maxqueue == this -> count;
}

void Extended_queue::clear() {
	this -> count = 0;
	this -> front = 0;
	this -> rear = maxqueue - 1;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
   if (count <= 0) return underflow;
   item = entry[front];
   count--;
   front = ((front + 1) == maxqueue) ? 0 : (front + 1);
   return success;
}

