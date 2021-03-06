#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

namespace graphics::elements::character
{
    class Character;

    class GroundedState : public BaseState
    {
    public:
        GroundedState(GroundedState &state);
        GroundedState(Character *character);

        virtual BaseState *Clone() override;
        virtual void Jump(double delta_time) override;
        virtual void Jump(double delta_time, physic::Direction direction) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
    };
}
