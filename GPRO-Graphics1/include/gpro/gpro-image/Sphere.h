#pragma once

/*
    Modified by : ____Shakeem Brown & Andrew Barnett________
    Modified because : ___Needed to Add the sphere class provided in Peter Shirley's
    "Ray Tracing in one Weekend" in order to provide a specific shape/ object to draw
    and to be hit._________
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "gpro/gpro-math/Vector3.h"
#include "gpro/gpro-math/Hittable.h"

class sphere : public hittable  // The Sphere object is a child of hittable
{
public:
    sphere() {} // Default constructor
    sphere(point3 cen, double r) : center(cen), radius(r) {}; // Constructor

    virtual bool hit(
        const ray& r, double tmin, double tmax, hit_record& rec) const override; // Inheritance of hittable

public:
    point3 center;
    double radius;
};

// Defines the way the sphere is being hit
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    vector3 oc = r.origin() - center;
    double a = r.direction().squared_length();
    double half_b = dot(oc, r.direction());
    double c = oc.squared_length() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant > 0) // checks if the sphere is being hit by a postive ray
    {
        double root = sqrt(discriminant);

        // Using the negative square root
        double temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) // The first case: in bounds of the sphere 
        {                                 // so there for the ray the ray is hitting the sphere
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            vector3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }

        // Using the postive square root
        temp = (-half_b + root) / a;      // The second case: in bounds of the sphere 
        if (temp < t_max && temp > t_min) // so there for the ray the ray is hitting the sphere
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            vector3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }
    return false;
}


#endif