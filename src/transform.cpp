#include "transform.h"

Transform Transform::translate(const Vector3f &delta)
{
    Matrix4f m(std::vector<float>({
        1, 0, 0, delta.x(), 
        0, 1, 0, delta.y(),
        0, 0, 1, delta.z(),
        0, 0, 0, 1}) );
    Matrix4f minv(std::vector<float>({1, 0, 0, -delta.x(), 
        0, 1, 0, -delta.y(),
        0, 0, 1, -delta.z(),
        0, 0, 0, 1}) );
    return Transform(m, minv);
}

Transform Transform::scale(float x, float y, float z) 
{
    Matrix4f m(std::vector<float>({
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1}) );
    Matrix4f minv(std::vector<float>({
        1/x, 0, 0, 0,
        0, 1/y, 0, 0,
        0, 0, 1/z, 0,
        0, 0, 0, 1}) );
    return Transform(m, minv);
}

Transform Transform::rotateX(float theta)
{
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        1, 0, 0, 0,
        0, cosTheta, -sinTheta, 0,
        0, sinTheta, cosTheta, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}

Transform Transform::rotateY(float theta)
{
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        cosTheta, 0, -sinTheta, 0,
        0, 1, 0, 0,
        sinTheta, 0, cosTheta, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}

Transform Transform::rotateZ(float theta)
{
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        cosTheta, -sinTheta, 0, 0,
        sinTheta, cosTheta, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}

Point3f Transform::operator()(const Point3f& p) const
{
    Vector4f point(p.x(), p.y(), p.z(), 1);
    Vector4f mul = m * point;
    if (mul.w() == 1) return Point3f(mul.x(), mul.y(), mul.z());
    else return Point3f(mul.x(), mul.y(), mul.z()) / mul.w();
}

Bounds Transform::operator()(const Bounds &b) const {
    const Transform &M = *this;
    Bounds ret(M(Point3f(b.pMin.x(), b.pMin.y(), b.pMin.z())));
    ret = Union(ret, M(Point3f(b.pMax.x(), b.pMin.y(), b.pMin.z())));
    ret = Union(ret, M(Point3f(b.pMin.x(), b.pMax.y(), b.pMin.z())));
    ret = Union(ret, M(Point3f(b.pMin.x(), b.pMin.y(), b.pMax.z())));
    ret = Union(ret, M(Point3f(b.pMin.x(), b.pMax.y(), b.pMax.z())));
    ret = Union(ret, M(Point3f(b.pMax.x(), b.pMax.y(), b.pMin.z())));
    ret = Union(ret, M(Point3f(b.pMax.x(), b.pMin.y(), b.pMax.z())));
    ret = Union(ret, M(Point3f(b.pMax.x(), b.pMax.y(), b.pMax.z())));
    return ret;
}
