#pragma once
template <typename T>
class DynamicArray {
    public:
        T* array;
        int size;
        int capacity;
        DynamicArray() {
            capacity = 4;
            array = new T[capacity];
            size = 0;
        }
        void add_back(T val) {
            if (size == capacity) {
                capacity *= 2;
                T* temp = new T[capacity];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array; 
                array = temp;
            }
        
            array[size] = val;
            size++;
        }

        void add_front(T val) {
            if (size == capacity) {
                capacity *= 2;
                T* temp = new T[capacity];
                
                temp[0] = val; 
                for (int i = 0; i < size; i++) {
                    temp[i + 1] = array[i]; 
                }
                
                delete[] array;
                array = temp;
            } 
            else {
                for (int i = size; i > 0; i--) {
                    array[i] = array[i - 1];
                }
                array[0] = val;
            }
            size++;
        }
        
        void add_at(T val, unsigned int index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            if (size == capacity) {
                capacity *= 2;
                T* temp = new T[capacity];
                
                for(int i = 0 ; i < index ; i++) temp[i] = array[i];

                temp[index] = val;
                for(int i = index; i < size ; i++) temp[i+1] = array[i];
                
                delete[] array;
                array = temp;
            }
            else {
                for(int i = size ; i > index ; i--) array[i] = array[i-1];
                array[index] = val;
            }
            size++;
        }

        void remove_back() {
            if (size == 0) return;
            size--; // jezeli nie zmieniamy capacity to tylko size-- nam starczy
            if (capacity > 4 && size <= capacity / 4) {
                capacity /= 2;
                T* temp = new T[capacity];
                
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                
                delete[] array;
                array = temp;
            }
        }

        void remove_front() {
            if (size == 0) return;
            size--;
            if (capacity > 4 && size <= capacity / 4) {
                capacity /= 2;
                T* temp = new T[capacity];
                
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i+1];
                }
                
                delete[] array;
                array = temp;
            }
            else {
                for(int i = 0 ; i < size ; i++) array[i] = array[i+1];
            }
        }

        void remove_at(unsigned int index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            size--;
            if (capacity > 4 && size <= capacity / 4) {
                capacity /= 2;
                T* temp = new T[capacity];
                
                for (int i = 0; i < index; i++) temp[i] = array[i];
                for(int i = index ; i < size ; i++) temp[i] = array[i+1];
                
                delete[] array;
                array = temp;
            }
            else {
                for(int i = index ; i < size ; i++) array[i] = array[i+1];
            }

        }

        T& operator[](unsigned int index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return array[index];
        }

        int find(T val) {
            for(int i = 0 ; i < size ; i++) {
                if(array[i] == val) return i;
            }
            return -1; // not found
        }

    ~DynamicArray() {
        delete[] array;
    }
};