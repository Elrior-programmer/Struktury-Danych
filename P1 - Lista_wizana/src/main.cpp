#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> l;
    LinkedList<int> l2;
    for(int i = 0 ; i < 100 ; i++) {
        l.add_back(i);
    }
    l.remove_at(6);
    for(int i = 0 ; i < l.size ; i++) {
        std::cout<<l[i]<<"|";
    }
    std::cout<<"\n";
    return 0;
}