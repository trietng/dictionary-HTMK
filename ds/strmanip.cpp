#include "strmanip.hpp"

std::string tolower(std::string source) {
    for (auto& c : source) {
        c = tolower(c);
    }
    return source;
}

std::string toupper(std::string source) {
    for (auto& c : source) {
        c = toupper(c);
    }
    return source;
}
