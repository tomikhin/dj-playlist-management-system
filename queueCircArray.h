#include <stdio.h>
#include <iostream>
#define NMAX 50


template<typename T> class QueueCirc {
    private:
        T queueArray[NMAX];
        int head, tail, size;
    public:
        void enqueue(T x) { //adds an element to the tail of the queue
            if (size == NMAX) {
                std::cout<<"Error 101 - The queue is full!\n";
                return;
            }
            queueArray[tail] = x;
            tail = (tail + 1) % NMAX;
            size++;
        }

        int getSize () {
        	return size; 
        }
        	
        T dequeue() { //removes the head of the queue and returns it
            if (isEmpty()) {
                std::cout<<"Error 102 - The queue is empty!\n";
                T x;
                return x;
            }
            T x = queueArray[head];
            head = (head + 1) % NMAX;
            size--;
            return x;
        }
        T peek() { //returns the head of the queue
            if (isEmpty()) 
            {
                std::cout<<stderr, "Error 103 - The queue is empty!\n";
                T x;
                return x;
            }
            return queueArray[head];
        }

        T peekLast() //returns the tail of the queue 
        {
            if (isEmpty())
            {
                std::cout << stderr, "Error 104 - The queue is empty!\n";
                T x;
                return x;
            }
            return queueArray[tail - 1];
        }

        int isEmpty() {
            return (size == 0);
        }

        int getHead() { //returns the index of the head of the queue
            return head;
        }

        int getTail() { //returns the index of the tail of the queue
            return tail; 
        }

        QueueCirc() {
            head = tail = size = 0;
        }
};

