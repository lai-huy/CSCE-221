#include <stdexcept>
#include "selection.h"

using std::invalid_argument;

int select(size_t k, const int* list, size_t N) {
    if (!list || !N)
        throw invalid_argument("List is empty");
    if (!k || k > N)
        throw invalid_argument("K is out of bounds!");

    int* sort = new int[N]();
    for (size_t i = 0; i < N; ++i)
        sort[i] = list[i];

    for (size_t i = 0; i < N - 1; ++i) {
        for (size_t j = 0; j < N - 1 - i; ++j) {
            if (sort[j] < sort[j + 1]) {
                int temp = sort[j + 1];
                sort[j + 1] = sort[j];
                sort[j] = temp;
            }
        }
    }

    int number = sort[k - 1];
    delete[] sort;
    return number;
}
