#include "pch.h"
#include "UserInterface.h"

UserInterface::UserInterface(gef::SpriteRenderer* sprite_renderer, gef::Platform* platform_)
{
}

UserInterface* UserInterface::Create(gef::SpriteRenderer* sprite_renderer, gef::Platform* platform_)
{
	return new UserInterface(sprite_renderer, platform_);
}
