#pragma once

namespace gui {
    struct general_t {
    public:
        void render(void);
    };

    inline general_t *general = new general_t;
}