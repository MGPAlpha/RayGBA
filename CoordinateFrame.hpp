#ifndef COORDINATEFRAME_HPP
#define COORDINATEFRAME_HPP

#include "Vector3.hpp"

struct CoordinateFrame
{
    Vector3 u;
    Vector3 v;
    Vector3 w;

    inline CoordinateFrame(Vector3 u, Vector3 v, Vector3 w) {
        this->u = u.normalized();
        this->v = v.normalized();
        this->w = w.normalized();
    }

    inline CoordinateFrame() : CoordinateFrame(Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1)) {
        
    }

    inline Vector3 transform(Vector3 val) {
        return u*val.x + v*val.y + w*val.z;
    }
};


#endif