
#ifndef OBJECT_H
#define OBJECT_H
#include <QVector3D>
#include <QDebug>

namespace RayMarching {
    class Object
    {
    protected:
        int type = -1;
        QVector3D position;
    public:
        virtual double dist(const QVector3D& point) const = 0;

        const QVector3D& get_position() const;
        int get_type() const;
        Object() = default;
    };

    class StaticObject : public Object {
    public:
        StaticObject();
        virtual QVector3D normal(const QVector3D& point) const = 0;
    };

    class LightObject : public Object {
    public:
        LightObject();
        virtual double evaluate_density(const QVector3D& point, const QVector3D& object_normal) const = 0;
    };
}

#endif // OBJECT_H
