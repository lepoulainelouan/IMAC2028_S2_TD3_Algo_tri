#include <vector>
#include <algorithm>


bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

//tri par selection
std::vector<int> array {1, 2, 3, 4, 5, 6, 7, 8, 9};
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
