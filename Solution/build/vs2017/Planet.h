#pragma once
#include "GameObject.h"

namespace gef
{

}

class Planet : public GameObject
{
protected:

	Planet(PrimitiveBuilder* primitive_builder, gef::Platform& platform_, b2World* world_, float radius);
	~Planet();

protected:


private:
};

