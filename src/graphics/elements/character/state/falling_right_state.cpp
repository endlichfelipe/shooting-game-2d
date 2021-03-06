#include "./falling_right_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::FallingRightState;
using graphics::elements::character::FallingState;
using graphics::elements::character::GroundedState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

FallingRightState::FallingRightState(FallingRightState &state)
    : BaseState(state)
{
    name_ = "FallingRightState";
}

FallingRightState::FallingRightState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = Character::default_horizontal_velocity_;
    if (character->velocity_[1] < 0)
        character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "FallingRightState";
}

BaseState *FallingRightState::Clone()
{
    return new FallingRightState(*this);
}

void FallingRightState::Jump(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void FallingRightState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
        character_->ProcessMove(delta_time);
    else
    {
        character_->Mirror();
        character_->set_state(new FallingLeftState(character_));
    }
}

void FallingRightState::Stop(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void FallingRightState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kRight)
        character_->ProcessMove(delta_time);
    else
    {
        character_->Mirror();
        character_->set_state(new FallingLeftState(character_));
    }
}
void FallingRightState::ProcessCollision(ICollidable *collidable)
{
    if (collidable->IsColliding(character_->get_last_position()[0], character_->get_position()[1], 0, character_->get_height()))
    {
        character_->ProcessCollisionByBottom(collidable);
        character_->set_state(new GroundedState(character_));
    }
    else
    {
        character_->ProcessCollisionByRight(collidable);
        character_->set_state(new FallingState(character_));
    }
}
