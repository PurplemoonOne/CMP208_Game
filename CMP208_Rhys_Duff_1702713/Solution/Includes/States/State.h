#pragma once

class Context;
class PawnController;

namespace gef
{
	class Platform;
	class Renderer3D;
	class SpriteRenderer;
}

class State
{
public:
	
	virtual ~State(){}

	virtual void SetContext(Context* context){
		this->context = context;
	}

	virtual void OnEnter() = 0;
	virtual void Input(float delta_time) = 0;
	virtual bool Update(float delta_time) = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;

protected:

	gef::Platform* platform;
	Context* context;

};

