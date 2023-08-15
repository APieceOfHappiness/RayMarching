
#ifndef SPHERE_H
#define SPHERE_H

#include <object.h>

namespace RayMarching {
    class Sphere : public StaticObject
    {
        double radius;
    public:
        double dist(const QVector3D& point) const override;
        QVector3D normal(const QVector3D& point) const override;
        void info() const;

        Sphere(const QVector3D& center, double radius);
        Sphere();
    };
}

#endif // SPHERE_H
