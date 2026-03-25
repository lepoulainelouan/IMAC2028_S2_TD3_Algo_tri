#include <vector>
#include <iostream>
#include <algorithm>


bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

//tri par selection
int main (){
    std::vector<int> array {1, 2, 3, 4, 7, 6, 5, 8, 9};
        if (is_sorted(array)) {
            std::cout << "Le tableau est trié" << std::endl;
        } else {
            std::cout << "Le tableau n'est pas trié" << std::endl;
        }   
}

void selection_sort(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min]) {
                min=j;
            }
        }
        std::swap(vec[i], vec[min]);
    }
}

