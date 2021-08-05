#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <iostream>
#include <memory>
#include <vector>

#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable{
    public:
        std::vector<shared_ptr<Hittable>> objectsList;
    public:
        HittableList(){}
        HittableList(shared_ptr<Hittable> object){ this->add(object); }

        void add(shared_ptr<Hittable> object){
            objectsList.push_back(object);
        }

        void clear(){
            objectsList.clear();
        }

        virtual bool isRayHit(const Ray& r, double t_min, double t_max, HitRecord& hitRecord) const override {
            HitRecord tempRec;
            bool hitAnything = false;
            double closest_t = t_max;

            for (const auto &object : this->objectsList)
            {
                if (object->isRayHit(r, t_min, closest_t, tempRec))
                {
                    hitAnything = true;
                    closest_t = tempRec.t;
                    hitRecord = tempRec;
                }
            }

            return hitAnything;
        };
};

#endif