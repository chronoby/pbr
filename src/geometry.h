#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <limits>

#include "math.h"

using Point2f = Vector<float, 2>;
using Point3f = Vector<float, 3>;
using Point2i = Vector<int, 2>;
using Point3i = Vector<int, 3>;

class Ray
{
public:
    Ray() : tMax(std::numeric_limits<float>::max()), time(0.0f) { }
    Ray(Point3f &o, Vector3f &d, float tmax = std::numeric_limits<float>::max(), float t = 0.f)
        : origin(o), direction(d), tMax(tmax), time(t) { } 
    
    Point3f operator()(float t) { return origin + direction * t; }
private:
    Point3f origin;
    Vector3f direction;
    float tMax;
    float time;
    // medium
};

class RayDifferential : public Ray 
{
    // Chapter 10, P106
};

class Bounds
{
public:
    Bounds() 
    {
        float minNum = std::numeric_limits<float>::lowest();
        float maxNum = std::numeric_limits<float>::max();
        pMin = Point3f(maxNum, maxNum, maxNum);
        pMax = Point3f(minNum, minNum, minNum);
    }
    Bounds(const Point3f &p) : pMin(p), pMax(p) { }
    Bounds(const Point3f &p1, const Point3f &p2)
        : pMin(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()), std::min(p1.z(), p2.z())),
        pMax(std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()), std::max(p1.z(), p2.z())) { }

    const Point3f &operator[](int i) const;
    Point3f &operator[](int i);

    // P110
private:
    Point3f pMin, pMax;
};

inline const Point3f &Bounds::operator[](int i) const {
    return (i == 0) ? pMin : pMax;
}

inline Point3f &Bounds::operator[](int i) {
    return (i == 0) ? pMin : pMax;
}

#endif // GEOMETRY_H_