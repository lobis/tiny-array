
#include "tiny_array/tiny_array.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    // create a tiny array of 12 bits and size 100
    auto array = tiny_array::TinyArray<12, 100>();
    // print the size of the array
    cout << "Size of the array: " << array.size() << endl;
    // print the range of the array
    cout << "Range of the array: " << array.range().first << " - " << array.range().second << endl;
    return 0;
}