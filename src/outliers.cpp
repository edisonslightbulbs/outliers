#include <vector>

#include "outliers.h"
#include "point.h"
#include "logger.h"
#include "timer.h"

const float IQR = 1.1;

std::vector<Point> outliers::remove(std::vector<Point>& points)
{
    Timer timer;
    /** find within-point variance using the centroid */
    Point centroid = Point::centroid(points);
    for (auto& point : points) {
        float distance = centroid.distance(point);
        point.m_distance.second = distance;
    }
    Point::sort(points);

    /** remove outliers */
    float sd = 0;
    float sum = 0;
    float mean = 0;
    float varsum = 0;
    float variance = 0;

    for (auto& point : points) {
        sum += point.m_distance.second;
    }
    mean = sum / (float)points.size();

    for (auto& point : points) {
        varsum += (float)pow((point.m_distance.second - mean), 2);
    }

    variance = varsum / (float)points.size();
    sd = std::sqrt(variance);

    auto upperBound = mean + (IQR * sd);
    int reject = 0;
    for (auto& point : points) {
        if (point.m_distance.second > upperBound) {
            reject++;
        }
    }
    points.resize(points.size() - reject);
    LOG(INFO) << timer.getDuration() << " ms: outlier removal runtime";

    return points;
}

std::vector<float> outliers::remove(std::vector<float>& values)
{
    Timer timer;
    /** find within-point variance using the centroid */
    std::sort(values.begin(), values.end());

    /** remove outliers */
    float sd = 0;
    float sum = 0;
    float mean = 0;
    float varsum = 0;
    float variance = 0;

    for (auto& val : values) {
        sum += val;
    }
    mean = sum / (float)values.size();

    for (auto& val : values) {
        varsum += (float)pow((val - mean), 2);
    }

    variance = varsum / (float)values.size();
    sd = std::sqrt(variance);

    auto upperBound = mean + (IQR * sd);
    int reject = 0;
    for (auto& val : values) {
        if (val > upperBound) {
            reject++;
        }
    }
    values.resize(values.size() - reject);
    LOG(INFO) << timer.getDuration() << " ms: outlier removal runtime";

    return values;
}
