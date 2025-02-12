
#include "pointlight.h"

namespace RayMarching {
    double PointLight::get_light_strength() const {
        return this->light_strength;
    }

    void PointLight::set_light_strength(double light_strength) {
        this->light_strength = light_strength;
    }

    PointLight::PointLight(const QVector3D& position, double light_strength) {
        this->position = position;
        this->light_strength = light_strength;
    }

    PointLight::PointLight() {
        this->position = QVector3D(0, 0, 0);
        this->light_strength = 1;
    }

    double PointLight::dist(const QVector3D& point) const {
        return (this->position - point).length();
    }

    double PointLight::evaluate_density(const QVector3D& point, const QVector3D& object_normal) const {
        QVector3D light_normal = (point - this->get_position()).normalized();
        double density = (1 - QVector3D::dotProduct(object_normal, light_normal)) / 2;
        density = pow(density, this->get_light_strength());
        // (->, <-) = -1; (->, ->) = 1; I want it to be (->, <-) = 1; (->, ->) = 0;

        return density;
    }
}

