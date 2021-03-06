#include "head.hpp"

#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Head;
using ::math::Vector;

Vector Head::TorsoAnchorPoint() const
{
    Vector position = get_center_position();
    position[0] += radius_ * cos(angle_ + M_PI / 2);
    position[1] += radius_ * sin(angle_ + M_PI / 2);
    return position;
}

void Head::Mirror(math::Vector &mirror_point)
{
    Scale(mirror_point, -1, 1);
    angle_ *= -1;
}
