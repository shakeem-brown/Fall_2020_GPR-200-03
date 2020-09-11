#pragma once

#ifndef HITTABLES
#define HITTABLES

#include "gpro/gpro-math/Hittable.h"

#include <memory>
#include <vector>

using namespace std;
using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable 
{
    public:
        hittable_list() {} // Default constructor
        hittable_list(shared_ptr<hittable> object) { add(object); } // Constructor

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double tmin, double tmax, hit_record& rec) const override; // Inheritance of hittable

    public:
        vector<shared_ptr<hittable>> objects;
};

// Checks if an object has been hit at a given time and updates information accordingly
bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec; // creates a temporay object
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const shared_ptr<hittable>& object : objects) 
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) // Checks if the object is hit
        {                                                    
            hit_anything = true;
            closest_so_far = temp_rec.t; // the time is updated
            rec = temp_rec;              // the hit record object is updated
        }
    }
    return hit_anything; // returns if something has been hit or not
}

#endif
