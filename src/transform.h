#include "math.h"

class Transform
{
public:
    Transform() { }
    Transform(float v[]) : m(v) { mInv = m.inverse(); }
    Transform(Matrix4f &t) : m(t) { mInv = m.inverse(); }
    Transform(Matrix4f &t, Matrix4f &tinv) : m(t), mInv(tinv) { }
    
    Transform translate(const Vector3f &delta);
    Transform scale(float x, float y, float z);
    Transform Transform::rotateX(float theta);
    Transform Transform::rotateY(float theta);
    Transform Transform::rotateZ(float theta);
    
private:
    Matrix4f m;
    Matrix4f mInv;
};
