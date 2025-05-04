#include "Color.h"

Color ScaleColor(const Color& pixelColor)
{
    return Color{
        static_cast<std::uint8_t>(255 * pixelColor.r),
        static_cast<std::uint8_t>(255 * pixelColor.g),
        static_cast<std::uint8_t>(255 * pixelColor.b),
        static_cast<std::uint8_t>(255 * pixelColor.a)
    };
}