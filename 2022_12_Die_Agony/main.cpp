#include <chrono>
#include <cmath>
#include "die_agony.h"

int main() {
    // initialize everything
    DieAgony run;
    std::vector<std::vector<int>> seen(6, std::vector<int>(6, 0));
    std::vector<int> empty_path(1, 0);
    std::map<std::string, int> blank_die;
    auto start = std::chrono::high_resolution_clock::now();
    // try to solve when first roll is to the 5 and when first roll is to the 77
    run.solve(empty_path, blank_die, 4, 0, 1, seen);
    run.solve(empty_path, blank_die, 5, 1, 1, seen);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nSolved in: " << (float) duration.count() * pow(10, -6) << " seconds\n";
}