
#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QVector2D>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QImage>
#include <QDebug>
#include <QQuaternion>
#include <object.h>
#include <vector>

#include <QTimer>

namespace RayMarching {
    class Camera : public QGraphicsView
    {
        Q_OBJECT
    private:
        int temp_width = 1000;
        int temp_height = 550;

        const int max_steps = 10;
        const double max_dist = 10;
        const double collision_accuracy = 0.01;

        QImage *draft = nullptr;
        QGraphicsScene *scene = nullptr;

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

        void keyPressEvent(QKeyEvent *event);
    public:
        explicit Camera(QWidget *parent = 0);
        void set_draft(QImage &draft);
        void set_position(const QVector3D &position);
        void set_rotation(const QQuaternion &rotation);
        void add_object(Object &object);

        const QImage &get_draft() const;
        const QVector3D &get_position() const;
        const QQuaternion &get_rotation() const;
        void delete_object();

        void render_the_scene();

        IntersectionInfo ray(const QVector2D &pixel); // 12 bytes are not a lot (pointer and double);
    };
}

#endif // CAMERA_H
