#include <vector>
#include <iostream>
#include <algorithm>
bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

//tri rapide (quick sort)

//partition
size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right){
if (left < right) {
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
}

//Récursion
void quick_sort(std::vector<int> & vec, size_t const left, size_t const right){
if (left < right) {
    size_t pivot_index = quick_sort_partition(vec, left, right);
    quick_sort(vec, left, pivot_index - 1);
    quick_sort(vec, pivot_index+1, right);
}
}

void quick_sort(std::vector<int> & vec) {
    quick_sort(vec, 0, vec.size() - 1);
}

int main (){
    std::vector<int> array {1, 67, 42, 4, 11, 6, 5, 8, 9};
    quick_sort(array);
        if (is_sorted(array)) {
            std::cout << "Le tableau est trié" << std::endl;
        } else {
            std::cout << "Le tableau n'est pas trié" << std::endl;
        }   
}

