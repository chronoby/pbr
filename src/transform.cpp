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

Transform Transform::rotateX(float theta) {
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        1, 0, 0, 0,
        0, cosTheta, -sinTheta, 0,
        0, sinTheta, cosTheta, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}

Transform Transform::rotateY(float theta) {
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        cosTheta, 0, -sinTheta, 0,
        0, 1, 0, 0,
        sinTheta, 0, cosTheta, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}

Transform Transform::rotateZ(float theta) {
    float sinTheta = std::sin(theta * PI / 180);
    float cosTheta = std::cos(theta * PI / 180);
    Matrix4f m(std::vector<float>({
        cosTheta, -sinTheta, 0, 0,
        sinTheta, cosTheta, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1}) );
    return Transform(m, m.transpose());
}
