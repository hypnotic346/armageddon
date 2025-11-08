#pragma once

#include <unordered_map>

namespace settings {
    struct val_t {
        bool b;
        float fl;
        int i;
    };

    inline std::unordered_map<std::string, val_t> _vars = {};

    template <typename T>
    inline T &get(const std::string &key) {
        if constexpr (std::is_same_v<T, bool>)
            return _vars[key].b;

        else if constexpr (std::is_same_v<T, int>)
            return _vars[key].i;

        else if constexpr (std::is_same_v<T, float>)
            return _vars[key].fl;
    }
} // namespace settings