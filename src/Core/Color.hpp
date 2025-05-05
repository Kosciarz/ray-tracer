#pragma once

#include <glm/vec4.hpp>

using Color = glm::vec4;

namespace raytracer {

    Color ScaleColor(const Color& pixelColor);

}