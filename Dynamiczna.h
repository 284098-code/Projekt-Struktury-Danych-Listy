#ifndef DYNAMICZNA_H
#define DYNAMICZNA_H

class Dynamiczna {
private:
    int* arr;
    int size;
    int capacity;

public:
    Dynamiczna() {
        size = 0;
        capacity = 10;
        arr = new int[capacity];
    }

    Dynamiczna(const Dynamiczna& other) {
        size = other.size;
        capacity = other.capacity;
        arr = new int[capacity];

        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    ~Dynamiczna() {
        delete[] arr;
    }

    int& operator[](int index) {
        return arr[index];
    }

    void enlarge() {
        capacity *= 2;
        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }

    int getsize() {
        return size;
    }

    int getcapacity() {
        return capacity;
    }

    void add_back(int i) {
        if (size == capacity) {
            enlarge();
        }
        arr[size++] = i;
    }

    void add_front(int i) {
        if (size == capacity) {
            enlarge();
        }

        for (int j = size; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
        arr[0] = i;
        size++;
    }
    
    void add_index(int i, int index) {
        if (index < 0 || index > size) {
            return;
        }

        if (size == capacity) {
            enlarge();
        }

        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = i;
        size++;
    }
    
    void delete_front() {
        if (size == 0) {
            return;
        }

        for (int i = 0; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    void delete_back() {
        if (size == 0) {
            return;
        }
        size--;
    }

    void delete_index(int index) {
        if (index < 0 or index >= size) {
            return;
        }

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
    int find(int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1; 
    }
    void print(){
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
    }
};


#endif // !DYNAMICZNA_H
