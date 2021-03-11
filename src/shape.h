#include "transform.h"
#include "geometry.h"

class Shape
{
public:
    Shape(Transform *o2w, Transform *w2o, bool reverse) :
        ObjectToWorld(o2w), WorldToObject(w2o),
        reverseOrientation(reverse) { }

    virtual Bounds ObjectBound() const = 0;
private:
    Transform *ObjectToWorld, *WorldToObject;
    bool reverseOrientation;
    bool transformSwapHandedness;
};
