#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Medium.h"
#include "Large.h"

template <typename T>
void badania_dodawania(int n, std::string outFile, int range);

template <typename T>
void badania_odejmowania(int n, std::string outFile, int range) ;

template <typename T>
void badania_wyszukiwania(int n, std::string outFile, int range) ;

int main() {
    std::string outFile = "data/S2_List_find_longlong.csv";
    int range = 1000000;
    for(int i =0  ;i < 10 ; i++) {
        badania_wyszukiwania<long long>(i,outFile,range);
    }
    return 0;
}

template <typename T>
T generate_data(std::mt19937& rng);

// char
template <>
char generate_data<char>(std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 254);
    char c = dist(rng);
    return c;
}

// long long
template <>
long long generate_data<long long>(std::mt19937& rng) {
    std::uniform_int_distribution<long long> dist(0, 1000000);
    return dist(rng);
}

// Medium
template <>
Medium generate_data<Medium>(std::mt19937& rng) {
    std::uniform_int_distribution<long long> dist(0, 1000000);
    return Medium(dist(rng), dist(rng), dist(rng));
}

template <typename T>
void badania_dodawania(int n, std::string outFile, int range) {

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    std::ofstream File(outFile, std::ios::app);

    LinkedList<T> l;

    for (int i = 0; i < range; i++) {

        T temp_data = generate_data<T>(rng);

        auto start = std::chrono::high_resolution_clock::now();

        l.add_at(temp_data,l.size/2);

        auto stop = std::chrono::high_resolution_clock::now();
        asm volatile("" ::: "memory"); 
        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        File << n << ";" << i << ";" << czas << "\n"; 
    }
}


template <typename T>
void badania_odejmowania(int n, std::string outFile, int range) {

    std::mt19937 rng(std::random_device{}());
    std::ofstream File(outFile, std::ios::app);

    DynamicArray<T> arr;

    for (int i = 0; i < range; i++) {
        T temp_data = generate_data<T>(rng);
        arr.add_back(temp_data);
    }

    for (int i = 0; i < range; i++) {


        auto start = std::chrono::high_resolution_clock::now();

        arr.remove_front();

        auto stop = std::chrono::high_resolution_clock::now();

        asm volatile("" ::: "memory");

        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        File << n << ";" << i << ";" << czas << "\n";
    }
}
template <typename T>
void badania_wyszukiwania(int n, std::string outFile, int range) {
    std::mt19937 rng(std::random_device{}());
    std::ofstream File(outFile, std::ios::app);

    LinkedList<T> l;

    l.add_back(-1);
    for(int i = 1 ; i < range ; i++) {
        T temp_data = generate_data<T>(rng);
        l.add_front(temp_data);
        auto start = std::chrono::high_resolution_clock::now();
        l.find(-1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        File << n << ";" << i << ";" << czas << "\n";
    }
}
