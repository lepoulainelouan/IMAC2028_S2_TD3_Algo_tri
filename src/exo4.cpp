//Exercice 4 (dichotomie)
#include <vector>
#include <iostream>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

//dichotomie
bool dichotomic_search(std::vector<int> const& vec, int const target) {
    size_t left = 0;
    size_t right = vec.size()- 1;
    while (left <= right) {
        size_t mid = left + (right - left)/ 2;
        if (vec[mid] == target) {
            return true;
        } else if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}
int main() {
    std::vector<int> array {5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::sort(array.begin(), array.end());
    int target = 6;
    if (dichotomic_search(array, target)) {
        std::cout << "Yessss " << target << " est bien dans le tableau" << std::endl;
    } else {
        std::cout << "Oulala nan, " << target << " n'est pas dans le tableau." << std::endl;
    }
}
