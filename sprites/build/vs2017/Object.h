#pragma once

namespace gef
{
	class Platform;
	class Sprite;
}

class Object
{
public:

	Object();
	~Object();


public:

	/*..Getter methods to obtain object attributes..*/
	inline gef::Sprite* GetGFX();


protected:

	gef::Sprite* graphic;

private:


};

