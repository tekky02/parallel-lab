#include <vector>
#include <cmath>

#include "utils.hpp"

#define SEQUENTIAL 0       // for sequential analysis.
#define SPEEDUP 1

void hanoi_seq(int n) {
    int i = 1;
    uint64_t step = 1;
    while (i < n) {
#if SEQUENTIAL
        fprintf(stderr, "%ld ", step);
        step *= 2;
#elif SPEEDUP
        fprintf(stderr, "%ld ", uint64_t(pow(2, i)));
#endif
        i++;
    }
    fprintf(stderr, "%ld\n", uint64_t(pow(2, i)));
}

void hanoi_omp(uint64_t arr[], int n) {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = (uint64_t)pow(2, i);
    }

    int j = 0;
    for (; j < n - 1; j++) {
        fprintf(stderr, "%ld ", arr[j]);
    }
    fprintf(stderr, "%ld\n", arr[j]);
}

int main(int argc, char const *argv[]) {
#if SEQUENTIAL
    std::vector<int> input_scale = {10, 20, 30, 40, 50, 60}; // should not larger than 64 since uint64_t has 64 bit.
    // for sequential analysis.
    for (auto input : input_scale) {
        {
            utils::Timer timer{"input_scale=" + std::to_string(input)};
            for (int i = 0; i < 100; i++) { // for time scale.
                hanoi_seq(input);
            }
        }
    }
#elif SPEEDUP
    int input_scale = 60;
    // sequence
    {
        utils::Timer timer{"sequence"};
        for (int i = 0; i < 100; i++) {
            hanoi_seq(input_scale);
        }
    }

    // OpenMP
    uint64_t arr[input_scale];
    {
        utils::Timer timer{"OpenMP"};
        for (int i = 0; i < 100; i++) {
            hanoi_omp(arr, input_scale);
        }
    }
#endif

    return 0;
}
