#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> l;
    LinkedList<int> l2;
    for(int i = 0 ; i < 100 ; i++) {
        l.add_back(i);
    }
    for(int i = 0 ; i < 100 ; i++) {
        l2.add_front(i);
    }
    for(int i = 0 ; i < 100 ; i++) {
        std::cout<<l[i]<<"|";
    }
    std::cout<<"\n";
    for(int i = 0 ; i < 100 ; i++) {
        std::cout<<l2[i]<<"|";
    }
    std::cout<<"\n";
    return 0;
}