#ifndef averagePointClipping_hpp
#define averagePointClipping_hpp

#include "data.h"
#include <vector>

class AveragePointClipping {
private:
    std::vector<Section> solve(std::vector<Section> sections);
};

#endif /* averagePointClipping_h */
