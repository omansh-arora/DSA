
#include "Stack.h"

#include <stdexcept>

Stack::Stack(){

    size = 0;

}

void Stack::push(int x){

    if(size >= STACKCAP){ //1

        throw std::logic_error("Stack Overflow");

    }else if (isEmpty()){ //1

        arr[0] = x;
        size++;
        return;

    }else {

        for(int i = size-1; i >= 0;i--){

            arr[i+1] = arr[i];

        }
        arr[0] = x;
        size++;
        return;

    }

}

int Stack::pop(){

    if (isEmpty()) {

        throw std::logic_error("Stack is empty!");

    }else if(size == 1){
        
        size--;
        return arr[0];

    }else{

        int val = arr[0];

        for(int i = 0; i < size-1;i++){

            arr[i] = arr[i+1];

        }

        size--;
        return val;

    }

}

int Stack::peek() const{

    if(isEmpty()){

        throw std::logic_error("Stack empty!");

    }else{

        return arr[0];
    
    }

}

bool Stack::isEmpty() const{

    if(size <= 0) return true;
    return false;

}


