#include <vector>
#include <cstdlib>
#include <algorithm>

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

#include "ScopedTimer.hpp"


{

ScopedTimer timer("nom du chronomètre");
// code à chronométrer
}

std::vector<int> array {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::sort(array.begin(), array.end());// test
