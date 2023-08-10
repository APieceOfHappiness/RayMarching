
#include "circle.h"

namespace RayMarching {
    double Circle::dist(const QVector3D& point) const {
        return (this->position - point).length() - this->radius;
    }

    Circle::Circle(const QVector3D& center, double radius) {
        this->position = center;
        this->radius = radius;
    }

    void Circle::info() const {
        qDebug() << "( x =" << this->position.x() << "y =" << this->position.y() << "z =" << this->position.z() << "r =" << this->radius << ")";
    }

    QVector3D Circle::normal(const QVector3D& point) const {
        return (point - this->position).normalized();
    }
}

