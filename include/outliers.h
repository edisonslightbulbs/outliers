#ifndef LDA_H
#define LDA_H

#include "point.h"
#include <vector>

namespace outliers {
std::vector<Point> remove(std::vector<Point>& points);
std::vector<float> remove(std::vector<float>& points);
}
#endif /* LDA_H */
