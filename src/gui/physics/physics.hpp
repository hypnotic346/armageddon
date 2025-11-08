#pragma once

namespace gui {
    struct physics_t {
    public:
        void render(void);
    };

    inline physics_t *physics = new physics_t;
} // namespace gui