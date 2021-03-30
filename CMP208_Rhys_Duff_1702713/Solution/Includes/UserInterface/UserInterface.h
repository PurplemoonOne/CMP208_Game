#pragma once

namespace gef
{
	class SpriteRenderer;
}

class UserInterface
{
protected:

	UserInterface(gef::SpriteRenderer* sprite_renderer, gef::Platform* platform_);

public:

	~UserInterface();

	static UserInterface* Create(gef::SpriteRenderer* sprite_renderer, gef::Platform* platform_);

private:



};

