#include <Catalogue.h>
#include <iostream>

int main() {

    std::cout << "==================Catalogue====================" << std::endl;

    Catalogue cat("data/nd_courses_2021.json");

    // only print first 5 entries
    std::cout << "Showing first five entries of " << cat.size() << std::endl;
    size_t i = 0;
    for (const auto& id : cat.ids()) {
        if (i++ > 5) break;
        std::cout << cat.at(id);
    }

    std::cout << "Showing (max) 10 results for searching for 'chinese'" << std::endl;
    for (const auto& entry : cat.search("chinese", 10)) {
        std::cout << entry;
    }
    
    std::cout << "===============================================" << std::endl;
    return EXIT_SUCCESS;
}