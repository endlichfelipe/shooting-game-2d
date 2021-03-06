#pragma once

#include "../../../shapes/rectangle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Thig : public graphics::shapes::Rectangle
    {
    public:
        Thig(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
            : Rectangle(origin, width, height, color){};
        ~Thig() = default;

        math::Vector TorsoAnchorPoint() const;
        math::Vector CalfAnchorPoint() const;

        void Mirror(math::Vector &mirror_point);
    };
}