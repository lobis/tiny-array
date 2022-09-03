#ifndef COMPACT_ARRAY_LIBRARY_H
#define COMPACT_ARRAY_LIBRARY_H

#include <vector>

class ADCArray {
private:
    std::vector<unsigned int> data;

public:
    inline std::vector<unsigned int> GetData() const { return data; }
};

#endif // COMPACT_ARRAY_LIBRARY_H
