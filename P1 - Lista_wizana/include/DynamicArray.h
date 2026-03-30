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


};