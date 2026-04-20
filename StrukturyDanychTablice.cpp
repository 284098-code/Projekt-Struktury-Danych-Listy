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

const int TESTS = 50;
const int OPS = 100;

// wypełnianie
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

    int sizes[] = { 1000, 5000, 10000, 20000, 50000 };

    for (int s = 0; s < 5; s++) {
        int N = sizes[s];

        long long td_af = 0, l1_af = 0, l2_af = 0;
        long long td_ab = 0, l1_ab = 0, l2_ab = 0;
        long long td_fi = 0, l1_fi = 0, l2_fi = 0;

        for (int t = 0; t < TESTS; t++) {

            Dynamiczna td;
            Wiazana l1;
            Dwokierunkowa l2;

            fill(td, l1, l2, N);

            int val = rand() % 10000;

            // ================= add_front =================
            auto start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) td.add_front(val);
            auto end = high_resolution_clock::now();
            td_af += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l1.add_front(val);
            end = high_resolution_clock::now();
            l1_af += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l2.add_front(val);
            end = high_resolution_clock::now();
            l2_af += duration_cast<nanoseconds>(end - start).count() / OPS;

            // ================= add_back =================
            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) td.add_back(val);
            end = high_resolution_clock::now();
            td_ab += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l1.add_back(val);
            end = high_resolution_clock::now();
            l1_ab += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l2.add_back(val);
            end = high_resolution_clock::now();
            l2_ab += duration_cast<nanoseconds>(end - start).count() / OPS;

            // ================= find =================
            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) td.find(val);
            end = high_resolution_clock::now();
            td_fi += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l1.find(val);
            end = high_resolution_clock::now();
            l1_fi += duration_cast<nanoseconds>(end - start).count() / OPS;

            start = high_resolution_clock::now();
            for (int i = 0; i < OPS; i++) l2.find(val);
            end = high_resolution_clock::now();
            l2_fi += duration_cast<nanoseconds>(end - start).count() / OPS;
        }

        // średnia
        td_af /= TESTS; l1_af /= TESTS; l2_af /= TESTS;
        td_ab /= TESTS; l1_ab /= TESTS; l2_ab /= TESTS;
        td_fi /= TESTS; l1_fi /= TESTS; l2_fi /= TESTS;

        // zapis CSV
        file << N << ";"
            << td_af << ";" << l1_af << ";" << l2_af << ";"
            << td_ab << ";" << l1_ab << ";" << l2_ab << ";"
            << td_fi << ";" << l1_fi << ";" << l2_fi << "\n";

        // console
        cout << "\nN = " << N << "\n";
        cout << "add_front -> TD: " << td_af << " | L1: " << l1_af << " | L2: " << l2_af << "\n";
        cout << "add_back  -> TD: " << td_ab << " | L1: " << l1_ab << " | L2: " << l2_ab << "\n";
        cout << "find      -> TD: " << td_fi << " | L1: " << l1_fi << " | L2: " << l2_fi << "\n";
    }

    file.close();
    return 0;
}