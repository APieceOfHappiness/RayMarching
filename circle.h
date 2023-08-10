
#ifndef CIRCLE_H
#define CIRCLE_H

#include <object.h>

namespace RayMarching {
    class Circle : public StaticObject
    {
        double radius;
    public:
        double dist(const QVector3D& point) const override;
        QVector3D normal(const QVector3D& point) const override;
        void info() const;

        Circle(const QVector3D& center, double radius);
        Circle();
    };
}

#endif // CIRCLE_H
