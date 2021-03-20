#ifndef LDA_H
#define LDA_H

#include <vector>
#include "point.h"

namespace outliers {
    std::vector<Point> remove(std::vector<Point>& points);
    std::vector<float> remove(std::vector<float>& points);
}
#endif /* LDA_H */
