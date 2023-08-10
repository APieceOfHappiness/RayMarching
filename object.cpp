
#include "object.h"

namespace RayMarching {
    int Object::get_type() const {
        return this->type;
    }

    const QVector3D& Object::get_position() const {
        return this->position;
    }

    StaticObject::StaticObject() {
        this->type = 0;
    }

    LightObject::LightObject() {
        this->type = 1;
    }

}

