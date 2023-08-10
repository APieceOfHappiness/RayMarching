
#include "object.h"

namespace RayMarching {
    int Object::get_type() const {
        return this->type;
    }

    StaticObject::StaticObject() {
        this->type = 0;
    }

    LightObject::LightObject() {
        this->type = 1;
    }
}

