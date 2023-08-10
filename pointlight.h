
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <object.h>

namespace RayMarching {
    class PointLight : public LightObject
    {
    private:
        double light_strength = 1;
    public:
        double get_light_strength() const;
        void set_light_strength(double light_strength);
        double dist(const QVector3D& point) const override;

        double evaluate_density(const QVector3D& point, const QVector3D& object_normal) const;

        PointLight(const QVector3D& position, double light_strength);
        PointLight();
    };
};

#endif // POINTLIGHT_H
