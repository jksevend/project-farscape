#pragma once
#include <unordered_map>

#include <iostream>
#include <string>

#include "game_entity.h"

namespace Tobot::Core {
    class Layer {
        public:
            std::size_t order;

            std::string id;

            std::unordered_map<std::string, GameEntity *> entities;

            Layer(std::string id, std::size_t order);
    };
} // namespace Tobot::Core
