#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "gpro/gpro-math/Ray.h"

struct hit_record
{
    point3 p;
    vector3 normal;
    double t;

    bool front_face;

    // Defines what the front of the object is and what it's normal
    inline void set_face_normal(const ray& r, const vector3& outward_normal) 
    {                                                                        
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

class hittable 
{
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif