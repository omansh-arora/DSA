
#include "Queue.h"
#include <iostream>


// Desc:  Constructor
Queue::Queue() : size(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0) {

    arr = new int[capacity];

} // constructor


// Desc:  Destructor
Queue::~Queue() {

    delete [] arr;
    arr = nullptr;

} // destructor


// Desc:  Copy Constructor
Queue::Queue(const Queue &other) {
    if (this != &other) {

        size = other.size;
        capacity = other.capacity;
        frontindex = other.frontindex;
        backindex = other.backindex;
        arr = new int[capacity];

        for (unsigned i = 0; i < capacity; i++) {
            arr[i] = other.arr[i];
        }
    }
} // copy constructor


// Desc:  Assignment operator
Queue & Queue::operator=(const Queue &rhs) {
    if (this != &rhs) {

        delete [] arr;
        size = rhs.size;
        capacity = rhs.capacity;
        frontindex = rhs.frontindex;
        backindex = rhs.backindex;
        arr = new int[capacity];

        for (unsigned i = 0; i < capacity; i++) {
            arr[i] = rhs.arr[i];
        }
    }
    return *this;
} // lhs = rhs


// Desc:  Inserts element x at the back (O(1))
void Queue::enqueue(int x) {

    if(size==capacity){

        int* carr = new int[capacity*2];

        if (frontindex > backindex){
            for(unsigned i = frontindex; i < capacity; i++){

                carr[i-frontindex] = arr[i];

            }
            for(unsigned i = 0; i <= backindex; i++){

                carr[i] = arr[i];

            }
        }else if (backindex > frontindex)
        {
            for(unsigned i = frontindex; i <= backindex; i++){

                carr[i-frontindex] = arr[i];

            }
        }else if (frontindex == backindex){

            for(unsigned i = frontindex; i < capacity; i++){

                carr[i-frontindex] = arr[i];

            }
            for(unsigned i = 0; i < backindex; i++){

                carr[i+(capacity-frontindex)] = arr[i];

            }

        }
        capacity = capacity*2;

        delete [] arr;
        arr = nullptr;
        arr = new int[capacity];

        for(unsigned i = 0; i < capacity; i++){
  
            arr[i] = carr[i];

        }
        delete [] carr;
        carr = nullptr;
        
        frontindex = 0;
        backindex = (frontindex + size)%capacity;
        arr[backindex] = x;
        backindex = (backindex + 1) % capacity;
        size++;

    }else{
        size++;
        arr[backindex] = x;
        backindex = (backindex + 1) % capacity;
    }
} // enqueue


// Desc:  Removes the frontmost element (O(1))
//  Pre:  Queue not empty
void Queue::dequeue() {

    if(Queue::isEmpty()) throw std::logic_error("Queue empty cannot dequeue");
    if(!isEmpty() && size != 1 && capacity/(size-1) > 3 && capacity/2 >= INITIAL_SIZE){
        size--;
        frontindex = (frontindex + 1) % capacity;
        int* carr = new int[capacity/2];

        if (frontindex > backindex){
            for(unsigned i = frontindex; i < capacity; i++){

                carr[i-frontindex] = arr[i];

            }
            for(unsigned i = 0; i <= backindex; i++){

                carr[i+size] = arr[i];

            }
        }else if (backindex > frontindex)
        {
            for(unsigned i = frontindex; i <= backindex; i++){

                carr[i-frontindex] = arr[i];

            }
        }else if (frontindex == backindex){

            for(unsigned i = frontindex; i < capacity; i++){

                carr[i-frontindex] = arr[i];

            }
            for(unsigned i = 0; i < backindex; i++){

                carr[i+(capacity-frontindex)] = arr[i];

            }

        }
        capacity = capacity/2;

        delete [] arr;
        arr = new int[capacity];

        for(unsigned i = 0; i < capacity; i++){
  
            arr[i] = carr[i];

        }
        delete [] carr;
        carr = nullptr;
        
        frontindex = 0;
        backindex = (frontindex + size)%capacity;
        


    }else{
        size--;
        frontindex = (frontindex + 1) % capacity;
    }
} // dequeue


// Desc:  Returns a copy of the frontmost element (O(1))
//  Pre:  Queue not empty
int Queue::peek() const {
    if(Queue::isEmpty()) throw std::logic_error("Queue empty cannot dequeue");
    return arr[frontindex];
} // top


// Desc:  Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const {
    return size == 0;
} // isempty

void Queue::print(){

    //std::cout << arr[9];
    for(unsigned i = 0; i < capacity; i++){

        std::cout << arr[i] << std::endl;

    }

    std::cout << "fi: " << frontindex << std::endl << "bi: "<< backindex << std::endl << "size1: "<< size << std::endl << "cap: "<< capacity << std::endl;

}




