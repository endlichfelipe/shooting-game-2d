#pragma once

#include <string>

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

namespace graphics::elements::character
{
    class Character;

    class BaseState
    {
    public:
        BaseState();
        BaseState(BaseState &state)
            : character_(state.character_), direction_(state.direction_){};
        BaseState(Character *character)
            : character_(character) {}
        virtual ~BaseState() {}

        std::string get_name() const;

        virtual void Jump(double delta_time){};
        virtual void Jump(double delta_time, physic::Direction direction){};
        virtual void Stop(double delta_time){};
        virtual void Move(double delta_time, physic::Direction direction){};
        virtual void ProcessCollision(physic::ICollidable *collidable){};
        virtual void ProcessGravity(){};

        virtual BaseState *Clone() = 0;

        virtual std::string to_string() const;

    protected:
        Character *character_;
        physic::Direction direction_ = physic::Direction::kRight;
        std::string name_ = "Unnamed";
    };
}