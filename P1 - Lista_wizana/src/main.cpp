#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include "LinkedList.h"
#include "DynamicArray.h"

template <typename T>
void badania_dodawania(int n, std::string outFile, int range);
void loadingScreen(int i, int n);
int main() {
    std::string outFile = "data/LinkedList_small_addFront_50_10000.csv";
    int range = 1000000;
   // for(int i =0  ;i < 10 ; i++) {
        badania_dodawania<char>(0,outFile,range);
   // }
    return 0;
}
template <typename T>
void badania_dodawania(int n, std::string outFile, int range) {

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    std::ofstream File(outFile, std::ios::app);
    LinkedList<T> lista;
    for(int i = 0 ; i < range/5 ; i++) {
        volatile T temp_data = static_cast<T>(dist(rng));
        auto start = std::chrono::high_resolution_clock::now();
            lista.add_front(temp_data);
        auto stop = std::chrono::high_resolution_clock::now();
        asm volatile("" ::: "memory"); 
        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        File << n << ";" << i << ";" << czas << "\n"; 
    }
}

