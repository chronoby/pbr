#include "geometry.h"

const Point3f& Bounds::operator[](int i) const
{
    return (i == 0) ? pMin : pMax;
}

Point3f& Bounds::operator[](int i)
{
    return (i == 0) ? pMin : pMax;
}

Bounds Union(const Bounds& b1, const Bounds& b2)
{
    return Bounds(
        Point3f(std::min(b1.pMin.x(), b2.pMin.x()),
                std::min(b1.pMin.y(), b2.pMin.y()),
                std::min(b1.pMin.z(), b2.pMin.z())),
        Point3f(std::max(b1.pMax.x(), b2.pMax.x()),
                std::max(b1.pMax.y(), b2.pMax.y()),
                std::max(b1.pMax.z(), b2.pMax.z())));
}