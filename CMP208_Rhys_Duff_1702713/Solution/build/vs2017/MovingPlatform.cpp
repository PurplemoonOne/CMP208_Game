#include "pch.h"
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform()
    :
    impulse(12.5f),
    oscillation_switch(0)
{
}

MovingPlatform* MovingPlatform::Create()
{
    return new MovingPlatform();
}

MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Update(float delta_time)
{
    GameObject::Update(delta_time);

 //   Oscillate(delta_time);
}

void MovingPlatform::OnCollision(ObjectType type)
{
    if (type == ObjectType::dynamic_pawn_)
    {

    }
}

void MovingPlatform::EndCollision(ObjectType type)
{
}

void MovingPlatform::SetTargetLocations(b2Vec2 loc_a, b2Vec2 loc_b)
{
    targets[0] = loc_a;
    targets[1] = loc_b;
}

void MovingPlatform::Oscillate(float delta_time)
{
    // Get the current position.
    float current_x = GetPosition().x();
    float current_y = GetPosition().y();

    // Calculate the direction.
    b2Vec2 direction  = 
    {
        (targets[oscillation_switch].x - current_x * impulse * delta_time), 
        (targets[oscillation_switch].y - current_y * impulse * delta_time)
    };

    // Check if we've reached the target.
    if ((int)current_x != (int)targets[oscillation_switch].x)
    {
        if (physics)
        {
            physics->PhysicsBody()->ApplyLinearImpulseToCenter(direction, true);
        } 
        else {
            return;
        }
    }
    else
    {
        // If we've reached the target incriment/decriment the value depending on which target we 
        //just reached.
        oscillation_switch = ((oscillation_switch == 0) ? ++oscillation_switch : --oscillation_switch);
    }
}
