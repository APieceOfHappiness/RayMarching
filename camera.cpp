
#include "camera.h"
#include <circle.h>

namespace RayMarching {

    void Camera::set_inner_scene(QImage &inner_scene) {
        this->inner_scene = &inner_scene;
    }

    void Camera::set_position(const QVector3D &position) {
        this->position = position;
    }

    void Camera::set_rotation(const QQuaternion &rotation) {
        this->rotation = rotation;
    }

    void Camera::add_object(Object &object) {
        if (object.get_type() == 0) {
            this->static_objects.push_back(dynamic_cast<StaticObject*>(&object));
        }
        else if (object.get_type() == 1) {
            this->light_objects.push_back(dynamic_cast<LightObject*>(&object));
        }
    }

    const QImage& Camera::get_inner_scene() const {
        return *this->inner_scene;
    }

    const QVector3D& Camera::get_position() const {
        return this->position;
    }

    const QQuaternion& Camera::get_rotation() const {
        return this->rotation;
    }

    void Camera::render_the_scene() {
        if (this->inner_scene) {
            double width = this->inner_scene->width();
            double height = this->inner_scene->height();
            IntersectionInfo intersection{};
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    intersection = this->ray(QVector2D(i, j));
                    if (intersection.there_is_an_intersection) {
                        // TODO: smth
                    }
                    double density = pow(intersection.light, this->light_strength) * 255;
                    this->inner_scene->setPixel(i, j, qRgb(density, density, density));
                }
            }
        }
    }

    Camera::IntersectionInfo Camera::ray(const QVector2D &pixel) {
        IntersectionInfo intersection_info{};

        double whole_dist = 0;
        double weight = this->get_inner_scene().width();
        double height = this->get_inner_scene().height();
        double screen_resolution_aspect = weight / height;

        double y = pixel.y() / height - 0.5;
        double x = pixel.x() / weight - 0.5;
        x *= screen_resolution_aspect;

        QVector3D direction(x, y, 1); // will be improved
        direction.normalize();

        QVector3D temp_point;
        for (int i = 0; i < this->max_steps; ++i) {
            temp_point = this->position + whole_dist * direction;
            intersection_info = this->find_closest_static_object(temp_point);
            whole_dist += intersection_info.dist;

            if (whole_dist > this->max_dist || intersection_info.dist < this->collision_accuracy) {
                if (intersection_info.dist < this->collision_accuracy) {
                    intersection_info.dist = whole_dist;
                    intersection_info.light = this->get_light(temp_point, *intersection_info.object);
                    intersection_info.there_is_an_intersection = true;
                }
                break;
            }
        }
        if (!intersection_info.there_is_an_intersection) {
            intersection_info.dist = 0;
            intersection_info.object = nullptr;
        }
        return intersection_info;
    }

    Camera::IntersectionInfo Camera::find_closest_static_object(const QVector3D& point) {
        double min_dist = INFINITY;
        IntersectionInfo intersection_info;
        double cur_dist;

        for (auto object: this->static_objects) {
            cur_dist = object->dist(point);
            if (cur_dist < min_dist) {
                min_dist = cur_dist;
                intersection_info.dist = cur_dist;
                intersection_info.object = object;
            }
        }
        return intersection_info;
    }

    double Camera::get_light(const QVector3D& point, const StaticObject& object) const {
        QVector3D light_pos(2, 2, 0); // TODO: new objects: lights

        object.dist(point);
        QVector3D object_normal = object.normal(point);
        QVector3D light_normal = (point - light_pos).normalized();

        // (->, <-) = -1; (->, ->) = 1; I want it to be (->, <-) = 1; (->, ->) = 0;
        return (1 - QVector3D::dotProduct(object_normal, light_normal)) / 2;
    }
}

