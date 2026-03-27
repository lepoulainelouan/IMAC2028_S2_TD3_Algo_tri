#include <vector>
#include <iostream>
#include <algorithm>

//algo de dichotomie
bool dichotomie(std::vector<int> const& vec, int const value) {
    size_t left = 0;
    size_t right = vec.size() - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] == value) {
            return true;
        } else if (vec[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

int main (){
    std::vector<int> array {1, 67, 42, 4, 11, 6, 5, 8, 9};
    bool found = dichotomie(array, 42);
    if (found) {
        std::cout << "Valeur trouvée" << std::endl;
    } else {
        std::cout << "Valeur non trouvée" << std::endl;
    }
}

