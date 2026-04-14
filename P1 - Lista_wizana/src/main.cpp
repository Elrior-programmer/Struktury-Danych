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

int main() {
    std::string outFile = "data/S2_List_remove_back_Large.csv";
    int range = 1000000;
    for(int i =0  ;i < 10 ; i++) {
        badania_odejmowania<Large>(i,outFile,range);
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

// Large (zakładamy long long[32])
template <>
Large generate_data<Large>(std::mt19937& rng) {
    std::uniform_int_distribution<long long> dist(0, 1000000);
    Large obj;
    for (int i = 0; i < 32; i++) {
        obj.data[i] = dist(rng);
    }
    return obj;
}

template <typename T>
void badania_dodawania(int n, std::string outFile, int range) {

    std::mt19937 rng(std::random_device{}());
    std::ofstream File(outFile, std::ios::app);

    LinkedList<T> lista;

    for (int i = 0; i < range; i++) {

        T temp_data = generate_data<T>(rng);

        auto start = std::chrono::high_resolution_clock::now();

        lista.add_at(temp_data,lista.size/2);

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

    LinkedList<T> lista;

    for (int i = 0; i < range; i++) {
        T temp_data = generate_data<T>(rng);
        lista.add_front(temp_data);
    }

    for (int i = 0; i < range; i++) {


        auto start = std::chrono::high_resolution_clock::now();

        lista.remove_back();

        auto stop = std::chrono::high_resolution_clock::now();

        asm volatile("" ::: "memory");

        auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        File << n << ";" << i << ";" << czas << "\n";
    }
}