
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

    class Display {

    };

    struct ButtonPressed {
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        bool forward = false;
        bool backward = false;
        int cnt = 0;
    };

    class Camera : public QGraphicsView
    {
        Q_OBJECT
    private slots:
        void main_loop_actions();

    private:
        size_t pixel_size_move = 10;
        size_t pixel_size_stop = 1;

        const int temp_width = 1000;
        const int temp_height = 550;

        const int max_steps = 100;
        const double max_dist = 100;
        const double collision_accuracy = 0.01;

        QImage *draft = nullptr;
        QGraphicsScene *scene = nullptr;
        QTimer *infinity_loop = nullptr;
        bool high_quality_is_displayed = false;

        QVector3D direction;
        QVector3D position;
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

        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        ButtonPressed button_pressed;

    public:
        explicit Camera(QWidget *parent = 0);
        void set_draft(QImage &draft);
        void set_position(const QVector3D &position);
        void set_direction(const QVector3D &direction);
        void add_object(Object &object);

        const QImage &get_draft() const;
        const QVector3D &get_position() const;
        const QVector3D &get_direction() const;
        void delete_object();

        void render_the_scene(int pixel_size);

        IntersectionInfo ray(const QVector2D &pixel); // 12 bytes are not a lot (pointer and double);
    };
}

#endif // CAMERA_H
