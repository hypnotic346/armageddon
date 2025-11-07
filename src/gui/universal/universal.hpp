#pragma once

namespace gui {
    struct universal_t {
    public:
        void render(void);
    };

    inline universal_t *universal = new universal_t;
}