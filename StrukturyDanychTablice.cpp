#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "dynamiczna.h"
#include "wiazana.h"
#include "dwokierunkowa.h"

using namespace std;
using namespace std::chrono;

const int TESTS = 40;
const int OPS = 80;

void fill(Dynamiczna& td, Wiazana& l1, Dwokierunkowa& l2, int n) {
    for (int i = 0; i < n; i++) {
        int val = rand() % 10000;
        td.add_back(val);
        l1.add_back(val);
        l2.add_back(val);
    }
}

int main() {
    srand(time(NULL));

    ofstream file("wyniki.csv");
    file << "N;TD_af;L1_af;L2_af;TD_ab;L1_ab;L2_ab;TD_find;L1_find;L2_find\n";

    int sizes[] = { 1000, 2000, 5000, 10000, 20000 };

    for (int s = 0; s < 5; s++) {
        int N = sizes[s];

        cout << "TEST DLA N = " << N << "\n";

        long long td_af = 0, l1_af = 0, l2_af = 0;
        long long td_ab = 0, l1_ab = 0, l2_ab = 0;
        long long td_fi = 0, l1_fi = 0, l2_fi = 0;

        
        Dynamiczna base_td;
        Wiazana base_l1;
        Dwokierunkowa base_l2;

        cout << "Tworzenie bazy danych...\n";
        fill(base_td, base_l1, base_l2, N);

        for (int t = 0; t < TESTS; t++) {

            int val = rand() % 10000;

            
            cout << "add_front test...\n";

            for (int i = 0; i < OPS; i++) {
                Dynamiczna td = base_td;

                auto start = high_resolution_clock::now();
                td.add_front(val);
                auto end = high_resolution_clock::now();

                td_af += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Wiazana l1 = base_l1;

                auto start = high_resolution_clock::now();
                l1.add_front(val);
                auto end = high_resolution_clock::now();

                l1_af += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Dwokierunkowa l2 = base_l2;

                auto start = high_resolution_clock::now();
                l2.add_front(val);
                auto end = high_resolution_clock::now();

                l2_af += duration_cast<nanoseconds>(end - start).count();
            }

            
            cout << "add_back test...\n";

            for (int i = 0; i < OPS; i++) {
                Dynamiczna td = base_td;

                auto start = high_resolution_clock::now();
                td.add_back(val);
                auto end = high_resolution_clock::now();

                td_ab += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Wiazana l1 = base_l1;

                auto start = high_resolution_clock::now();
                l1.add_back(val);
                auto end = high_resolution_clock::now();

                l1_ab += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Dwokierunkowa l2 = base_l2;

                auto start = high_resolution_clock::now();
                l2.add_back(val);
                auto end = high_resolution_clock::now();

                l2_ab += duration_cast<nanoseconds>(end - start).count();
            }

            
            cout << "find test...\n";

            for (int i = 0; i < OPS; i++) {
                Dynamiczna td = base_td;

                auto start = high_resolution_clock::now();
                td.find(val);
                auto end = high_resolution_clock::now();

                td_fi += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Wiazana l1 = base_l1;

                auto start = high_resolution_clock::now();
                l1.find(val);
                auto end = high_resolution_clock::now();

                l1_fi += duration_cast<nanoseconds>(end - start).count();
            }

            for (int i = 0; i < OPS; i++) {
                Dwokierunkowa l2 = base_l2;

                auto start = high_resolution_clock::now();
                l2.find(val);
                auto end = high_resolution_clock::now();

                l2_fi += duration_cast<nanoseconds>(end - start).count();
            }
        }

        
        td_af /= (TESTS * OPS);
        l1_af /= (TESTS * OPS);
        l2_af /= (TESTS * OPS);

        td_ab /= (TESTS * OPS);
        l1_ab /= (TESTS * OPS);
        l2_ab /= (TESTS * OPS);

        td_fi /= (TESTS * OPS);
        l1_fi /= (TESTS * OPS);
        l2_fi /= (TESTS * OPS);

        file << N << ";"
            << td_af << ";" << l1_af << ";" << l2_af << ";"
            << td_ab << ";" << l1_ab << ";" << l2_ab << ";"
            << td_fi << ";" << l1_fi << ";" << l2_fi << endl;

        cout << "\nWYNIKI:\n";
        cout << "add_front -> TD: " << td_af << " | L1: " << l1_af << " | L2: " << l2_af << "\n";
        cout << "add_back  -> TD: " << td_ab << " | L1: " << l1_ab << " | L2: " << l2_ab << "\n";
        cout << "find      -> TD: " << td_fi << " | L1: " << l1_fi << " | L2: " << l2_fi << "\n";
    }

    file.close();
    return 0;
}
