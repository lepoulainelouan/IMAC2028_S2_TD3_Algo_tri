#include <vector>
#include <iostream>
#include <algorithm>
//fonctions de hachages
//haching ordonné

size_t folding_string_ordered_hash(std::string const& s, size_t max){
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        hash += s[i] * (i + 1);
    }
    return hash % max;
}

int main(){
    std::vector<std::string> strings = {"banane","abricot","Benoit","albert","carotte","gamberge","kayak","jonglage","pouet"};
    size_t max = 10;
    for (const auto & s : strings) {
        std::cout << "La valeur de hachage de \"" << s <<"\" est " <<folding_string_ordered_hash(s, max) << std::endl;
    }
}