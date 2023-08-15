
#include "camera.h"
#include <circle.h>

namespace RayMarching {

    Camera::Camera(QWidget *parent) : QGraphicsView(parent) {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setAlignment(Qt::AlignCenter);

        this->direction = QVector3D(0, 0, 1);
        this->direction = QVector3D(0, 0, 0);

        this->draft = new QImage(this->temp_width, this->temp_height, QImage::Format_RGB32);
        this->scene = new QGraphicsScene(this);
        this->scene->addPixmap(QPixmap::fromImage(*this->draft));
        this->setScene(this->scene);
    }

    void Camera::set_draft(QImage &draft) {
        this->draft = &draft;
    }

    void Camera::set_position(const QVector3D &position) {
        this->position = position;
    }

    void Camera::set_direction(const QVector3D &direction) {
        this->direction = direction;
    }

    void Camera::add_object(Object &object) {
        if (object.get_type() == 0) {
            this->static_objects.push_back(dynamic_cast<StaticObject*>(&object));
        }
        else if (object.get_type() == 1) {
            this->light_objects.push_back(dynamic_cast<LightObject*>(&object));
        }
    }

    const QImage& Camera::get_draft() const {
        return *this->draft;
    }

    const QVector3D& Camera::get_position() const {
        return this->position;
    }

    const QVector3D& Camera::get_direction() const {
        return this->direction;
    }

    void Camera::render_the_scene() {
        if (this->draft) {
            double optim_width = this->draft->width() / this->pixel_size_cur;
            double optim_height = this->draft->height() / this->pixel_size_cur;
            IntersectionInfo intersection{};
            for (int i = 0; i < optim_width; ++i) {
                for (int j = 0; j < optim_height; ++j) {
                    intersection = this->ray(QVector2D(this->pixel_size_cur * i, this->pixel_size_cur * j));
                    if (intersection.there_is_an_intersection) {
                        // TODO: smth
                    }
                    double density = intersection.light * 255;
                    for (size_t x = 0; x < this->pixel_size_cur; ++x) {
                        for (size_t y = 0; y < this->pixel_size_cur; ++y) {
                            this->draft->setPixel((this->pixel_size_cur * i + x) % this->draft->width(),
                                                  (this->pixel_size_cur * j + y) % this->draft->height(),
                                                  qRgb(density, density, density));
                        }
                    }
                }
            }

            this->scene->clear();
            this->scene->addPixmap(QPixmap::fromImage(*this->draft));
            this->update();
        }
    }

    Camera::IntersectionInfo Camera::ray(const QVector2D &pixel) {
        IntersectionInfo intersection_info{};
        if (!this->static_objects.size()) {
            return intersection_info;
        }

        double whole_dist = 0;
        double weight = this->get_draft().width();
        double height = this->get_draft().height();
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

        object.dist(point);
        QVector3D object_normal = object.normal(point);
        double total_density = 0;
        for (auto light_object : this->light_objects) {
            total_density += light_object->evaluate_density(point, object_normal);
        }

        if (total_density > 1) {
            total_density = 1;
        }

        return total_density;
    }

    void Camera::keyPressEvent(QKeyEvent *event) {
        this->pixel_size_cur = this->pixel_size_move;

        switch(event->key()) {
            case Qt::Key_W:
                if (!this->button_pressed.forward) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.forward = true;
                break;
            case Qt::Key_D:
                if (!this->button_pressed.right) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.right = true;
                break;
            case Qt::Key_S:
                if (!this->button_pressed.backward) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.backward = true;
                break;
            case Qt::Key_A:
                if (!this->button_pressed.left) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.left = true;
                break;
            case Qt::Key_Space:
                if (!this->button_pressed.up) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.up = true;
                break;
            case Qt::Key_Shift:
                if (!this->button_pressed.down) {
                    this->button_pressed.cnt++;
                }
                this->button_pressed.down = true;
                break;
        }

        if (this->button_pressed.forward) {
            this->position.setZ(this->position.z() + 0.05);
        }
        if (this->button_pressed.right) {
            this->position.setX(this->position.x() + 0.05);
        }
        if (this->button_pressed.backward) {
            this->position.setZ(this->position.z() - 0.05);
        }
        if (this->button_pressed.left) {
            this->position.setX(this->position.x() - 0.05);
        }
        if (this->button_pressed.up) {
            this->position.setY(this->position.y() - 0.05);
        }
        if (this->button_pressed.down) {
            this->position.setY(this->position.y() + 0.05);
        }
        this->render_the_scene();
    }

    void Camera::keyReleaseEvent(QKeyEvent *event) {
        if (event->isAutoRepeat())
        {
            return;
        }

        switch(event->key()) {
            case Qt::Key_W:
                this->button_pressed.forward = false;
                this->button_pressed.cnt--;
                break;
            case Qt::Key_D:
                this->button_pressed.right = false;
                this->button_pressed.cnt--;
                break;
            case Qt::Key_S:
                this->button_pressed.backward = false;
                this->button_pressed.cnt--;
                break;
            case Qt::Key_A:
                this->button_pressed.left = false;
                this->button_pressed.cnt--;
                break;
            case Qt::Key_Space:
                this->button_pressed.up = false;
                this->button_pressed.cnt--;
                break;
            case Qt::Key_Shift:
                this->button_pressed.down = false;
                this->button_pressed.cnt--;
                break;
        }

        if (!this->button_pressed.cnt) {
            this->pixel_size_cur = this->pixel_size_stop;
            this->render_the_scene();
        }
    }
}


