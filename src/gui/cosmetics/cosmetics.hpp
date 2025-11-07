#pragma once

namespace gui {
    struct cosmetics_t {
    public:
        void render(void);
    };

    inline cosmetics_t *cosmetics = new cosmetics_t;
} // namespace gui