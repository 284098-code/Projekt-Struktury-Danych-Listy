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
        << "TD_modify;L1_modify;L2_modify\n";

    int sizes[] = { 1000, 2000, 5000, 10000, 20000 };

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

        file << N << ";"
            << td_push << ";" << l1_push << ";" << l2_push << ";"
            << td_pop << ";" << l1_pop << ";" << l2_pop << ";"
            << td_mod << ";" << l1_mod << ";" << l2_mod
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
    }

    file.close();

    cout << "\nZapisano wyniki do pliku wyniki_kolejki.csv\n";

    return 0;
}
