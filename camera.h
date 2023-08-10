
#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QVector2D>
#include <QImage>
#include <QDebug>
#include <QQuaternion>
#include <object.h>
#include <vector>

namespace RayMarching {
    class Camera
    {
    private:
        const int max_steps = 300;
        const double max_dist = 100;
        const double collision_accuracy = 0.01;

        double light_strength = 4;

        QImage* inner_scene = nullptr;
        QVector3D position;
        QQuaternion rotation;
        std::vector<StaticObject*> static_objects;
        std::vector<LightObject*> light_objects;

        struct IntersectionInfo {
            bool there_is_an_intersection = false;
            StaticObject* object = nullptr;
            double dist = 0;
            double light = 0;
        };

        IntersectionInfo find_closest_static_object(const QVector3D& point);
        double get_light(const QVector3D& point, const StaticObject& object) const;
    public:
        Camera() = default;
        void set_inner_scene(QImage &inner_scene);
        void set_position(const QVector3D &position);
        void set_rotation(const QQuaternion &rotation);
        void add_object(Object &object);

        const QImage &get_inner_scene() const;
        const QVector3D &get_position() const;
        const QQuaternion &get_rotation() const;
        void delete_object();

        void render_the_scene();

        IntersectionInfo ray(const QVector2D &pixel); // 12 bytes are not a lot (pointer and double);
    };
}

#endif // CAMERA_H
