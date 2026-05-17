#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Dynamiczna.h"
#include "Wiazana.h"
#include "Dwokierunkowa.h"

using namespace std;
using namespace std::chrono;

const int TESTS = 40;
const int OPS = 80;


class PriorityDynamiczna {
private:
    Dynamiczna dane;

public:

    void push(int value) {

        int index = 0;

        while (
            index < dane.getsize() &&
            dane[index] > value
            ) {
            index++;
        }

        dane.add_index(value, index);
    }

    void pop() {
        dane.delete_front();
    }

    int peek() {

        if (dane.getsize() == 0)
            return -1;

        return dane[0];
    }

    int size() {
        return dane.getsize();
    }

    void modifyPriority(int oldValue, int newValue) {

        int index = dane.find(oldValue);

        if (index != -1) {

            dane.delete_index(index);
            push(newValue);
        }
    }
};


class PriorityWiazana {
private:
    Wiazana dane;

public:

    void push(int value) {

        int index = 0;

        while (
            index < dane.getsize() &&
            dane.get(index) > value
            ) {
            index++;
        }

        dane.add_index(value, index);
    }

    void pop() {
        dane.delete_front();
    }

    int peek() {

        if (dane.getsize() == 0)
            return -1;

        return dane.get(0);
    }

    int size() {
        return dane.getsize();
    }

    void modifyPriority(int oldValue, int newValue) {

        int index = dane.find(oldValue);

        if (index != -1) {

            dane.delete_index(index);
            push(newValue);
        }
    }
};


class PriorityDwokierunkowa {
private:
    Dwokierunkowa dane;

public:

    void push(int value) {

        int index = 0;

        while (
            index < dane.getsize() &&
            dane.get(index) > value
            ) {
            index++;
        }

        dane.add_index(value, index);
    }

    void pop() {
        dane.delete_front();
    }

    int peek() {

        if (dane.getsize() == 0)
            return -1;

        return dane.get(0);
    }

    int size() {
        return dane.getsize();
    }

    void modifyPriority(int oldValue, int newValue) {

        int index = dane.find(oldValue);

        if (index != -1) {

            dane.delete_index(index);
            push(newValue);
        }
    }
};

void fill(
    PriorityDynamiczna& td,
    PriorityWiazana& l1,
    PriorityDwokierunkowa& l2,
    int n
) {

    for (int i = 0; i < n; i++) {

        int val = rand() % 10000;

        td.push(val);
        l1.push(val);
        l2.push(val);
    }
}

int main() {

    srand(time(NULL));

    ofstream file("wyniki_kolejki.csv");

    file << "N;"
        << "TD_push;L1_push;L2_push;"
        << "TD_pop;L1_pop;L2_pop;"
        << "TD_modify;L1_modify;L2_modify;"
        << "TD_peek;L1_peek;L2_peek;"
        << "TD_size;L1_size;L2_size\n";

    int sizes[] = { 1000, 2000, 5000, 10000 };

    for (int s = 0; s < 5; s++) {

        int N = sizes[s];

        cout << "\n====================================\n";
        cout << "TEST DLA N = " << N << endl;
        cout << "====================================\n";

        long long td_push = 0;
        long long l1_push = 0;
        long long l2_push = 0;

        long long td_pop = 0;
        long long l1_pop = 0;
        long long l2_pop = 0;

        long long td_mod = 0;
        long long l1_mod = 0;
        long long l2_mod = 0;

        long long td_peek = 0;
        long long l1_peek = 0;
        long long l2_peek = 0;

        long long td_size = 0;
        long long l1_size = 0;
        long long l2_size = 0;

        PriorityDynamiczna base_td;
        PriorityWiazana base_l1;
        PriorityDwokierunkowa base_l2;

        cout << "Tworzenie struktur..." << endl;

        fill(base_td, base_l1, base_l2, N);


        for (int t = 0; t < TESTS; t++) {

            int val = rand() % 10000;


            cout << "push test..." << endl;

            for (int i = 0; i < OPS; i++) {

                PriorityDynamiczna q = base_td;

                auto start = high_resolution_clock::now();

                q.push(val);

                auto end = high_resolution_clock::now();

                td_push += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityWiazana q = base_l1;

                auto start = high_resolution_clock::now();

                q.push(val);

                auto end = high_resolution_clock::now();

                l1_push += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityDwokierunkowa q = base_l2;

                auto start = high_resolution_clock::now();

                q.push(val);

                auto end = high_resolution_clock::now();

                l2_push += duration_cast<nanoseconds>(end - start).count();
            }


            cout << "pop test..." << endl;

            for (int i = 0; i < OPS; i++) {

                PriorityDynamiczna q = base_td;

                auto start = high_resolution_clock::now();

                q.pop();

                auto end = high_resolution_clock::now();

                td_pop += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityWiazana q = base_l1;

                auto start = high_resolution_clock::now();

                q.pop();

                auto end = high_resolution_clock::now();

                l1_pop += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityDwokierunkowa q = base_l2;

                auto start = high_resolution_clock::now();

                q.pop();

                auto end = high_resolution_clock::now();

                l2_pop += duration_cast<nanoseconds>(end - start).count();
            }


            cout << "modify test..." << endl;

            for (int i = 0; i < OPS; i++) {

                PriorityDynamiczna q = base_td;

                auto start = high_resolution_clock::now();

                q.modifyPriority(q.peek(), rand() % 10000);

                auto end = high_resolution_clock::now();

                td_mod += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityWiazana q = base_l1;

                auto start = high_resolution_clock::now();

                q.modifyPriority(q.peek(), rand() % 10000);

                auto end = high_resolution_clock::now();

                l1_mod += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityDwokierunkowa q = base_l2;

                auto start = high_resolution_clock::now();

                q.modifyPriority(q.peek(), rand() % 10000);

                auto end = high_resolution_clock::now();

                l2_mod += duration_cast<nanoseconds>(end - start).count();
            }


            cout << "peek test..." << endl;

            for (int i = 0; i < OPS; i++) {

                PriorityDynamiczna q = base_td;

                auto start = high_resolution_clock::now();

                q.peek();

                auto end = high_resolution_clock::now();

                td_peek += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityWiazana q = base_l1;

                auto start = high_resolution_clock::now();

                q.peek();

                auto end = high_resolution_clock::now();

                l1_peek += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityDwokierunkowa q = base_l2;

                auto start = high_resolution_clock::now();

                q.peek();

                auto end = high_resolution_clock::now();

                l2_peek += duration_cast<nanoseconds>(end - start).count();
            }


            cout << "size test..." << endl;

            for (int i = 0; i < OPS; i++) {

                PriorityDynamiczna q = base_td;

                auto start = high_resolution_clock::now();

                q.size();

                auto end = high_resolution_clock::now();

                td_size += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityWiazana q = base_l1;

                auto start = high_resolution_clock::now();

                q.size();

                auto end = high_resolution_clock::now();

                l1_size += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {

                PriorityDwokierunkowa q = base_l2;

                auto start = high_resolution_clock::now();

                q.size();

                auto end = high_resolution_clock::now();

                l2_size += duration_cast<nanoseconds>(end - start).count();
            }
        }


        td_push /= (TESTS * OPS);
        l1_push /= (TESTS * OPS);
        l2_push /= (TESTS * OPS);

        td_pop /= (TESTS * OPS);
        l1_pop /= (TESTS * OPS);
        l2_pop /= (TESTS * OPS);

        td_mod /= (TESTS * OPS);
        l1_mod /= (TESTS * OPS);
        l2_mod /= (TESTS * OPS);

        td_peek /= (TESTS * OPS);
        l1_peek /= (TESTS * OPS);
        l2_peek /= (TESTS * OPS);

        td_size /= (TESTS * OPS);
        l1_size /= (TESTS * OPS);
        l2_size /= (TESTS * OPS);


        file << N << ";"
            << td_push << ";" << l1_push << ";" << l2_push << ";"
            << td_pop << ";" << l1_pop << ";" << l2_pop << ";"
            << td_mod << ";" << l1_mod << ";" << l2_mod << ";"
            << td_peek << ";" << l1_peek << ";" << l2_peek << ";"
            << td_size << ";" << l1_size << ";" << l2_size
            << endl;


        cout << "\nWYNIKI:\n" << endl;

        cout << "push   -> "
            << "TD: " << td_push
            << " | L1: " << l1_push
            << " | L2: " << l2_push
            << endl;

        cout << "pop    -> "
            << "TD: " << td_pop
            << " | L1: " << l1_pop
            << " | L2: " << l2_pop
            << endl;

        cout << "modify -> "
            << "TD: " << td_mod
            << " | L1: " << l1_mod
            << " | L2: " << l2_mod
            << endl;

        cout << "peek   -> "
            << "TD: " << td_peek
            << " | L1: " << l1_peek
            << " | L2: " << l2_peek
            << endl;

        cout << "size   -> "
            << "TD: " << td_size
            << " | L1: " << l1_size
            << " | L2: " << l2_size
            << endl;
    }

    file.close();

    cout << "\nZapisano wyniki do pliku wyniki_kolejki.csv\n";

    return 0;
}
