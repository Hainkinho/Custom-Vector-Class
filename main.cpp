#include <iostream>
#include <string>
#include "vector.h"

using namespace std;

int main() {

    Vector<int> vec1;
    Vector vec2{1, 2, 3, 4,5,6,7,8,9,10};

    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    // vec2.pop_back();
    // vec2.pop_back();
    // vec2.pop_back();
    // vec2.pop_back();
    // vec2.pop_back();
    vec2.to_string();
    vec2.shrink_to_fit();
    vec2.to_string();

    return 0;
}