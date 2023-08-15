
#include "sphere.h"

namespace RayMarching {
    double Sphere::dist(const QVector3D& point) const {
        return (this->position - point).length() - this->radius;
    }

    Sphere::Sphere(const QVector3D& center, double radius) {
        this->position = center;
        this->radius = radius;
    }

    Sphere::Sphere() {
        this->position = QVector3D(0, 0, 00);
        this->radius = 1;
    }

    void Sphere::info() const {
        qDebug() << "( x =" << this->position.x() << "y =" << this->position.y() << "z =" << this->position.z() << "r =" << this->radius << ")";
    }

    QVector3D Sphere::normal(const QVector3D& point) const {
        return (point - this->position).normalized();
    }
}

