//Exercice 3 (Comparaison des algorithmes de tri)

#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ScopedTimer.hpp"

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max; });
    return vec;
}
//tri par selection
void selection_sort(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min])
                min = j;
        }
        std::swap(vec[i], vec[min]);
    }
}
//tri rapide
// Partition
size_t quick_sort_partition(std::vector<int>& vec, size_t left, size_t right) {
    int pivot = vec[right];
    size_t i = left;
    for (size_t j = left; j < right; ++j) {
        if (vec[j] < pivot) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[right]);
    return i;
}

// Récursion
void quick_sort(std::vector<int>& vec, size_t left, size_t right) {
    if (left < right) {
        size_t pivot_index = quick_sort_partition(vec, left, right);
        if (pivot_index > 0)
            quick_sort(vec, left, pivot_index - 1);
        quick_sort(vec, pivot_index + 1, right);
    }
}

void quick_sort(std::vector<int>& vec) {
    if (!vec.empty())
        quick_sort(vec, 0, vec.size() - 1);
}


int main() {
    size_t const size = 100000;
    std::vector<int> vec1 = generate_random_vector(size);
    std::vector<int> vec2 = vec1;
    std::vector<int> vec3 = vec1;
    
    {
        ScopedTimer timer("selection_sort");
        selection_sort(vec1);
    }
    {
        ScopedTimer timer("quick_sort");
        quick_sort(vec2);
    }
    {
        ScopedTimer timer("std::sort");
        std::sort(vec3.begin(), vec3.end());
    }

    return 0;
}